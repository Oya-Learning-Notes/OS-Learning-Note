#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using std::cout, std::endl;
using std::vector;
using std::sort;
using std::map;

using LL = long long;
using vecLL = vector<LL>;
using cvecLLr = const vecLL &;
using mapLLLL = map<LL, LL>;


/**
 * Base class of all replacement algorithm
 * 
 * Extend Guide:
 * - Call base class constructor to set mCapacity.
 * - Override request(). simulate() will automatically call request().
 * - If necessary, you could override simulate() too.
 * 
 * request() Override Guide
 * - Update mRequestTime in request().
 * - If inMemory(), do sth if needed then return -1.
 * - call loadPage(), if function return true, do sth if needed then return -1.
 * - Find page that should be replaced.
 * - Call replacePage().
 * - Return the page that be selected to replace.
 */
class ReplaceAlgorithm{
    private:
    /**
     * The maximum page that could be stored in the memory.
     */
    LL mCapacity;

    /**
     * Count of current request time.
     */
    LL mRequestTime = 0;

    /**
     * Store the index of pages that been loaded into CPU.
     */
    vecLL mMemPageList;

    /**
     * Check if a page are loaded into memory.
     */
    bool inMemory(LL pageIndex){
        for(const auto& index : mMemPageList){
            if(index == pageIndex){
                return true;
            }
        }
        return false;
    }

    bool isFull(){
        return mMemPageList.size() >= mCapacity;
    }

    /**
     * Load a page into memory. This require memory not full.
     * 
     * If failed to load, return false.
     */
    bool loadPage(LL pageIndex){
        if(isFull()){
            cout << "[MemoryFull] Try to load page into a full memory" << endl;
            return false;
        }
        mMemPageList.push_back(pageIndex);
        return true;
    }

    void replacePage(LL index, LL replacedIndex){
        if(!isFull()){
            loadPage(index);
            return;
        }
        for(auto & memIndex : mMemPageList){
            if(memIndex == replacedIndex){
                memIndex = index;
                return;
            }
        }
        cout << "[Error] Try to replaced a page that not loaded into memory" << endl;
        exit(-1);
    }

    public:

    /**
     * Basic constructor that initialize the capacity.
     */
    ReplaceAlgorithm(LL capacity) : mCapacity(capacity) {}

    /**
     * Simulate the program requesting a page.
     * 
     * Returns the page that has been replaced. If no page replaced, 
     * return -1.
     */
    virtual LL request(LL requestIndex){
        cout << "[OverrideNeeded] request() should be overrided by sub-class"
        << endl;
        return -1;
    }

    /**
     * Process a requesting sequence by call request() one by one.
     */
    virtual void simulate(cvecLLr requestSequence){
        LL replacedPage = -1;
        for(const auto & requestIndex : requestSequence){
            replacedPage = request(requestIndex
            if(replacedPage != -1){
                cout << "[Replaced] "
                << replacedPage << " <- " << requestIndex << "  "
                << "(RequestCount=" << mRequestTime << ")" << endl;
            }
        }
        return;
    }
};


class FIFOAlgorithm : public ReplaceAlgorithm {
    private:
    mapLLLL mTimeStampMap;

    /**
     * Override base class request() method.
     */
    LL request(LL requestPage){
        // update request time stamp.
        ++mRequestTime;

        if inMemory(requestPage){
            return -1;
        }

        // Try directly load
        if(loadPage(requestPage)){
            mTimeStampMap[requestPage] = mRequestTime;
            return -1;
        }

        // find the first-in page in memory.
        LL mostSoonTime = mTimeStampMap + 1;
        LL selectedReplacePage = -1;

        for(const auto& inMemIndex : mMemPageList){
            if(mTimeStampMap[inMemIndex] < mostSoonTime){
                // assert timestamp not zero
                if(mTimeStampMap[inMemIndex] == 0){
                    cout << "[WrongTimeStamp] "
                    << "Load time of a page is impossible to be 0" << endl;
                }
                selectedReplacePage = inMemIndex;
            }
        }

        // assert page founded
        if(selectedReplacePage == -1){
            cout << "[Error] Coult not find page to be replaced" << endl;
            exit(-1);
        }

        replacePage(requestPage, selectedReplacePage);
        mTimeStampMap[requestPage] = mRequestTime;

        return selectedReplacePage;
    }
};

int main(){
    vecLL requestSequence = {1, 2, 3};
    ;
}