// mytest.h
#include <cxxtest/TestSuite.h>
#include "Matrix.h"
#include <fstream>
#include <algorithm>
class MyTestSuite : public CxxTest::TestSuite
{
public:
  // Constructors
  void test_constructors ( void ){
    // Default constructor
    Matrix<int> m1;
    TS_ASSERT(m1.rows() == 0);
    TS_ASSERT(m1.cols() == 0);

    // Dimensional constructor
    Matrix<int> m2(6);
    TS_ASSERT(m2.rows() == 6);
    TS_ASSERT(m2.cols() == 6);
    TS_ASSERT(m2(0,0) == 0);
    TS_ASSERT(m2(1,2) == 0);
    TS_ASSERT(m2(2,1) == 0);

    // Two input constructor
    Matrix<int> m3(6,3);
    TS_ASSERT(m3.rows() == 6);
    TS_ASSERT(m3.cols() == 3);
    TS_ASSERT(m3(0,0) == 0);
    TS_ASSERT(m3(1,2) == 0);
    TS_ASSERT(m3(2,1) == 0);

    // initializer_list constructor
    Matrix<int> m4 {1,2,3,4,5,6,7,8,9};   // Is there a way to test if the actual constructor call can throw?
    TS_ASSERT(m4.rows() == 3);
    TS_ASSERT(m4.cols() == 3);
    TS_ASSERT(m4(0,0) == 1);
    TS_ASSERT(m4(1,2) == 6);
    TS_ASSERT(m4(2,1) == 8);

    // Copy constructor
    Matrix<int> m5(m4);
    TS_ASSERT(m5.rows() == 3);
    TS_ASSERT(m5.cols() == 3);
    TS_ASSERT(m5(0,0) == 1);
    TS_ASSERT(m5(1,2) == 6);
    TS_ASSERT(m5(2,1) == 8);

    m5(0,0) = 10;                         // Check that the copied from does not change
    TS_ASSERT(m5(0,0) == 10);
    TS_ASSERT(m4(0,0) == 1);

    // Move constructor
    Matrix<int> m6 = std::move(m4);
    TS_ASSERT(m6.rows() == 3);
    TS_ASSERT(m6.cols() == 3);
    TS_ASSERT(m6(0,0) == 1);
    TS_ASSERT(m6(1,2) == 6);
    TS_ASSERT(m6(2,1) == 8);

  }

  // Accessors
  void test_accessors ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    TS_ASSERT(m1.rows() == 3);
    TS_ASSERT(m1.cols() == 3);
    TS_ASSERT(m1(1,2) == 6);
    TS_ASSERT_THROWS(m1(4,4), std::out_of_range);
  }

  // Operators
  void test_copy_operator ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    Matrix<int> m2 {1,3,5,7};
    Matrix<int> m3 = m1;

    TS_ASSERT(m3.rows() == 3);
    TS_ASSERT(m3.cols() == 3);

    m2 = m3;
    TS_ASSERT(m2.rows() == 3);
    TS_ASSERT(m2.cols() == 3);
  }

  void test_move_operator ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    Matrix<int> m2 {1,3,5,7,9,11,13,15,17};
    Matrix<int> m3 = std::move(m1);

    TS_ASSERT(m1.rows() == 0);
    TS_ASSERT(m1.cols() == 0);
    m2 = std::move(m1);

  }

  void test_subtraction ( void ){
    Matrix<int> err {1,2,3,4};
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    Matrix<int> m2 {1,3,5,7,9,11,13,15,17};
    Matrix<int> m3;

    TS_ASSERT_THROWS(m1-err, std::out_of_range);

    m3 = m1 - m2;
    TS_ASSERT(m3(0,0) == 0);
    TS_ASSERT(m3(1,1) == -4);
    TS_ASSERT(m3(1,2) == -5);

    TS_ASSERT(m1(0,0) == 1);
    TS_ASSERT(m1(1,1) == 5);

    TS_ASSERT(m2(0,0) == 1);
    TS_ASSERT(m2(1,1) == 9);

    m1 -= m1;
    TS_ASSERT(m1(0,0) == 0);
    TS_ASSERT(m1(1,1) == 0);

  }

  void test_addition ( void ){
    Matrix<int> err {1,2,3,4};
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    Matrix<int> m2 {1,3,5,7,9,11,13,15,17};
    Matrix<int> m3;

    TS_ASSERT_THROWS(m1+err, std::out_of_range);

    m3 = m1 + m2;
    TS_ASSERT(m3(0,0) == 2);
    TS_ASSERT(m3(1,1) == 14);
    TS_ASSERT(m3(1,2) == 17);

    TS_ASSERT(m1(0,0) == 1);
    TS_ASSERT(m1(1,1) == 5);

    TS_ASSERT(m2(0,0) == 1);
    TS_ASSERT(m2(1,1) == 9);

    m1 += m1;
    TS_ASSERT(m1(0,0) == 2);
    TS_ASSERT(m1(1,1) == 10);

  }

  void test_multiplication ( void ){
    Matrix<int> err {1,2,3,4};
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    Matrix<int> m2 {1,3,5,7,9,11,13,15,17};
    Matrix<int> m3;
    int expected [9] = {54,66,78,117,147,177,180,228,276};

    TS_ASSERT_THROWS(m1*err, std::out_of_range);

    m3 = m1 * m2;
    for (int i = 0; i<3; i++){
      for (int j = 0; j<3; j++){
        TS_ASSERT(m3(i,j) == expected[3*i+j]);
      }
    }

    TS_ASSERT(m1(0,0) == 1);
    TS_ASSERT(m1(1,1) == 5);

    TS_ASSERT(m2(0,0) == 1);
    TS_ASSERT(m2(1,1) == 9);

    m1 *= m1;
    TS_ASSERT(m1(0,0) == 30);
    TS_ASSERT(m1(1,2) == 96);
    TS_ASSERT(m1(2,1) == 126);
  }

  void test_operator_chaining ( void ){
    Matrix<int> m1 {1,2,3,4};
    Matrix<int> m2 {1,3,5,7};
    Matrix<int> m3 {1,4,7,11};
    Matrix<int> m4;

    m4 = m1 + m2 + m3;
    TS_ASSERT(m4(0,0) == 3);
    TS_ASSERT(m4(1,0) == 15);

    m4 = m1 - m2 + m3;
    TS_ASSERT(m4(0,0) == 1);
    TS_ASSERT(m4(1,0) == 5);
  }

  // Methods
  void test_reset ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    TS_ASSERT(m1(0,0) == 1);
    TS_ASSERT(m1(1,1) == 5);

    m1.reset();
    TS_ASSERT(m1(0,0) == 0);
    TS_ASSERT(m1(1,1) == 0);

  }

  void test_insert_row ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    m1.insert_row(1);
    TS_ASSERT(m1(1,1) == 0);
    TS_ASSERT(m1(2,1) == 5);
    TS_ASSERT(m1(3,1) == 8);

  }

  void test_append_row ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    m1.append_row(1);
    TS_ASSERT(m1(1,1) == 5);
    TS_ASSERT(m1(2,1) == 0);
    TS_ASSERT(m1(3,1) == 8);
  }

  void test_remove_row ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    m1.remove_row(1);
    TS_ASSERT(m1(0,1) == 2);
    TS_ASSERT(m1(1,1) == 8);
    TS_ASSERT(m1(1,2) == 9);
  }

  void test_insert_col ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    m1.insert_column(1);
    TS_ASSERT(m1(1,1) == 0);
    TS_ASSERT(m1(1,2) == 5);
    TS_ASSERT(m1(1,3) == 6);
  }

  void test_append_col ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    m1.append_column(1);
    TS_ASSERT(m1(1,1) == 5);
    TS_ASSERT(m1(1,2) == 0);
    TS_ASSERT(m1(1,3) == 6);
  }

  void test_remove_col ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    m1.remove_column(1);
    TS_ASSERT(m1(1,0) == 4);
    TS_ASSERT(m1(1,1) == 6);
    TS_ASSERT(m1(2,1) == 9);
  }

  void test_begin ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    TS_ASSERT(*m1.begin() == 1);
  }

  void test_end ( void ){
    Matrix<int> m1 {9,8,7,6,5,4,3,2,1};
    TS_ASSERT(*m1.end() == 1);

    /*
    std::sort(m1.begin(),m1.end());
    std::cout <<"\t" <<m1(0,0) <<"\t"<< m1(0,1) <<"\t";
    */
  }

  void test_ostream ( void ){
    Matrix<int> m1 {1,2,3,4,5,6,7,8,9};
    std::ofstream outfile ("writetofiletest.txt");
    outfile << m1;
    outfile.close();
  }

  void test_istream ( void ){
    Matrix<int> m1 {1,2,8,9};
    std::ifstream infile ("writetofiletest.txt");
    infile >> m1;
    TS_ASSERT(m1(1,1) == 5);
    infile.close();
  }

  void test_identity ( void ){
    Matrix<int> m1 = identity<int>(4);
    TS_ASSERT(m1(0,0) == 1);
    TS_ASSERT(m1(1,1) == 1);
    TS_ASSERT(m1(2,2) == 1);
    TS_ASSERT(m1(1,0) == 0);
    TS_ASSERT(m1(0,2) == 0);
  }
};
