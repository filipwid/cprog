#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <cstring>
#include "WaterManager.h"
#include "Gnu.h"

using namespace std;

WaterManager watermanager;
unordered_map<thread::id, string> animalMap;
bool trace = false;


Gnu::Gnu(int id) {
    this -> id = id;
}

void Gnu::operator()()  {
    int count = 0;
    bool loop = true;
    while (loop) {
        this_thread::sleep_for(chrono::seconds((rand() % 4) +2));
        if (trace) cout << *this << " is thirsty " << endl;
        watermanager.gnuEnters();

        this_thread::sleep_for(chrono::seconds((rand() % 2) +2));
        if (trace) cout << *this << " finished drinking and exits the water cave" << endl;
        watermanager.gnuLeaves();
        if (count == 2) loop = false;
        count++;
    }
}


ostream& operator<<(ostream & os, const Gnu & g) {
    os << "Gnu nr " << g.id;
    return os;
}

void WaterManager::hyenaEnters() {
    unique_lock<mutex> SOMELOCK(m);
    CONDITIONVAR.wait(SOMELOCK, [this] {return gnusInside == 0;});
    hyenasInside += 1;
    if (trace) cout << animalMap[this_thread::get_id()] << " enters the watering hole \t hyenas = " << hyenasInside << "\t gnu = " << gnusInside << endl;
};

void WaterManager::hyenaLeaves() {
    m.lock();
    hyenasInside -= 1;
    CONDITIONVAR.notify_all();
    if (trace) cout << animalMap[this_thread::get_id()] << " leaves the watering hole \t hyenas = " << hyenasInside << "\t gnu = " << gnusInside << endl;
    m.unlock();
};

void WaterManager::gnuEnters() {
    unique_lock<mutex> SOMELOCK(m);
    CONDITIONVAR.wait(SOMELOCK, [this] {return hyenasInside == 0;});
    gnusInside += 1;
    if (trace) cout << "A gnu enters the water cave \t hyenas = " << hyenasInside << "\t gnu = " << gnusInside << endl;

};

void WaterManager::gnuLeaves() {
    m.lock();
    gnusInside -= 1;
    CONDITIONVAR.notify_all();
    //if (trace) cout << "g "<< " leaves the watering hole \t hyenas = " << hyenasInside << "\t gnu = " << gnusInside << endl;
    m.unlock();

};


/*void gnu() {
    int count = 0;
    bool loop = true;
   while (loop) {
     this_thread::sleep_for(chrono::seconds(1));
     cout << animalMap[this_thread::get_id()] << " is thirsty" << endl;
	 watermanager.gnuEnters();
     this_thread::sleep_for(chrono::seconds(1));
	 watermanager.gnuLeaves();
     if (count == 2) loop = false;
     count++;
   }
}*/

void hyena() {
    int count = 0;
    bool loop = true;
    while (loop) {
        this_thread::sleep_for(chrono::seconds((rand() % 4) +2));
        if (trace) cout << animalMap[this_thread::get_id()] << " is thirsty" << endl;
    	watermanager.hyenaEnters();
        this_thread::sleep_for(chrono::seconds((rand() % 2) +2));
    	watermanager.hyenaLeaves();

        if (count == 2) loop = false;
        count++;
    }
}
int main(int argc, char *argv[]){
    if (argc == 2) {
        if (strcmp(argv[0], "trace") == 0){
            trace = true;
        }
    }
    srand(time(NULL));
    int nrHyenas = 2;
    int nrGnus = 2;
    vector<thread> threadvec;
    for (int i = 0; i < nrGnus; i++) {
        Gnu g = Gnu(i+1);
        function<void(void)> threadjob = g;
        threadvec.push_back(thread(threadjob));
        //animalMap[threadvec.back().get_id()] = "Gnu nr " + to_string(i+1);
    }
    for (int i = 0; i < nrHyenas; i++){
      threadvec.push_back(thread(hyena));
      animalMap[threadvec.back().get_id()] = "Hyena nr " + to_string(i+1);
    }

    for (auto& thread : threadvec)
	   thread.join();

    return 0;
}
