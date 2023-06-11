#include <iostream>
using namespace std;
#include <cstring>
#include "Matrix.h"


int main() {

  /*Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
  Matrix<int> m2 {1,3,5,7,9,11,13,15,17};
  Matrix<int> m3 = m1;
  m2 = m1;*/

  Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
  m1.remove_column(1);
  std::cout << m1(1,0) <<" " << m1(1,2);

  return 0;
}
