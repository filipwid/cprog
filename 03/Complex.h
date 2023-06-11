#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class Complex {

// Following the formatting of cppreference
// Using style from Labb 2
public:
    // constructors and assignment operators
    Complex();
    Complex(double real);
    constexpr Complex(double real, double imaginary);
    Complex(const Complex &rhs);

    /* Is move constructor actually needed?
    Complex(Complex && other) noexcept;
    */

    Complex & operator=(const Complex & other);
    Complex & operator=(Complex && other) noexcept;


    // accessors
    double real() const;
    double imag() const;

    // Operators with complex and scalar operations
    void operator+=(const Complex & other);
    void operator+=(double other);

    void operator-=(const Complex & other);
    void operator-=(double other);

    void operator/=(const Complex & other);
    void operator/=(double other);

    void operator*=(const Complex & other);
    void operator*=(double other);

private:
    double c_real;
    double c_imag;
};

// Non member functions
// A list of functions can be found here: https://en.cppreference.com/w/cpp/numeric/complex

// Unary operators
Complex operator+(const Complex & c);
Complex operator-(const Complex & c);

// Complex arithmetics
Complex operator+(const Complex & lhs, const Complex & rhs);
Complex operator+(const Complex & lhs, double rhs);
Complex operator+(double lhs, const Complex & rhs);

Complex operator-(const Complex & lhs, const Complex & rhs);
Complex operator-(const Complex & lhs, double rhs);
Complex operator-(double lhs, const Complex & rhs);

Complex operator*(const Complex & lhs, const Complex & rhs);
Complex operator*(const Complex & lhs, double rhs);
Complex operator*(double lhs, const Complex & rhs);

Complex operator/(const Complex & lhs, const Complex & rhs);
Complex operator/(const Complex & lhs, double rhs);
Complex operator/(double lhs, const Complex & rhs);

// Boolean operators
bool operator==(const Complex & lhs, const Complex & rhs);
bool operator!=(const Complex & lhs, const Complex & rhs);

// Components
double real(const Complex & c);
double imag(const Complex & c);
double abs(const Complex & c);

//
bool operator<(const Complex & lhs, const Complex & rhs);

// io operators, based on those in Labb 2
std::ostream & operator<<(std::ostream & os, const Complex & c);
std::istream & operator>>(std::istream & is, Complex & c);


// Implementation from https://en.cppreference.com/w/cpp/numeric/complex/operator%22%22i
constexpr Complex operator""_i(unsigned long long arg){
  return Complex(0.0, static_cast<double>(arg));
}

constexpr Complex operator""_i(long double arg){
  return Complex(0.0, static_cast<double>(arg));
}

constexpr Complex::Complex(double real, double imaginary) : c_real(real), c_imag(imaginary)  {
}

#endif
