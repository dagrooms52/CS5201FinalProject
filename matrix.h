////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: CS5201
// Date: 3/19/2015
// File Name: matrix.h
// Purpose: Class header for the matrix class
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include "abstractmatrix.h"

#include <iostream>

// Function: Matrix()
// Pre: None
// Post: m_rows = 0, m_cols = 0, m_data = NULL
// Description: The default constructor for a matrix

// Function: Matrix(const int size)
// Pre: int size > 0
// Post: A matrix with rows and columns equal to size is created; pointer m_data
//       points to an array of vectors, all of size specified by input "size"
// Description: Initializes a matrix with amounts of rows and columns equal to
//              the size input

// Function: ~Matrix()
// Pre: None
// Post: If m_data is not NULL, delete[] m_data
// Description: Deletes the member variable m_data pointer if need be

// Function: Matrix(Matrix copy)
// Pre: None
// Post: A matrix is constructed, with equal number of rows and columns as
//       the copy matrix. A deep copy is performed on the data pointed to by 
//       copy's m_data. 
// Description: Performs a deep copy of the passed matrix, constructing the 
//              calling object as a copy

// Function: operator=(Matrix rhs)
// Pre: None
// Post: The calling matrix has the same number of rows and columns as the rhs
//       matrix. A deep copy is performed on the data pointed to by the rhs's
//       m_data.
// Description: Performs a deep copy of the data in the rhs matrix so that the
//              calling matrix is equal to the rhs in size and data.

// Function: operator=(AbstractMatrix& rhs)
// Pre: None
// Post: The size of the calling matrix equals that of the rhs matrix. A deep
//       copy is performed to the calling object's m_data.
// Description: Performs a deep copy of any matrix derived from the interface
//              into the calling dense matrix. 

// Function: getSize()
// Pre: None
// Post: Returns number of rows of calling matrix; number of columns equals
//       number of rows, as it is a square matrix.
// Description: Returns the number of rows or columns of the calling matrix.
//              These two values are equal, as the matrix is square.

// Function: operator()(row, column) const
// Pre: Neither index is negative, neither index is greater than matrix size
// Post: A const reference to the T type value at the index position of m_data 
//       is returned
// Description: Gets the value at the index position

// Function: operator>>
// Pre: None
// Post: Each vector pointed to by m_data is filled with input from the stream
//       in the order of first to last, filling each vector before 
//       proceeding to the next.
// Description: Input operator, fills the matrix with values from the stream

// Function: operator()(row, column)
// Pre: Neither index is negative, neither is greater than size of matrix
// Post: A reference to the value at the index position of m_data is returned
// Description: Returns a reference to the value at the index position

// Function: operator()(index)
// Pre: Index is not less than zero, index is less than matrix size
// Post: A reference to the Vector at the index position of m_data is returned
// Description: Returns a reference to the Vector at the position in m_data

// Function: operator+
// Pre: Calling object size = passed matrix size, T + T is defined
// Post: A matrix whose values are the result of the addition of each
//       corresponding value of the calling matrix and the passed matrix
//       is returned.
// Description: Adds the corresponding values of the two matrices.

// Function: operator-
// Pre: Calling matrix size = passed matrix size, T - T is defined
// Post: A matrix whose values are the result of the subtraction of each 
//       corresponding value of the passed matrix from the calling matrix
//       is returned.
// Description: Subtracts the corresponding values of the two matrices.

// Function: transpose()
// Pre: None
// Post: A matrix is returned whose size equals that of the calling matrix,
//       and whose values are the result of the transpose operation of the
//       calling matrix.
// Description: Returns the transpose of the calling matrix

// Function: operator*(Matrix rhs)
// Pre: T * T, T + T defined; Calling matrix size = rhs size
// Post: A matrix with equal size to the calling matrix is returned,
//       whose values are the result of the multiplication of the 
//       calling matrix and the rhs matrix
// Description: Multiplies the calling matrix by the rhs matrix

// Function: operator*(Vector rhs)
// Pre: T * T defined; Calling matrix size = vector size
// Post: A vector with size equal to the passed vector is returned, whose
//       values are the result of the calling matrix multiplied by the
//       rhs vector.
// Description: Multiplies the calling matrix by the passed vector.

// Function: operator*(T scalar)
// Pre: T * T defined
// Post: A matrix with equal size to the calling matrix is returned, whose
//       values are each multiplied by the passed scalar.
// Description: Scales the matrix by multiplying each value in the matrix
//              by the scalar.

// Function: swap(index1, index2)
// Pre: 0 <= index1 < matrix size, 0 <= index2 < matrix size
// Post: The rows corresponding to index1 and index2 are swapped with each 
//       other so that the vectors at both indeces are switched with each other.
// Description: Swaps the two rows of the matrix indicated by the swap indeces.

// Function: operator+ (AbstractMatrix&)
// Pre: Size of rhs equals size of calling object, + is defined for type T
// Post: The addition of the calling matrix and the passed matrix is returned
// Description: Returns the addition of the calling matrix with any matrix
//              that has been derived from the interface base class.

// Function: operator- (AbstractMatrix&)
// Pre: Size of rhs equals size of calling object, -= is defined for type T
// Post: The subtraction of the passed matrix from the calling matrix is returned
// Description: Returns the subtraction of any matrix derived from the interface
//              base class from the calling matrix.

// Function: operator* (AbstractMatrix&)
// Pre: Size of rhs equals size of calling matrix, += and * defined for type T
// Post: The result of multiplication of the calling matrix and the rhs matrix
//       is returned
// Description: Returns the multiplication of the calling matrix with any matrix
//              that has been derived from the interface base class.

template <class T>
class Matrix: public AbstractMatrix<T>
{
  private:
    Vector<T> * m_data; // pointer to array of vectors
    int m_rows;
    int m_cols;

  public:

    // Default Constructor
    Matrix<T>();

    // Constructor with size
    Matrix<T>(const int size);

    // Destructor
    ~Matrix<T>();

    // Copy constructor
    Matrix<T>(const Matrix<T> & cpy);

    // Overload assignment operator
    Matrix<T>& operator= (const Matrix<T>& rhs);

    // Assignment operator using interface
    Matrix<T>& operator= (const AbstractMatrix<T>& rhs);

    ///////////////////////
    // --- Accessors --- //
    ///////////////////////

    // Get matrix size, assuming square matrix
    virtual int getSize() const;

    // Const () operator
    virtual const T& operator() (const int row, const int column) const;

    //////////////////////
    // --- Mutators --- //
    //////////////////////

    // Input operator >>
    template <class U>
    friend std::istream& operator>> (std::istream& in, Matrix<U>& mx);

    // Read/write () operator 
    virtual T& operator() (const int row, const int column);

    // Vector return using function operator
    virtual Vector<T>& operator() (const int index);

    // Matrix addition operator
    Matrix<T> operator+ (const Matrix<T>& mx) const;

    // Matrix subtraction operator
    Matrix<T> operator- (const Matrix<T>& mx) const;

    // Matrix transpose
    Matrix<T> transpose() const;

    // Matrix multiplication operator
    Matrix<T> operator* (const Matrix<T>& rhs) const;

    // Vector multiplication operator
    virtual Vector<T> operator* (const Vector<T>& rhs) const;

    // Scalar multiplication operator
    Matrix<T> operator* (const T scalar) const;

    // Swap rows of matrix
    void swap(const int index1, const int index2);

    ///////////////
    // Interface //
    ///////////////

    // Add matrix to other types through interface
    Matrix<T> operator+ (const AbstractMatrix<T>& rhs) const;

    // Subtract interface matrix from calling object
    Matrix<T> operator- (const AbstractMatrix<T>& rhs) const;

    // Multiply the matrix with other matrices through the interface
    Matrix<T> operator* (const AbstractMatrix<T>& rhs) const;
};

#include "matrix.hpp"

#endif
