////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: CS5201
// Date: 3/19/2015
// File Name: umatrix.h
// Purpose: To define a class for an Upper Triangle Matrix, which derives from the 
//          AbstractMatrix abstract base class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UMATRIX_H
#define UMATRIX_H

#include "vector.h"
#include "abstractmatrix.h"

#include <iostream>

// Function: UMatrix()
// Pre: None
// Post: m_size = 0, m_data = NULL
// Description: The default constructor for a matrix

// Function: UMatrix(const int size)
// Pre: int size > 0
// Post: A matrix with rows and columns equal to size is created; pointer m_data
//       points to an array of vectors, all of size specified by input "size"
// Description: Initializes a matrix with amounts of rows and columns equal to
//              the size input

// Function: ~UMatrix()
// Pre: None
// Post: If m_data is not NULL, delete[] m_data
// Description: Deletes the member variable m_data pointer if need be

// Function: UMatrix(UMatrix copy)
// Pre: None
// Post: A matrix is constructed, with equal number of rows and columns as
//       the copy matrix. A deep copy is performed on the data pointed to by 
//       copy's m_data. 
// Description: Performs a deep copy of the passed matrix, constructing the 
//              calling object as a copy

// Function: operator=(UMatrix rhs)
// Pre: None
// Post: The calling matrix has the same number of rows and columns as the rhs
//       matrix. A deep copy is performed on the data pointed to by the rhs's
//       m_data.
// Description: Performs a deep copy of the data in the rhs matrix so that the
//              calling matrix is equal to the rhs in size and data.

// Function: getSize()
// Pre: None
// Post: Returns the size of the matrix
// Description: Returns the number of rows or columns of the calling matrix.
//              These two values are equal, as the matrix is square.

// Function: operator()(row, column) const
// Pre: Neither index is negative, neither index is greater than matrix size
// Post: A const reference to the T type value at the index position of m_data 
//       is returned; m_zero is returned if the position is above the diagonal.
// Description: Gets the value at the index position

// Function: operator>>
// Pre: None
// Post: Each vector pointed to by m_data is filled with input from the stream
//       in the order of first to last, filling each vector before 
//       proceeding to the next.
// Description: Input operator, fills the matrix with values from the stream

// Function: operator()(row, column)
// Pre: Neither index is negative, neither is greater than size of matrix
// Post: A reference to the value at the index position of m_data is returned.
//       m_zero is returned if the position is above the diagonal.
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
// Description: Adds the corresponding values of the two matrices efficiently.

// Function: operator-
// Pre: Calling matrix size = passed matrix size, T - T is defined
// Post: A matrix whose values are the result of the subtraction of each 
//       corresponding value of the passed matrix from the calling matrix
//       is returned.
// Description: Subtracts the corresponding values of the two matrices efficiently.

// Function: operator*(UMatrix rhs)
// Pre: T * T, T + T defined; Calling matrix size = rhs size
// Post: A matrix with equal size to the calling matrix is returned,
//       whose values are the result of the multiplication of the 
//       calling matrix and the rhs matrix
// Description: Multiplies the calling matrix by the rhs matrix efficiently.

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

template <class T>
class UMatrix : public AbstractMatrix<T>
{
  private:
    Vector<T>* m_data;
    int m_size;
    static T m_zero;
  
  public:
    
    // Default Constructor
    UMatrix<T>();

    // Size Constructor
    UMatrix<T>(const int size);

    // Destructor
    ~UMatrix<T>();

    // Assignment operator
    UMatrix<T>& operator= (const UMatrix<T>& rhs);

    // Copy constructor
    UMatrix<T>(const UMatrix<T> & cpy);
 
    //////////////////////
    // --- Mutators --- //
    //////////////////////

    // Input operator
    template <class U>
    friend std::istream& operator>> (std::istream& in, UMatrix<U>& mx);

    // UMatrix addition - more needed
    UMatrix<T> operator+ (const UMatrix<T>& mx) const;

    // UMatrix subtraction - more needed
    UMatrix<T> operator- (const UMatrix<T>& mx) const;

    // UMatrix multiplication - more needed
    UMatrix<T> operator* (const UMatrix<T>& rhs) const;

    // Scalar multiplication - only 1
    UMatrix<T> operator* (const T scalar) const;

    ///////////////////////
    // --- Inherited --- //
    ///////////////////////

    // Read-only subscript operator
    virtual const T& operator() (const int row, const int column) const;

    // Read-write subscript operator
    virtual T& operator() (const int row, const int column);

    //Vector return using function operator
    virtual Vector<T>& operator() (const int index);

    // Return size of matrix, assuming square
    virtual int getSize() const;

    // Matrix * vector dot product
    virtual Vector<T> operator* (const Vector<T>& rhs) const;
};

// Static T is 0
template <class T>
T UMatrix<T>::m_zero = 0;

#include "umatrix.hpp"

#endif
