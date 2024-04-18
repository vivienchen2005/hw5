#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper (DailySchedule& sched, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, size_t row, size_t col, vector<size_t>& numShifts);
bool DailyScheduleComplete(DailySchedule& sched);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    sched.resize(avail.size(), vector<Worker_T>());
    vector<size_t> numShifts(avail[0].size(), 0);
    return scheduleHelper(sched, avail, dailyNeed, maxShifts, 0, 0, numShifts);
}

bool scheduleHelper (DailySchedule& sched, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, size_t row, size_t col, vector<size_t>& numShifts) {
    if (row == avail.size()) {
        return true;
    }
    
    else {
        for (size_t i = col; i < avail[0].size(); i++) {
            if (avail[row][i] && numShifts[i] < maxShifts) {
                sched[row].push_back(i);
                //update numshifts
                numShifts[i]++;
                if (sched[row].size() == dailyNeed) { //if the row is filled
                    if (scheduleHelper(sched, avail, dailyNeed, maxShifts, row+1, 0, numShifts)) { return true; }
                }
                bool status = scheduleHelper(sched, avail, dailyNeed, maxShifts, row, i+1, numShifts);
                if (status) { return true; }
                //reset
                sched[row].pop_back();
                numShifts[i]--;
            }
        }
        return false;
    }
    
}

