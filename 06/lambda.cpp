#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;


void printvec(vector<int> v){
  for (auto x : v) { cout << x << " ";};
  cout << endl;
}

int main() {
    vector<int> v = {1, 3, 4, 5, 6, 7, 8, 9};
    int OUTSIDEDATA = 223;
    cout << "vector v:" << endl;
    printvec(v);

    cout << "Odd numbers in v:" << endl;
    for_each(v.cbegin(), v.cend(), [](int n) {if(n%2 == 1) cout << n << " ";});
    cout << endl;

    for_each(v.begin(), v.end(), [](int &n) {if(n%2==1) n=n*2; });
    cout << "Multiplied v:" << endl;
    printvec(v);

    for_each(v.begin(), v.end(), [v](int &n) {n=n+v.size(); });
    cout << "Added vector size:" << endl;
    printvec(v);

    cout << OUTSIDEDATA << endl;
    auto captureChange =  [ & OUTSIDEDATA ](int x) {OUTSIDEDATA = OUTSIDEDATA + x;};
    captureChange(112);
    cout << OUTSIDEDATA;

    return 0;
}
