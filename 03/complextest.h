#include <cxxtest/TestSuite.h>
#include "Complex.h"
#include <fstream>
#include <algorithm>
class MyTestSuite : public CxxTest::TestSuite
{
public:
  // Constructors
  void test_default_constructor ( void ){
      Complex c;
      TS_ASSERT(c.real() == 0);
      TS_ASSERT(c.imag() == 0);
  }

  void test_one_parameter_constructor ( void ){
      Complex c1 = 5;
      TS_ASSERT(c1.real() == 5);
      TS_ASSERT(c1.imag() == 0);

      Complex c2 = 7.15;
      TS_ASSERT(c2.real() == 7.15);
      TS_ASSERT(c2.imag() == 0);

      Complex c3 = -5;
      TS_ASSERT(c3.real() == -5);
      TS_ASSERT(c3.imag() == 0);

      Complex c4 = -7.15;
      TS_ASSERT(c4.real() == -7.15);
      TS_ASSERT(c4.imag() == 0);
  }

  void test_two_parameter_constructor ( void ){
      Complex c1(6, 2);
      TS_ASSERT(c1.real() == 6);
      TS_ASSERT(c1.imag() == 2);

      Complex c2(6.15, 2.37);
      TS_ASSERT(c2.real() == 6.15);
      TS_ASSERT(c2.imag() == 2.37);

      Complex c3(-6, -2);
      TS_ASSERT(c3.real() == -6);
      TS_ASSERT(c3.imag() == -2);

      Complex c4(-6.15, -2.37);
      TS_ASSERT(c4.real() == -6.15);
      TS_ASSERT(c4.imag() == -2.37);
  }

  void test_literal_constructor ( void ){
      Complex c1 = 3 + 5_i;
      TS_ASSERT(c1.real() == 3);
      TS_ASSERT(c1.imag() == 5);

      Complex c2 = 3.67 + 5.94_i;
      TS_ASSERT(c2.real() == 3.67);
      TS_ASSERT(c2.imag() == 5.94);

      Complex c3 = -3 - 5_i;
      TS_ASSERT(c3.real() == -3);
      TS_ASSERT(c3.imag() == -5);

      Complex c4 = -3.67 - 5.94_i;
      TS_ASSERT(c4.real() == -3.67);
      TS_ASSERT(c4.imag() == -5.94);

      Complex c5 = 5.94_i;
      TS_ASSERT(c5.real() == 0);
      TS_ASSERT(c5.imag() == 5.94);
  }

  void test_copy_constructor ( void ){
      Complex c1(6, 2);
      Complex c2(c1);
      TS_ASSERT(c2.real() == c1.real());
      TS_ASSERT(c2.imag() == c1.imag());

      Complex c3(6.15, 2.37);
      Complex c4(c3);
      TS_ASSERT(c4.real() == c3.real());
      TS_ASSERT(c4.imag() == c3.imag());

      Complex c5(-6, -2);
      Complex c6(c5);
      TS_ASSERT(c6.real() == c5.real());
      TS_ASSERT(c6.imag() == c5.imag());

      Complex c7(-6.15, -2.37);
      Complex c8(c7);
      TS_ASSERT(c8.real() == c7.real());
      TS_ASSERT(c8.imag() == c7.imag());
  }

  void test_copy_assignement ( void ){
      Complex c1(6, 2);
      Complex c2;
      c2 = c1;
      TS_ASSERT(c2.real() == c1.real());
      TS_ASSERT(c2.imag() == c1.imag());

      Complex c3(6.15, 2.37);
      Complex c4;
      c4 = c3;
      TS_ASSERT(c4.real() == c3.real());
      TS_ASSERT(c4.imag() == c3.imag());

      Complex c5(-6, -2);
      Complex c6;
      c6 = c5;
      TS_ASSERT(c6.real() == c5.real());
      TS_ASSERT(c6.imag() == c5.imag());

      Complex c7(-6.15, -2.37);
      Complex c8;
      c8 = c7;
      TS_ASSERT(c8.real() == c7.real());
      TS_ASSERT(c8.imag() == c7.imag());
  }

  // Accessors
  void test_accessors ( void ){
      Complex c1(6, 2);
      double c1_real = c1.real();
      double c1_imag = c1.imag();
      TS_ASSERT(c1_real == 6);
      TS_ASSERT(c1_imag == 2);

      Complex c2(6.15, 2.37);
      double c2_real = c2.real();
      double c2_imag = c2.imag();
      TS_ASSERT(c2_real == 6.15);
      TS_ASSERT(c2_imag == 2.37);

      Complex c3(-6, -2);
      double c3_real = c3.real();
      double c3_imag = c3.imag();
      TS_ASSERT(c3_real == -6);
      TS_ASSERT(c3_imag == -2);

      Complex c4(-6.15, -2.37);
      double c4_real = c4.real();
      double c4_imag = c4.imag();
      TS_ASSERT(c4_real == -6.15);
      TS_ASSERT(c4_imag == -2.37);
  }

  // Compound operators
  // c1 += c2
  void test_compound_addition ( void ){
      Complex c1(6, 2);
      Complex c2(2.33, 3.45);
      double expected_real = c1.real() + c2.real();
      double expected_imag = c1.imag() + c2.imag();
      c1 += c2;
      TS_ASSERT(c1.real() == expected_real);
      TS_ASSERT(c1.imag() == expected_imag);

      Complex c3(-6, -2);
      Complex c4(-2.33, -3.45);
      expected_real = c3.real() + c4.real();
      expected_imag = c3.imag() + c4.imag();
      c3 += c4;
      TS_ASSERT(c3.real() == expected_real);
      TS_ASSERT(c3.imag() == expected_imag);
  }

  // c1 += scalar
  void test_compound_addition_scalar ( void ){
      Complex c1(6, 2);
      double scalar = 4.13;
      double expected_real = c1.real() + scalar;
      double expected_imag = c1.imag();
      c1 += scalar;
      TS_ASSERT(c1.real() == expected_real);
      TS_ASSERT(c1.imag() == expected_imag);

      Complex c2(-6, -2);
      scalar = -4.13;
      expected_real = c2.real() + scalar;
      expected_imag = c2.imag();
      c2 += scalar;
      TS_ASSERT(c2.real() == expected_real);
      TS_ASSERT(c2.imag() == expected_imag);
  }

  // c1 -= c2
  void test_compound_subtraction ( void ){
      Complex c1(6, 2);
      Complex c2(2.33, 3.45);
      double expected_real = c1.real() - c2.real();
      double expected_imag = c1.imag() - c2.imag();
      c1 -= c2;
      TS_ASSERT(c1.real() == expected_real);
      TS_ASSERT(c1.imag() == expected_imag);

      Complex c3(-6, -2);
      Complex c4(-2.33, -3.45);
      expected_real = c3.real() - c4.real();
      expected_imag = c3.imag() - c4.imag();
      c3 -= c4;
      TS_ASSERT(c3.real() == expected_real);
      TS_ASSERT(c3.imag() == expected_imag);
  }

  // c1 -= scalar
  void test_compound_subtraction_scalar ( void ){
      Complex c1(6, 2);
      double scalar = 4.13;
      double expected_real = c1.real() - scalar;
      double expected_imag = c1.imag();
      c1 -= scalar;
      TS_ASSERT(c1.real() == expected_real);
      TS_ASSERT(c1.imag() == expected_imag);

      Complex c2(-6, -2);
      scalar = -4.13;
      expected_real = c2.real() - scalar;
      expected_imag = c2.imag();
      c2 -= scalar;
      TS_ASSERT(c2.real() == expected_real);
      TS_ASSERT(c2.imag() == expected_imag);
  }

  // c1 /= c2
  // https://www.codegrepper.com/code-examples/cpp/double+decimal+places+c%2B%2B
  void test_compound_division ( void ){
      Complex c1(6, 2);
      Complex c2(2, 3);
      double expected_real = 1.385;
      double expected_imag = -1.077;
      c1 /= c2;
      TS_ASSERT(round(c1.real()*1000.0)/1000.0 == expected_real);
      TS_ASSERT(round(c1.imag()*1000.0)/1000.0 == expected_imag);

      Complex c3(6, 2);
      Complex c4(-2.33, -3.45);
      expected_real = -1.205;
      expected_imag = 0.925;
      c3 /= c4;
      TS_ASSERT(round(c3.real()*1000.0)/1000.0 == expected_real);
      TS_ASSERT(round(c3.imag()*1000.0)/1000.0 == expected_imag);
  }

  // c1 /= scalar
  void test_compound_division_scalar ( void ){
      Complex c1(6, 2);
      double scalar = 2;
      double expected_real = 3;
      double expected_imag = 1;
      c1 /= scalar;
      TS_ASSERT(c1.real() == expected_real);
      TS_ASSERT(c1.imag() == expected_imag);

      Complex c2(6, 2);
      scalar = -1.33;
      expected_real = -4.511;
      expected_imag = -1.504;
      c2 /= scalar;
      TS_ASSERT(round(c2.real()*1000.0)/1000.0 == expected_real);
      TS_ASSERT(round(c2.imag()*1000.0)/1000.0 == expected_imag);
  }

  // c1 *= c2
  void test_compound_multiplication ( void ){
      Complex c1(6, 2);
      Complex c2(2, 3);
      double expected_real = 6;
      double expected_imag = 22;
      c1 *= c2;
      TS_ASSERT(c1.real() == expected_real);
      TS_ASSERT(c1.imag() == expected_imag);

      Complex c3(6, 2);
      Complex c4(-2.33, -3.45);
      expected_real = -7.08;
      expected_imag = -25.36;
      c3 *= c4;
      TS_ASSERT(round(c3.real()*100.0)/100.0 == expected_real);
      TS_ASSERT(round(c3.imag()*100.0)/100.0 == expected_imag);
  }

  // c1 *= scalar
  void test_compound_multiplication_scalar ( void ){
      Complex c1(6, 2);
      double scalar = 3;
      double expected_real = 18;
      double expected_imag = 6;
      c1 *= scalar;
      TS_ASSERT(c1.real() == expected_real);
      TS_ASSERT(c1.imag() == expected_imag);

      Complex c2(6, 2);
      scalar = -2.5;
      expected_real = -15;
      expected_imag = -5;
      c2 *= scalar;
      TS_ASSERT(c2.real() == expected_real);
      TS_ASSERT(c2.imag() == expected_imag);
  }

  // Unary operators
  // c1 *= c2
  void test_unary_operators ( void ){
      Complex c1(5,3);
      Complex c2(-3,2);
      Complex c3;

      c3 = +c1;
      TS_ASSERT(c3.real() == 5);
      TS_ASSERT(c3.imag() == 3);

      c3 = -c1;
      TS_ASSERT(c3.real() == -5);
      TS_ASSERT(c3.imag() == -3);

      c3 = +c2;
      TS_ASSERT(c3.real() == -3);
      TS_ASSERT(c3.imag() == 2);

      c3 = -c2;
      TS_ASSERT(c3.real() == 3);
      TS_ASSERT(c3.imag() == -2);
  }

  // Complex arithmetics

  // Addition
  void test_complex_addition ( void ){
      Complex c1(5,3);
      Complex c2(-3.3,2.17);
      Complex c3;
      double expected_real = 1.7;
      double expected_imag = 5.17;

      c3 = c1 + c2;
      TS_ASSERT(round(c3.real()*100.0)/100.0 == expected_real);
      TS_ASSERT(round(c3.imag()*100.0)/100.0 == expected_imag);
  }

  // Addition with scalar
  void test_complex_addition_scalar ( void ){
      Complex c1(5,3);
      Complex c2;
      double scalar = 2.34;
      double expected_real = 7.34;
      double expected_imag = 3;

      c2 = c1 + scalar;
      TS_ASSERT(round(c2.real()*100.0)/100.0 == expected_real);
      TS_ASSERT(round(c2.imag()*100.0)/100.0 == expected_imag);

      c2 = scalar + c1;
      TS_ASSERT(round(c2.real()*100.0)/100.0 == expected_real);
      TS_ASSERT(round(c2.imag()*100.0)/100.0 == expected_imag);
  }

  // Subtraction
  void test_complex_subtraction ( void ){
      Complex c1(5,3);
      Complex c2(-3.3,2.17);
      Complex c3;
      double expected_real = 8.3;
      double expected_imag = 0.83;

      c3 = c1 - c2;
      TS_ASSERT(round(c3.real()*100.0)/100.0 == expected_real);
      TS_ASSERT(round(c3.imag()*100.0)/100.0 == expected_imag);
  }

  // Subtraction with scalar
  void test_complex_subtraction_scalar ( void ){
      Complex c1(5,3);
      Complex c2;
      double scalar = 2.34;
      double expected_real = 2.66;
      double expected_imag = 3;

      c2 = c1 - scalar;
      TS_ASSERT(round(c2.real()*100.0)/100.0 == expected_real);
      TS_ASSERT(round(c2.imag()*100.0)/100.0 == expected_imag);

      c2 = scalar - c1;
      TS_ASSERT(round(c2.real()*100.0)/100.0 == -expected_real);
      TS_ASSERT(round(c2.imag()*100.0)/100.0 == -expected_imag);
  }

  // Multiplication
  void test_complex_multiplication ( void ){
      Complex c1(5,3);
      Complex c2(-3.3,2.17);
      Complex c3;
      double expected_real = -23.01;
      double expected_imag = 0.95;

      c3 = c1 * c2;
      TS_ASSERT(round(c3.real()*100.0)/100.0 == expected_real);
      TS_ASSERT(round(c3.imag()*100.0)/100.0 == expected_imag);
  }

  // Multiplication with scalar
  void test_complex_multiplication_scalar ( void ){
      Complex c1(5,3);
      Complex c2;
      double scalar = 2.34;
      double expected_real = 11.70;
      double expected_imag = 7.02;

      c2 = c1 * scalar;
      TS_ASSERT(round(c2.real()*100.0)/100.0 == expected_real);
      TS_ASSERT(round(c2.imag()*100.0)/100.0 == expected_imag);

      c2 = scalar * c1;
      TS_ASSERT(round(c2.real()*100.0)/100.0 == expected_real);
      TS_ASSERT(round(c2.imag()*100.0)/100.0 == expected_imag);
  }

  // Division
  void test_complex_division ( void ){
      Complex c1(6, 2);
      Complex c2(-2.33, -3.45);
      Complex c3;
      double expected_real = -1.205;
      double expected_imag = 0.925;

      c3 = c1 / c2;
      TS_ASSERT(round(c3.real()*1000.0)/1000.0 == expected_real);
      TS_ASSERT(round(c3.imag()*1000.0)/1000.0 == expected_imag);
  }

  // Division with scalar
  void test_complex_division_scalar ( void ){
      Complex c1(5, 3);
      Complex c2;
      double scalar = 2.340;
      double expected_real = 2.137;
      double expected_imag = 1.282;

      c2 = c1 / scalar;
      TS_ASSERT(round(c2.real()*1000.0)/1000.0 == expected_real);
      TS_ASSERT(round(c2.imag()*1000.0)/1000.0 == expected_imag);

      c2 = scalar / c1;
      expected_real = 0.344;
      expected_imag = -0.206;
      TS_ASSERT(round(c2.real()*1000.0)/1000.0 == expected_real);
      TS_ASSERT(round(c2.imag()*1000.0)/1000.0 == expected_imag);
  }

  // Boolean operators

  // Equality operator
  void test_equality_operator ( void ){
      Complex c1(5, 3);
      Complex c2(5.0, 3.0);
      bool result = (c1 == c2);
      TS_ASSERT(result == true);

      c1 = 5.12 + 3.66_i;
      c2 = -5.12 + 3.66_i;
      result = (c1 == c2);
      TS_ASSERT(result == false);

      c1 = 3.66_i;
      c2 = 3.66_i;
      result = (c1 == c2);
      TS_ASSERT(result == true);

      c1 = 3.66_i;
      c2 = -5.12 + 3.66_i;
      result = (c1 == c2);
      TS_ASSERT(result == false);
  }

  // Inequality operator
  void test_inequality_operator ( void ){
      Complex c1(5, 3);
      Complex c2(5.0, 3.0);
      bool result = (c1 != c2);
      TS_ASSERT(result == false);

      c1 = 5.12 + 3.66_i;
      c2 = -5.12 + 3.66_i;
      result = (c1 != c2);
      TS_ASSERT(result == true);

      c1 = 3.66_i;
      c2 = 3.66_i;
      result = (c1 != c2);
      TS_ASSERT(result == false);

      c1 = 3.66_i;
      c2 = -5.12 + 3.66_i;
      result = (c1 != c2);
      TS_ASSERT(result == true);
  }

  // Return the real component
  void test_real_component ( void ){
      Complex c1(5, 3);
      double val = real(c1);
      TS_ASSERT(val == 5);

      c1 = -5.12 + 3.66_i;
      val = real(c1);
      TS_ASSERT(val == -5.12);
  }

  // Return the imaginary component
  void test_imag_component ( void ){
      Complex c1(5, 3);
      double val = imag(c1);
      TS_ASSERT(val == 3);

      c1 = 5.12 - 3.66_i;
      val = imag(c1);
      TS_ASSERT(val == -3.66);
  }

  // abs
  void test_magnitude ( void ){
      Complex c1(-4, 3);
      double val = abs(c1);
      double expected_val = 5;
      TS_ASSERT(val == expected_val);

      Complex c2(-4.3, 3.19);
      val = abs(c2);
      expected_val = 5.354;
      TS_ASSERT(round(val*1000.0)/1000.0 == expected_val);

      Complex c3;
      val = abs(c3);
      expected_val = 0;
      TS_ASSERT(val == expected_val);

      Complex c4(1, 2);
      val = abs(c4);
      expected_val = 2.236;
      TS_ASSERT(round(val*1000.0)/1000.0 == expected_val);

      Complex c5(0,2);
      val = abs(c5);
      expected_val = 2;
      TS_ASSERT(val == expected_val);

      Complex c6(2,0);
      val = abs(c6);
      expected_val = 2;
      TS_ASSERT(val == expected_val);
  }

  // less than operator
  void test_less_than_operator ( void ){
      Complex c1(4, 3);
      Complex c2(-4.3, -3.19);
      bool result1 = (c1 < c2);
      bool result2 = (c2 < c1);
      TS_ASSERT(result1 == true);
      TS_ASSERT(result2 == false);

      c1 = 1 + 2_i;
      c2 = 2 + 2_i;
      result1 = (c1 < c2);
      TS_ASSERT(result1 == true);

      c1 = 2 + 1_i;
      result1 = (c1 < c2);
      TS_ASSERT(result1 == true);

      c1 = 0;
      c2 = 0;
      result1 = (c1 < c2);
      TS_ASSERT(result1 == false);
  }

  // output operator
  void test_output_operator ( void ){
      Complex c1(4, 3);
      std::ofstream outfile1 ("outfile.txt");
      outfile1 << c1;
      outfile1.close();

      std::string inp;
      std::ifstream intest1 ("outfile.txt");
      intest1 >> inp;
      TS_ASSERT(inp == "(4,3)");
      intest1.close();

      Complex c2(-4.3, -3.19);
      std::ofstream outfile2 ("outfile.txt");
      outfile2 << c2;
      outfile2.close();

      std::ifstream intest2 ("outfile.txt");
      intest2 >> inp;
      TS_ASSERT(inp == "(-4.3,-3.19)");
      intest2.close();
  }

  // input operator
  void test_input_operator ( void ){
      Complex c1;
      std::ofstream outfile1 ("outfile.txt");
      outfile1 << "(4.12,3)";
      outfile1.close();
      std::ifstream intest1 ("outfile.txt");
      intest1 >> c1;
      intest1.close();

      Complex c2;
      std::ofstream outfile2 ("outfile.txt");
      outfile2 << "(4,-3.63)";
      outfile2.close();
      std::ifstream intest2 ("outfile.txt");
      intest2 >> c2;
      intest2.close();

      TS_ASSERT(c1.real() == 4.12);
      TS_ASSERT(c1.imag() == 3);

      TS_ASSERT(c2.real() == 4);
      TS_ASSERT(c2.imag() == -3.63);
  }

  void test_input_operator_onlyreal ( void ){
      Complex c1;
      std::ofstream outfile1 ("outfile.txt");
      outfile1 << "(4.12)";
      outfile1.close();
      std::ifstream intest1 ("outfile.txt");
      intest1 >> c1;
      intest1.close();

      Complex c2;
      std::ofstream outfile2 ("outfile.txt");
      outfile2 << "-5.54";
      outfile2.close();
      std::ifstream intest2 ("outfile.txt");
      intest2 >> c2;
      intest2.close();

      TS_ASSERT(c1.real() == 4.12);
      TS_ASSERT(c1.imag() == 0);

      TS_ASSERT(c2.real() == -5.54);
      TS_ASSERT(c2.imag() == 0);
  }

  void test_input_operator_invalid_input ( void ){
      Complex c;
      std::ofstream outfile1 ("outfile.txt");
      outfile1 << "(4.12";
      outfile1.close();
      std::ifstream intest1 ("outfile.txt");
      TS_ASSERT_THROWS(intest1 >> c, std::invalid_argument);
      intest1.close();

      std::ofstream outfile2 ("outfile.txt");
      outfile2 << "(4.12,6.12k)";
      outfile2.close();
      std::ifstream intest2 ("outfile.txt");
      TS_ASSERT_THROWS(intest2 >> c, std::invalid_argument);
      intest2.close();

      std::ofstream outfile3 ("outfile.txt");
      outfile3 << "-4.12,6.12";
      outfile3.close();
      std::ifstream intest3 ("outfile.txt");
      TS_ASSERT_THROWS(intest3 >> c, std::invalid_argument);
      intest3.close();

      std::ofstream outfile4 ("outfile.txt");
      outfile4 << "-";
      outfile4.close();
      std::ifstream intest4 ("outfile.txt");
      TS_ASSERT_THROWS(intest4 >> c, std::invalid_argument);
      intest4.close();

      std::ofstream outfile5 ("outfile.txt");
      outfile5 << "It's morbin time";
      outfile5.close();
      std::ifstream intest5 ("outfile.txt");
      TS_ASSERT_THROWS(intest5 >> c, std::invalid_argument);
      intest5.close();
  }


};
