//
// DD1388 - Lab 2: The matrix
//

#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <cmath>

template <typename T>
class Matrix {

    static_assert(std::is_move_constructible<T>::value, "Must be move-constructible"); // T must be move-constructible */
    static_assert(std::is_move_assignable<T>::value, "Must be move-assignable"); // T must be move-assignable */

public:
    // constructors and assignment operators
    /* TODO: Make the appropriate constructor(s) explicit */
    Matrix();
    explicit Matrix(size_t dim);
    Matrix(size_t rows, size_t cols);
    Matrix(const std::initializer_list<T> & list);
    Matrix(Matrix<T> & other);
    Matrix(Matrix<T> && other) noexcept;

    Matrix<T> & operator=(const Matrix<T> & other);
    Matrix<T> & operator=(Matrix<T> && other) noexcept;

    ~Matrix();

    // accessors
    size_t rows() const;
    size_t cols() const;

    T & operator()(size_t row, size_t col);
    const T & operator()(size_t row, size_t col) const;

    // operators
    Matrix<T> operator*(const Matrix<T> & other) const;
    Matrix<T> operator+(const Matrix<T> & other) const;
    Matrix<T> operator-(const Matrix<T> & other) const;

    void operator*=(const Matrix<T> & other);
    void operator+=(const Matrix<T> & other);
    void operator-=(const Matrix<T> & other);

    // methods
    void reset();

    void insert_row(size_t row);
    void append_row(size_t row);
    void remove_row(size_t row);
    void insert_column(size_t col);
    void append_column(size_t col);
    void remove_column(size_t col);

    // iterators
    typedef T* iterator;

    iterator begin();
    iterator end();

private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    T * m_vec;
};

// input/output operators
template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m);

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m);

// functions
template<typename T>
Matrix<T> identity(size_t dim);


//
// Implementations
//

template<typename T>
Matrix<T>::Matrix()
/*:  Initialize members here */ {
    m_rows = 0;
    m_cols = 0;
    m_capacity = m_rows*m_cols;
    m_vec = new T[0];
}

template<typename T>
Matrix<T>::Matrix(size_t dim)
/*:  Initialize members here */ {
    m_rows = dim;
    m_cols = dim;
    m_capacity = dim*dim;
    m_vec = new T[m_capacity];
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
/*:  Initialize members here */ {
    m_rows = rows;
    m_cols = cols;
    m_capacity = rows*cols;
    m_vec = new T[m_capacity];
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T> & list)
/*:  Initialize members here */ {
    if (list.size() <= 0 || fmod(sqrt(list.size()), 1) > 0){  // fmod finds the remainder, an there should be 0 remainder after dividing with 1
      throw std::out_of_range ("Input out of range");
    }
    m_rows = sqrt(list.size());
    m_cols = sqrt(list.size()); // If time, do a better solution
    m_capacity = list.size();
    m_vec = new T[m_capacity];
    int i = 0;
    for(T element : list){ // for (auto element) May be another way to do it
      m_vec[i] = element;
      i++;
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> & other)   // Not allowed to change to const?
/*:  Initialize members here */ {
    m_rows = other.m_rows;  // copy constructor is same class so will have access to private variables
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = new T[m_capacity];  // Cannot copy the pointer
    for (int i = 0; i < m_capacity; i++){
      m_vec[i] = other.m_vec[i];
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept {
    m_rows = std::move(other.m_rows);
    m_cols = std::move(other.m_cols);
    m_capacity = std::move(other.m_capacity);
    m_vec = std::move(other.m_vec);
    other.m_rows = 0;
    other.m_cols = 0;
    other.m_capacity = 0;
    other.m_vec = nullptr;    // Maybe, fix later
}

/*template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept {
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = other.m_vec;
    other.m_vec = nullptr;    // Maybe, fix later
}*/

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & other) {
    if (this != &other){
      delete[] m_vec;                             // Valgrind gives leak without
      m_rows = other.m_rows;
      m_cols = other.m_cols;
      m_capacity = other.m_capacity;
      m_vec = new T[other.m_capacity];
      for (int i = 0; i < m_capacity; i++){
        m_vec[i] = other.m_vec[i];
      }
    }
    return *this;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) noexcept {
  if (this != &other){
    delete[] m_vec;
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = other.m_vec;
    other.m_rows = 0;
    other.m_cols = 0;
    other.m_capacity = 0;
    other.m_vec = nullptr;
  }
  return *this;
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] m_vec;
}

template<typename T>
size_t Matrix<T>::rows() const {
    return m_rows;
}

template<typename T>
size_t Matrix<T>::cols() const {
    return m_cols;
}

template<typename T>
T & Matrix<T>::operator()(size_t row, size_t col) {
    if (row >= m_rows || col >= m_cols || row < 0 || col < 0){
      throw std::out_of_range ("Invalid row or column");
    }
    return m_vec[m_cols * row + col];
}

template<typename T>
const T & Matrix<T>::operator()(size_t row, size_t col) const {
    return m_vec[m_cols * row + col];
}

// Matrix multiplication
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const {
    if (m_cols != other.m_rows){
      throw std::out_of_range ("Invalid dimensions");
    }
    size_t tempcols = m_rows;
    size_t temprows = other.m_cols;
    Matrix<T> temp = Matrix<T>(temprows, tempcols);
    for (int i = 0; i < temprows; i++){   // https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
      for (int j = 0; j < tempcols; j++){
        temp.m_vec[m_cols*i+j] = 0;
        for (int k = 0; k < m_cols; k++){
          temp.m_vec[m_cols*i+j] +=m_vec[m_cols * i + k] * other.m_vec[other.m_cols * k + j];
        }
      }
    }

    return temp;
}

// Matric addition
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const {
  if (m_rows != other.m_rows || m_cols != other.m_cols){
    throw std::out_of_range ("Invalid dimensions");
  }
  Matrix<T> temp = Matrix<T>(m_rows, m_cols);
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_cols; j++){
      temp.m_vec[m_cols*i + j] = m_vec[m_cols*i + j] + other.m_vec[other.m_cols * i + j];
    }
  }

  return temp;
}

// Matrix subtraction
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const {
  if (m_rows != other.m_rows || m_cols != other.m_cols){
    throw std::out_of_range ("Invalid dimensions");
  }
  Matrix<T> temp = Matrix<T>(m_rows, m_cols);
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_cols; j++){
      temp.m_vec[m_cols*i+j] = m_vec[m_cols * i + j] - other.m_vec[other.m_cols * i + j];
    }
  }

  return temp;
}


template<typename T>
void Matrix<T>::operator*=(const Matrix<T> & other) {
  if (m_cols != other.m_rows){
    throw std::out_of_range ("Invalid dimensions");
  }
  *this = *this * other;
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T> & other) {
  if (m_rows != other.m_rows || m_cols != other.m_cols){
    throw std::out_of_range ("Invalid dimensions");
  }
  *this = *this + other;
}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T> & other) {
  if (m_rows != other.m_rows || m_cols != other.m_cols){
    throw std::out_of_range ("Invalid dimensions");
  }
  *this = *this - other;
}

template<typename T>
void Matrix<T>::reset() {
    for (int i = 0; i < m_capacity; i++){
      m_vec[i] = T();
    }
}

template<typename T>
void Matrix<T>::insert_row(size_t row) {
    if (row > m_rows || row < 0){
      throw std::out_of_range ("Invalid row");
    }
    size_t t_rows = m_rows + 1;
    T * t_vec = new T[t_rows*m_cols];

    for (int i = 0; i < t_rows; i++){
      for (int j = 0; j < m_cols; j++){
        if (i == row){
          t_vec[m_cols*i+j] = 0;
        }
        else if (i > row){
          t_vec[m_cols*i+j] = m_vec[m_cols*(i-1)+j];
        }
        else{
          t_vec[m_cols*i+j] = m_vec[m_cols*i+j];
        }
      }
    }
    m_rows = t_rows;
    m_capacity = m_rows * m_cols;
    delete[] m_vec;
    //m_vec = new T[m_capacity];
    m_vec = t_vec;
}

template<typename T>
void Matrix<T>::append_row(size_t row) {
    if (row > m_rows || row < 0){
      throw std::out_of_range ("Invalid row");
    }
    row++;
    size_t t_rows = m_rows + 1;
    T * t_vec = new T[t_rows*m_cols];

    for (int i = 0; i < t_rows; i++){
      for (int j = 0; j < m_cols; j++){
        if (i == row){
          t_vec[m_cols*i+j] = 0;
        }
        else if (i > row){
          t_vec[m_cols*i+j] = m_vec[m_cols*(i-1)+j];
        }
        else{
          t_vec[m_cols*i+j] = m_vec[m_cols*i+j];
        }
      }
    }
    m_rows = t_rows;
    m_capacity = m_rows * m_cols;
    delete[] m_vec;
    m_vec = t_vec;
}

template<typename T>
void Matrix<T>::remove_row(size_t row) {
    if (row > m_rows || row < 0){
      throw std::out_of_range ("Invalid row");
    }
    size_t t_rows = m_rows - 1;
    T * t_vec = new T[t_rows*m_cols];

    for (int i = 0; i < m_rows; i++){
      for (int j = 0; j < m_cols; j++){
        if (i < row){
          t_vec[m_cols*i+j] = m_vec[m_cols*i+j];
        }
        else if (i > row){
          t_vec[m_cols*(i-1)+j] = m_vec[m_cols*i+j];
        }
      }
    }
    m_rows = t_rows;
    m_capacity = m_rows * m_cols;
    delete[] m_vec;
    m_vec = t_vec;
}

template<typename T>
void Matrix<T>::insert_column(size_t col) {
    if (col > m_cols || col < 0){
      throw std::out_of_range ("Invalid column");
    }
    size_t t_cols = m_cols + 1;
    T * t_vec = new T[m_rows*t_cols];

    for (int i = 0; i < m_rows; i++){
      for (int j = 0; j < t_cols; j++){
        if (j == col){
          t_vec[t_cols*i+j] = 0;
        }
        else if (j > col){
          t_vec[t_cols*i+j] = m_vec[m_cols*i+j-1];
        }
        else{
          t_vec[t_cols*i+j] = m_vec[m_cols*i+j];
        }
      }
    }
    m_cols = t_cols;
    m_capacity = m_rows * m_cols;
    delete[] m_vec;
    m_vec = t_vec;
}

template<typename T>
void Matrix<T>::append_column(size_t col) {
    if (col > m_cols || col < 0){
      throw std::out_of_range ("Invalid column");
    }
    col++;
    size_t t_cols = m_cols + 1;
    T * t_vec = new T[m_rows*t_cols];

    for (int i = 0; i < m_rows; i++){
      for (int j = 0; j < t_cols; j++){
        if (j == col){
          t_vec[t_cols*i+j] = 0;
        }
        else if (j > col){
          t_vec[t_cols*i+j] = m_vec[m_cols*i+j-1];
        }
        else{
          t_vec[t_cols*i+j] = m_vec[m_cols*i+j];
        }
      }
    }
    m_cols = t_cols;
    m_capacity = m_rows * m_cols;
    delete[] m_vec;
    m_vec = t_vec;
}

template<typename T>
void Matrix<T>::remove_column(size_t col) {
    if (col > m_cols || col < 0){
      throw std::out_of_range ("Invalid column");
    }
    size_t t_cols = m_cols - 1;
    T * t_vec = new T[m_rows*t_cols];

    for (int i = 0; i < m_rows; i++){
      for (int j = 0; j < m_cols; j++){
        if (j < col){
          t_vec[t_cols*i+j] = m_vec[m_cols*i+j];
        }
        else if (j > col){
          t_vec[t_cols*i+j-1] = m_vec[m_cols*i+j];
        }
      }
    }
    m_cols = t_cols;
    m_capacity = m_rows * m_cols;
    delete[] m_vec;
    m_vec = t_vec;
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() {
    return &m_vec[0];
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::end() {
    return &m_vec[m_capacity-1];
}

template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m) {
    size_t rows, cols;
    is >> rows >> cols;         // First line in the file contain number of rows and number of columns, in that order
    Matrix<T> temp = Matrix<T>(rows,cols);
    T currelem;
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        is >> currelem;
        temp(i,j) = currelem;
      }
    }
    m = std::move(temp);
    return is;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m) {
    os << m.rows() << "\t" << m.cols() << "\n";       // First line in the file contain number of rows and number of columns, in that order
    for (int i = 0; i < m.rows(); i++){
      for (int j = 0; j < m.cols(); j++){
        os << m(i,j) << "\t";
      }
      os << "\n";
    }
    return os;
}

template<typename T>
Matrix<T> identity(size_t dim) {
    static_assert(std::is_arithmetic<T>::value, "Must be numeric");
    Matrix<T> temp = Matrix<T>(dim);
    for (int i = 0; i < dim; i++){
      temp(i,i) = 1;
    }
    return temp;
}

#endif //MATRIX_H
