The following code try to simulate two process scheduling algorithm:

- Static Priority Scheduling Algorithm (PSA)
- Round Robin Algorithm (RR)
  - When `q=1`
  - When `q=4`

```cpp
// Auther: Yujia Zhou, E22214017, Anhui University
// Process Schedule Experiment Program

// include STL Lib
#include <iostream>
#include <vector>
#include <algorithm>

// using statement (some just for convenience lol)
using std::cin, std::cout, std::endl;
using std::min, std::max, std::sort;
using std::ostream;
using std::reference_wrapper;
using std::string;
using std::vector;
using LL = long long;

// Show personal info
void showPersonalCredit()
{
    cout << "周裕佳 E22214017 AHU" << endl;
}

// Job class, contains all necessary info of a job inside schedule algorithm
class Process
{
public:
    string mId;      // ID of this process
    LL mArriveTime;  // arrive time of this process
    LL mProcessTime; // required process time of this job
    LL mPriority = 0;

public:
    // constructor
    Process(string id, LL arriveTime, LL processTime, LL priority = 0)
        : mId(id),
          mArriveTime(arriveTime),
          mProcessTime(processTime),
          mPriority(priority) {}

    Process(const Process &job) = default;

    // if a job already arrive the system at a certain timestamp
    bool isArrived(const LL &currentTimestamp) const
    {
        return mArriveTime <= currentTimestamp;
    }

    // override << for Job class
    friend ostream &operator<<(ostream &os, const Process &job);
};

// override << for Job class
ostream &operator<<(ostream &os, const Process &job)
{
    os << job.mId << "\t" << job.mArriveTime << "\t" << job.mProcessTime << "\t"
       << job.mPriority;
    return os;
}

/**
 * Structure that stores runtime info about a job.
 *
 * Notice:
 * - Please call startProcess() before calling process()
 */
class ProcessRuntimeInfo
{
public:
    Process mProcess;    // related proc instance
    LL mStartTime = -1;  // process start time of this job
    LL mFinishTime = -1; // process finish time of this job
    LL mRestProcess;     // rest time needed to finish process

public:
    ProcessRuntimeInfo(const Process &job) : mProcess(job)
    {
        mRestProcess = mProcess.mProcessTime;
    }

    // get total response time
    LL getResponseTime() const
    {
        if (mFinishTime == -1)
        {
            cout << "[Error] Try to get response time of a non-finished "
                 << "JobRuntimeInfo instance"
                 << endl;
            return -1;
        }
        return (mFinishTime - mProcess.mArriveTime);
    }

    // get weighted response time
    double getWeightedResponseTime() const
    {
        LL responseTime = getResponseTime();
        if (responseTime < 0)
        {
            cout << "[Error] Could not get valid job response time" << endl;
            return -1;
        }
        return responseTime / double(mProcess.mProcessTime);
    }

    bool isArrived(const LL &currentTimestamp) const
    {
        return mProcess.isArrived(currentTimestamp);
    }

    bool isStart() const
    {
        return mStartTime > -1;
    }

    bool isFinished() const
    {
        return mRestProcess <= 0;
    }

    void startProcess(LL startTime)
    {
        mStartTime = startTime;
    }

    // process this job
    void process(LL currentTimestamp, LL processTime)
    {
        if (mStartTime == -1)
        {
            cout << "[Error] Please call JobRuntimeInfo::startProcess() "
                 << "before you call process()"
                 << endl;
            return;
        }

        if (isFinished())
        {
            cout << "[Warning] Calling process() on a already finished "
                 << "JobRuntimeInfo instance" << endl;
            mRestProcess -= processTime;
            return;
        }

        // if this time the process is finished
        if (mRestProcess - processTime <= 0)
        {
            mFinishTime = currentTimestamp + mRestProcess;
            mRestProcess -= processTime;
            if (mRestProcess < 0)
            {
                cout << "[Warning] mRestProcess < 0, "
                     << "which means CPU idle time occurred"
                     << endl;
            }
            return;
        }

        mRestProcess -= processTime;
        return;
    }

    // ovveride cout operator
    friend ostream &operator<<(ostream &os, const ProcessRuntimeInfo &rt);
};

ostream &operator<<(ostream &os, const ProcessRuntimeInfo &rt)
{
    os << rt.mProcess << "\t" << rt.mStartTime << "\t" << rt.mFinishTime << "\t"
       << rt.getResponseTime() << "\t" << rt.getWeightedResponseTime();
    return os;
}

/**
 * Schedule Model Base Class
 *
 * Usage:
 * - Initial one schedule base class instance
 * - call simulate()
 * - call showSimulateResult()
 *
 * Override:
 * - Generally you need to add a new method processNextTask()
 *   - Could use skipIdleTime(), processJob() provide in base class
 */
class ScheduleModelBase
{
public:
    const vector<Process> &mProcessList;
    vector<ProcessRuntimeInfo> mProcessRuntimeList;
    LL mCurrentTimeStamp = 0;

    // Initialize model, load jobs info, generate initial runtime
    ScheduleModelBase(const vector<Process> &processList)
        : mProcessList(processList),
          mCurrentTimeStamp(0)
    {
        mProcessRuntimeList.clear();
        for (const Process &proc : mProcessList)
        {
            mProcessRuntimeList.push_back(ProcessRuntimeInfo(proc));
        }
    }

    // check if all task finished
    bool allFinished()
    {
        for (const ProcessRuntimeInfo &job : mProcessRuntimeList)
        {
            if (!job.isFinished())
            {
                return false;
            }
        }

        return true;
    }

    // aglin timestamp until at least one job is arrived
    void skipIdleTime()
    {
        LL earliestArriveTime = -1;
        for (const ProcessRuntimeInfo &rt : mProcessRuntimeList)
        {
            if (rt.isFinished())
            {
                continue;
            }
            if (rt.isStart())
            {
                return;
            }
            if (rt.isArrived(mCurrentTimeStamp))
            {
                return;
            }
            if (earliestArriveTime = -1)
            {
                earliestArriveTime = rt.mProcess.mArriveTime;
                continue;
            }
            earliestArriveTime = min(earliestArriveTime, rt.mProcess.mArriveTime);
        }

        if (earliestArriveTime > -1 && earliestArriveTime > mCurrentTimeStamp)
        {
            mCurrentTimeStamp = earliestArriveTime;
        }
    }

    // process a specified job
    void processJob(ProcessRuntimeInfo &processRuntime, LL processTime)
    {
        // align timestamp if needed
        skipIdleTime();
        // if jobRuntime not start, start it
        if (!processRuntime.isStart())
        {
            processRuntime.startProcess(mCurrentTimeStamp);
        }
        processRuntime.process(mCurrentTimeStamp, processTime);
        mCurrentTimeStamp += processTime;

        return;
    }

    // Show the result of simulation on this model
    // Notice:
    // You must first call simulate() before showing the result
    void showSimulateResult()
    {
        cout << "------------------------------------------------------------------------" << endl;
        const char *header = "ID\tArrive\tProcess\tPrior\tBegin\tFin\tResp\tWght Resp\n";
        cout << header;
        for (const ProcessRuntimeInfo &runtime : mProcessRuntimeList)
        {
            cout << runtime << endl;
        }

        // calculate avg process time
        LL totalProcessTime = 0;
        double totalWeightedProcessTime = 0;

        for (const ProcessRuntimeInfo &rt : mProcessRuntimeList)
        {
            totalProcessTime += rt.getResponseTime();
            totalWeightedProcessTime += rt.getWeightedResponseTime();
        }
        LL size = mProcessRuntimeList.size();

        cout << "Avg Process Time: " << totalProcessTime / double(size)
             << endl;
        cout << "Avg Weighted Process Time: " << totalWeightedProcessTime / size
             << endl;

        cout << "------------------------------------------------------------------------" << endl;
        return;
    }

    // virtual function to start simulate of this algorithm
    // acutally here it's ok to not mark this function as virtual
    // since we don't access this function polymorphically
    virtual void simulate()
    {
        cout << "[Error] [Override Needed] Sub class need to "
             << "override this method" << endl;
        return;
    }
};

class PriorityModel : public ScheduleModelBase
{
private:
    void processNext()
    {
        skipIdleTime();

        LL nextIdx = -1;
        LL size = mProcessRuntimeList.size();

        bool found = false;

        for (LL i = 0; i < size; ++i)
        {
            const ProcessRuntimeInfo &rt = mProcessRuntimeList[i];
            if (!rt.isArrived(mCurrentTimeStamp))
            {
                continue;
            }
            if (rt.isFinished())
            {
                continue;
            }
            if (found == false)
            {
                nextIdx = i;
                found = true;
                continue;
            }
            if (rt.mProcess.mPriority > mProcessRuntimeList[nextIdx].mProcess.mPriority)
            {
                nextIdx = i;
            }
        }

        if (found == false)
        {
            return;
        }

        ProcessRuntimeInfo &nextRt = mProcessRuntimeList[nextIdx];

        processJob(nextRt, max(LL(0), nextRt.mRestProcess));
    }

public:
    using ScheduleModelBase::ScheduleModelBase;

    void simulate()
    {
        while (!allFinished())
        {
            processNext();
        }
    }
};

class RRScheduleModel : public ScheduleModelBase
{
private:
    vector<std::reference_wrapper<ProcessRuntimeInfo>> mReadyList;

    // The time slice length of the CPU
    LL mTimeSlice = 1;

    bool mScheduleInMidOfSlice = false;

    bool inReadyList(const ProcessRuntimeInfo &rt)
    {
        for (auto &rtInList : mReadyList)
        {
            if (rtInList.get().mProcess.mId == rt.mProcess.mId)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * Insert the arrived process to ready list
     */
    void insertNewlyArrivedProc()
    {
        vector<std::reference_wrapper<ProcessRuntimeInfo>> waitForInsertList;
        for (auto &proc : mProcessRuntimeList)
        {
            if (!proc.mProcess.isArrived(mCurrentTimeStamp))
            {
                continue;
            }
            if (proc.isFinished())
            {
                continue;
            }
            if (proc.isStart())
            {
                continue;
            }
            if (inReadyList(proc))
            {
                continue;
            }

            waitForInsertList.push_back(proc);
        }

        if (waitForInsertList.empty())
        {
            return;
        }

        // sort wait for insert list by the arrive time
        sort(
            waitForInsertList.begin(),
            waitForInsertList.end(),
            [](ProcessRuntimeInfo &proc1, ProcessRuntimeInfo &proc2)
            {
                return proc1.mProcess.mArriveTime < proc2.mProcess.mArriveTime;
            });

        // insert the wait list to the end of mReadyList
        mReadyList.insert(mReadyList.begin(), waitForInsertList.begin(), waitForInsertList.end());
    }

    // simply put the back element in the ready list to the first place
    void cyclingReadyList()
    {
        if (mReadyList.empty())
        {
            return;
        }

        std::rotate(mReadyList.begin(), mReadyList.begin() + 1, mReadyList.end());

        if (mReadyList.back().get().isFinished())
        {
            cout << "> [DEBUG][Fin] Process Finished, PID: " << mReadyList.back().get().mProcess.mId << endl;
            mReadyList.pop_back();
        }
    }

    void processNextJob()
    {
        skipIdleTime();
        insertNewlyArrivedProc();

        // No task
        if (mReadyList.empty())
        {
            return;
        }

        // get next process -> process it -> rounding
        ProcessRuntimeInfo &nextProcess = mReadyList.front();
        LL realProcTime = mTimeSlice;
        if (mScheduleInMidOfSlice)
        {
            realProcTime = min(realProcTime, nextProcess.mRestProcess);
        }
        processJob(nextProcess, realProcTime);
        cout << "[DEBUG][SliceInfo] ";
        cout << "PID: " << nextProcess.mProcess.mId << "   ";
        cout << "Rest: " << nextProcess.mRestProcess;
        cout << endl;
        cyclingReadyList();
    }

public:
    RRScheduleModel(vector<Process> processList)
        : ScheduleModelBase(processList) {}

    RRScheduleModel &setTimeSlice(LL slice)
    {
        mTimeSlice = slice;
        return *this;
    }

    RRScheduleModel &scheduleInMidOfSlice(bool isAllow)
    {
        mScheduleInMidOfSlice = isAllow;
        return *this;
    }

    void simulate()
    {
        while (!allFinished())
        {
            processNextJob();
        }
    }
};

int main()
{
    showPersonalCredit();

    // priority job list
    vector<Process> procListPriority = {
        // PID, Arrive, Process, Prior
        Process("A", 0, 4, 1),
        Process("B", 1, 3, 2),
        Process("C", 2, 4, 3),
        Process("D", 3, 2, 4),
        Process("E", 4, 4, 5),
    };

    // test job list
    vector<Process> procList = {
        // PID, Arrive, Process, Prior (default to 1)
        Process("A", 0, 4),
        Process("B", 1, 3),
        Process("C", 2, 4),
        Process("D", 3, 2),
        Process("E", 4, 4),
    };

    // Priority
    PriorityModel priorityModel(procListPriority);
    priorityModel.simulate();
    priorityModel.showSimulateResult();

    // RR with slice 1
    RRScheduleModel rrModel(procList);
    rrModel
        .setTimeSlice(1)
        .simulate();
    rrModel.showSimulateResult();

    // RR with slice 1
    RRScheduleModel rrModel4(procList);
    rrModel4
        .setTimeSlice(4)
        .scheduleInMidOfSlice(true)
        .simulate();
    rrModel4.showSimulateResult();

    return 0;
}
```