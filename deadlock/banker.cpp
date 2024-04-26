#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// namespace
using std::cout, std::endl;
using std::min, std::max, std::sort;
using std::vector, std::string;

// usings and typedefs
using LL = long long;
typedef vector<LL> vecLL;
typedef vector<vecLL> vecLL2;
typedef const vecLL &cvecLLr;
typedef const vecLL2 &cvecLL2r;

/**
 * Arithmetic operation to vecLL object, return the result as a new vector with same size.
 *
 * Size of two vectors must be the same
 *
 * @param opr1 The first operand
 * @param opr2 The second operand
 * @param flag If true, perform addition, else perform subtraction(default)
 *
 * @return vecLL object with the same size of two input parameter as result.
 */
vecLL operateVector(cvecLLr opr1, cvecLLr opr2, bool flag = false)
{
    if (opr1.size() != opr2.size())
    {
        cout << "[Error]"
             << "[VectorSizeError] "
             << "Cannot substract two vector since they have different size"
             << endl;
        exit(0);
    }

    vecLL ansVec;
    LL size = opr1.size();

    if (size == 0)
    {
        cout << "[Warning] Subtract two empty vectors";
        return ansVec;
    }

    for (LL i = 0; i < size; ++i)
    {
        if (flag)
        {
            ansVec.push_back(opr1[i] + opr2[i]);
        }
        else
        {
            ansVec.push_back(opr1[i] - opr2[i]);
        }
    }

    return ansVec;
}

vecLL operator+(cvecLLr opr1, cvecLLr opr2)
{
    return operateVector(opr1, opr2, true);
}

vecLL operator-(cvecLLr opr1, cvecLLr opr2)
{
    return operateVector(opr1, opr2, false);
}

std::ostream &operator<<(std::ostream &os, cvecLLr vec)
{
    os << "{";
    for (const auto &i : vec)
    {
        os << i << ", ";
    }
    os << "}";

    return os;
}

/**
 * opr1 is considered >= opr2 only when for any i, opr1[i] >= opr2[i]
 */
bool operator>=(cvecLLr opr1, cvecLLr opr2)
{
    vecLL tmp = opr1 - opr2;

    for (const auto &num : tmp)
    {
        if (num < 0)
        {
            return false;
        }
    }

    return true;
}

bool operator<(cvecLLr opr1, cvecLLr opr2)
{
    return !(opr1 >= opr2);
}

/**
 * Similar to operateVector, check its doc for more info.
 */
vecLL2 operateMatrix(cvecLL2r opr1, cvecLL2r opr2, bool flag = false)
{
    if (opr1.size() != opr2.size())
    {
        cout << "[Error]"
             << "[MatrixSizeError] "
             << "Cannot substract two matrices since they have different size"
             << endl;
        exit(0);
    }

    vecLL2 ansMat;
    LL rowCount = opr1.size();

    if (rowCount == 0)
    {
        cout << "[Warning] Subtract two empty matrices";
        return ansMat;
    }

    for (LL i = 0; i < rowCount; ++i)
    {
        ansMat.push_back(operateVector(
            opr1[i],
            opr2[i],
            flag));
    }

    return ansMat;
}

vecLL2 operator+(cvecLL2r opr1, cvecLL2r opr2)
{
    return operateMatrix(opr1, opr2, true);
}

vecLL2 operator-(cvecLL2r opr1, cvecLL2r opr2)
{
    return operateMatrix(opr1, opr2, false);
}

/**
 * Runtime class for banker algorithm
 *
 * Usage Guide:
 * - Call updateNeed() when mMax or mNeed has been changed
 */
class BankerRuntime
{
private:
    vecLL2 mAllocated;
    vecLL2 mMax;
    vecLL2 mNeed;
    vecLL mAvailable;
    vecLL mTmpAvailable; // work vector in bankers algorithm
    vecLL mFinished;
    vector<LL> mSafeSequence;

    /**
     * Use mAllocated and mMax to calculate and update mNeed
     */
    BankerRuntime &updateNeed()
    {
        // assert rows count identical
        if (mAllocated.size() != mMax.size())
        {
            cout << "[Error]";
            cout << "[MatrixSizeError] ";
            cout << "The matrix rows count different between "
                 << "mAvailable and mMax when updating mNeed"
                 << endl;
            exit(0);
        }

        mNeed = mMax - mAllocated;

        return (*this);
    }

    /**
     * If all process has been marked finished
     *
     * This method only used when checking safety
     */
    bool allFinished()
    {
        for (const auto &isFin : mFinished)
        {
            if (!isFin)
            {
                return false;
            }
        }

        return true;
    }

    /**
     * Find a capable process then give it resources and finished it.
     *
     * @return `true` if successfully finished a task. `false` is no more
     * capable task
     */
    bool processNextCapableProc()
    {
        bool found = false;
        LL procCount = mAllocated.size();

        for (LL i = 0; i < procCount; ++i)
        {
            // if this proc already finished
            if (mFinished[i])
            {
                continue;
            }
            if (mAllocated[i] >= mMax[i])
            {
                // cout << "[Debug] Resources already satisfied" << endl;
                // cout << "Index: " << i << endl;
                // cout << "mAllocated: " << mAllocated[i] << endl;
                // cout << "mMax: " << mMax[i] << endl;
                // cout << "mNeed: " << mNeed[i] << endl;
                markFinished(i);
                // cout << "AvaiAfter: " << mTmpAvailable << endl;
                found = true;
            }
            // if could finished, mark it
            else if (mTmpAvailable >= mNeed[i])
            {
                // cout << "[Debug] Resources could be allocated" << endl;
                // cout << "Index: " << i << endl;
                // cout << "mAllocated: " << mAllocated[i] << endl;
                // cout << "mMax: " << mMax[i] << endl;
                // cout << "mNeed: " << mNeed[i] << endl;
                markFinished(i);
                // cout << "AvaiAfter: " << mTmpAvailable << endl;
                found = true;
            }
        }

        return found;
    }

    BankerRuntime &markFinished(LL idx)
    {
        if (mFinished[idx])
        {
            cout << "[Warning] Try to mark an already finished proc: " << idx << endl;
            return *this;
        }
        mFinished[idx] = true;
        mTmpAvailable = mTmpAvailable + mAllocated[idx];

        mSafeSequence.push_back(idx + 1);

        return *this;
    }

public:
    /**
     * Parameteraized constructor of BankerRuntime
     */
    BankerRuntime(
        cvecLL2r allocated,
        cvecLL2r max,
        cvecLLr available)
        : mAllocated(allocated),
          mMax(max),
          mAvailable(available),
          mFinished(max.size())
    {
        updateNeed();
    }

    /**
     * Copy constructor of BankerRuntime
     */
    BankerRuntime(const BankerRuntime &rt)
    {
        mAllocated = rt.mAllocated;
        mMax = rt.mMax;
        mAvailable = rt.mAvailable;
        updateNeed();
    }

    /**
     * Check if current runtime is deadlock free
     *
     * @return `true` if safe, `false` if unsafe
     */
    bool isSafe()
    {
        cout << "[Info][SafetyCheck]\tChecking system deadlock safety" << endl;
        mSafeSequence.clear();
        mTmpAvailable = mAvailable;
        mFinished = vecLL(mNeed.size(), 0);
        while (processNextCapableProc())
        {
        }
        bool isSafe = allFinished();
        cout << "[Info][SafetyCheck]\tSystem Safe: " << (isSafe ? "true" : "false") << endl;
        if (isSafe)
        {
            cout << "[Info][SafeSequence]\tSafe Sequence: " << mSafeSequence << endl;
        }

        return isSafe;
    }

    /**
     * Try to allocate a bunch of resources to a process
     *
     * @return `true` if allocation is safe, and update the runtime state
     * @return `false` if allocation is unsafe.
     */
    bool tryAllocate(LL idx, vecLL resVector)
    {
        cout << "[Info][TryAlloc]\tTry to allocate: " << resVector << " -> "
             << "proc: " << idx << endl;

        if (mAvailable < resVector)
        {
            cout << "[Info][AllocFailed]\tAllocation prerequisition test failed, insufficient system resources" << endl;
            return false;
        }
        if (mMax[idx] < mAllocated[idx] + resVector)
        {
            cout << "[Info][AllocFailed]\tAllocation prerequisition test failed, process has asked resources"
                 << " more than its max resources allegation" << endl;
            return false;
        }

        // create a sandbox copy of this instance
        BankerRuntime sandboxRt(*this);

        // pre-allocate and system safety check
        sandboxRt.mAvailable = sandboxRt.mAvailable - resVector;
        sandboxRt.mAllocated[idx] = sandboxRt.mAllocated[idx] + resVector;
        sandboxRt.updateNeed();
        bool isSafeAfterAllo = sandboxRt.isSafe();

        if (isSafeAfterAllo)
        {
            cout << "[Info][AllocFinished]\tResources allocation check passed, resources successfully allocated" << endl;
            mAvailable = mAvailable - resVector;
            mAllocated[idx] = mAllocated[idx] + resVector;
            updateNeed();
        }
        else
        {
            cout << "[Info][AllocFailed]\tAllocation test failed" << endl;
        }
        return isSafeAfterAllo;
    }

    friend std::ostream &operator<<(std::ostream &os, const BankerRuntime &rt);
};

std::ostream &operator<<(std::ostream &os, const BankerRuntime &rt)
{
    os << "-------------------------------------------------------" << endl;
    os << "Allocated             Max              Need" << endl;
    LL rowCount = rt.mAllocated.size();

    for (LL i = 0; i < rowCount; ++i)
    {
        os << rt.mAllocated[i] << "    " << rt.mMax[i] << "    " << rt.mNeed[i] << endl;
    }

    os << "Available: " << rt.mAvailable << endl;

    os << "-------------------------------------------------------";

    return os;
}

// main function
int main()
{
    vecLL2 alloc = {
        {0, 0, 1, 2},
        {1, 0, 0, 0},
        {1, 3, 5, 4},
        {0, 6, 3, 2},
        {0, 0, 1, 4},
    };

    vecLL2 max = {
        {0, 0, 1, 2},
        {1, 7, 5, 0},
        {2, 3, 5, 6},
        {0, 6, 5, 2},
        {0, 6, 5, 6},
    };

    // vecLL2 alloc = {
    //     {0, 0, 1, 2},
    //     {1, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {0, 6, 3, 2},
    //     {0, 0, 1, 4},
    // };

    // vecLL2 max = {
    //     {0, 0, 1, 2},
    //     {1, 7, 5, 0},
    //     {0, 0, 0, 2},
    //     {0, 6, 5, 2},
    //     {0, 6, 5, 6},
    // };

    vecLL avai = {1, 5, 2, 0};

    BankerRuntime rt(alloc, max, avai);
    rt.isSafe();

    rt.tryAllocate(1, {0, 4, 2, 0});
    cout << rt << endl;
    rt.tryAllocate(2, {1, 0, 0, 0});
    cout << rt << endl;
    rt.tryAllocate(4, {0, 5, 2, 0});
    cout << rt << endl;

    rt.isSafe();

    return 0;
}
