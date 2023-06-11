//
// DD1388 - Lab 6
//

#include <condition_variable>
#include <mutex>
#include <atomic>

using namespace std;

#ifndef WATERMANAGER_H
#define WATERMANAGER_H

class WaterManager {
public:
    condition_variable CONDITIONVAR;
    mutex m;
    atomic<int> hyenasInside = {0};
    atomic<int> gnusInside = {0};

    void hyenaEnters();
    void gnuEnters();
    void hyenaLeaves();
    void gnuLeaves();
};

#endif
