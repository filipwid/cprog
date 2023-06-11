// Layout of all the functions and constructors etc is based on Matrix.h
#include "Complex.h"
#include <regex>

// Constructors
Complex::Complex() {
    c_real = 0.0;
    c_imag = 0.0;
}

Complex::Complex(double real) {
    c_real = real;
    c_imag = 0.0;
}

//constexpr Complex::Complex(double real, double imaginary) : c_real(real), c_imag(imaginary)  {
// }

Complex::Complex(const Complex &rhs) {
    c_real = rhs.real();
    c_imag = rhs.imag();
}

// Copy assignment
Complex & Complex::operator=(const Complex & other){
    c_real = other.real();
    c_imag = other.imag();

    return *this;
}

// Move assignment
Complex & Complex::operator=(Complex && other) noexcept{
    c_real = other.real();
    c_imag = other.imag();
    other.c_real = 0;
    other.c_imag = 0;

    return *this;
}

double Complex::real() const {
    return c_real;
}

double Complex::imag() const {
    return c_imag;
}

void Complex::operator+=(const Complex & other){
    c_real += other.real();
    c_imag += other.imag();
}

void Complex::operator+=(double other){
    c_real += other;
}

void Complex::operator-=(const Complex & other){
  c_real -= other.real();
  c_imag -= other.imag();
}

void Complex::operator-=(double other){
    c_real -= other;
}

// https://en.wikipedia.org/wiki/Complex_number#Reciprocal_and_division
void Complex::operator/=(const Complex & other){
    double denominator = other.real()*other.real() + other.imag()*other.imag();
    double calc_real = (c_real*other.real() + c_imag*other.imag()) / denominator;
    double calc_imag = (c_imag*other.real() - c_real*other.imag()) / denominator;

    c_real = calc_real;
    c_imag = calc_imag;
}

void Complex::operator/=(double other){
    c_real /= other;
    c_imag /= other;
}

// https://en.wikipedia.org/wiki/Complex_number#Multiplication_and_square
// (x + yi)(u + vi) = (xu - yv) + (xv + yu)i
void Complex::operator*=(const Complex & other){
    double calc_real = c_real*other.real() - c_imag*other.imag();
    double calc_imag = c_real*other.imag() + c_imag*other.real();
    c_real = calc_real;
    c_imag = calc_imag;
}

void Complex::operator*=(double other){
    c_real *= other;
    c_imag *= other;
}

// Unary Operators
Complex operator+(const Complex & c){
    Complex ret(c.real(), c.imag());
    return ret;
}

Complex operator-(const Complex & c){
    Complex ret(-c.real(), -c.imag());
    return ret;
}

// Complex arithmetics
// Addition
Complex operator+(const Complex & lhs, const Complex & rhs){
    Complex temp(lhs.real() + rhs.real(), lhs.imag() + rhs.imag());
    return temp;
}

Complex operator+(const Complex & lhs, double rhs){
    Complex temp(lhs.real() + rhs, lhs.imag());
    return temp;
}

Complex operator+(double lhs, const Complex & rhs){
    Complex temp(lhs + rhs.real(), rhs.imag());
    return temp;
}

// subtraction
Complex operator-(const Complex & lhs, const Complex & rhs){
    Complex temp(lhs.real() - rhs.real(), lhs.imag() - rhs.imag());
    return temp;
}

Complex operator-(const Complex & lhs, double rhs){
    Complex temp(lhs.real() - rhs, lhs.imag());
    return temp;
}

Complex operator-(double lhs, const Complex & rhs){
    Complex temp(lhs - rhs.real(), -rhs.imag());
    return temp;
}

// Multiplication
Complex operator*(const Complex & lhs, const Complex & rhs){
    double calc_real = lhs.real()*rhs.real() - lhs.imag()*rhs.imag();
    double calc_imag = lhs.real()*rhs.imag() + lhs.imag()*rhs.real();

    Complex temp(calc_real, calc_imag);
    return temp;
}

Complex operator*(const Complex & lhs, double rhs){
    Complex temp(lhs.real()*rhs, lhs.imag()*rhs);
    return temp;
}

Complex operator*(double lhs, const Complex & rhs){
    Complex temp(rhs.real()*lhs, rhs.imag()*lhs);
    return temp;
}

// Division
Complex operator/(const Complex & lhs, const Complex & rhs){
    double denominator = rhs.real()*rhs.real() + rhs.imag()*rhs.imag();
    double calc_real = (lhs.real()*rhs.real() + lhs.imag()*rhs.imag()) / denominator;
    double calc_imag = (lhs.imag()*rhs.real() - lhs.real()*rhs.imag()) / denominator;

    Complex temp(calc_real, calc_imag);
    return temp;
}

Complex operator/(const Complex & lhs, double rhs){
    Complex temp(lhs.real()/rhs, lhs.imag()/rhs);
    return temp;
}

// https://en.wikipedia.org/wiki/Complex_number#Reciprocal_and_division
Complex operator/(double lhs, const Complex & rhs){
    double denominator = rhs.real()*rhs.real() + rhs.imag()*rhs.imag();
    double calc_real = lhs*rhs.real() / denominator;
    double calc_imag = -lhs*rhs.imag() / denominator;

    Complex temp(calc_real, calc_imag);
    return temp;
}

// Boolean operators
bool operator==(const Complex & lhs, const Complex & rhs){
    return (lhs.real() == rhs.real() && lhs.imag() == rhs.imag());
}

bool operator!=(const Complex & lhs, const Complex & rhs){
    return !(lhs.real() == rhs.real() && lhs.imag() == rhs.imag());
}

// Return (placeholder description)
double real(const Complex & c){
    double temp = c.real();
    return temp;
}

double imag(const Complex & c){
    double temp = c.imag();
    return temp;
}

double abs(const Complex & c){
    double temp = c.real()*c.real() + c.imag()*c.imag();
    return sqrt(temp);
}

// Checks magnitude of lhs and rhs
bool operator<(const Complex & lhs, const Complex & rhs){
    double lhs_pow = abs(lhs);
    double rhs_pow = abs(rhs);
    return (lhs_pow < rhs_pow);
}

// io operators

// Output ostream in the form "(real,imaginary)"
std::ostream & operator<<(std::ostream & os, const Complex & c) {
    os << "(" << c.real() << "," << c.imag() << ")";
    return os;
}

// Convert input into Complex
/*std::istream & operator>>(std::istream & is, Complex & c){
    std::string inp;
    is >> inp;
    if (inp[0] == '(' && inp.back() == ')'){      // Might be able to make prettier
        int cpos = inp.find(",");
        if (cpos != -1) {   // If .find() does not find a comma, cpos = -1
            std::string num1 = inp.substr(1, cpos - 1);
            std::string num2 = inp.substr(cpos + 1, inp.length()-2-cpos);
            double dnum1 = std::stod(num1);
            double dnum2 = std::stod(num2);
            c = Complex(dnum1, dnum2);
        }
        else {
            std::string num = inp.substr(1, inp.length()-2);
            double dnum = std::stod(num);
            c = Complex(dnum);
        }
    }
    else {
      double dnum = std::stod(inp);
      c = Complex(dnum);
    }

    return is;
}*/

std::istream & operator>>(std::istream & is, Complex & c){
    std::string inp;
    is >> inp;
    std::regex fullComplex("^\\([-]?[0-9]*[.]?[0-9]+\\,[-]?[0-9]*[.]?[0-9]+\\)$");
    std::regex realOnlyInPar("^\\([-]?[0-9]*[.]?[0-9]+\\)$");
    std::regex realOnly("^[-]?[0-9]*[.]?[0-9]+$");

    if (regex_match(inp, fullComplex)){
      int cpos = inp.find(",");
      std::string num1 = inp.substr(1, cpos - 1);
      std::string num2 = inp.substr(cpos + 1, inp.length()-2-cpos);
      double dnum1 = std::stod(num1);
      double dnum2 = std::stod(num2);
      c = Complex(dnum1, dnum2);
    }
    else if (regex_match(inp, realOnlyInPar)){
      std::string num = inp.substr(1, inp.length()-2);
      double dnum = std::stod(num);
      c = Complex(dnum);
    }
    else if (regex_match(inp, realOnly)){

      double dnum = std::stod(inp);
      c = Complex(dnum);
    }
    else {
      throw std::invalid_argument("Invalid formatting in file");
    }

    return is;
}
