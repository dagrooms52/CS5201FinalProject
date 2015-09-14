////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: CS5201
// Daate: 3/30/2015
// File Name: tridiagmatrix.h
// Purpose: To define a class for a Tri-Diagonal Matrix, which derives from the 
//          AbstractMatrix abstract base class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIDIAGMATRIX_H
#define TRIDIAGMATRIX_H

#include "abstractmatrix.h"
#include "matrix.h"

// Function: TriDiagMatrix()
// Pre: None
// Post: m_size = 0, m_data = NULL
// Description: The default constructor for a matrix

// Function: TriDiagMatrix(const int size)
// Pre: int size > 0
// Post: A matrix with rows and columns equal to size is created; pointer m_data
//       points to an array of vectors, all of size specified by input "size"
// Description: Initializes a matrix with amounts of rows and columns equal to
//              the size input

// Function: ~TriDiagMatrix()
// Pre: None
// Post: If m_data is not NULL, delete[] m_data
// Description: Deletes the member variable m_data pointer if need be

// Function: TriDiagMatrix(TriDiagMatrix copy)
// Pre: None
// Post: A matrix is constructed, with equal number of rows and columns as
//       the copy matrix. A deep copy is performed on the data pointed to by 
//       copy's m_data. 
// Description: Performs a deep copy of the passed matrix, constructing the 
//              calling object as a copy

// Function: operator=(TriDiagMatrix rhs)
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

// Function: const Vector<T> operator(index)
// Pre: Index is at least zero, less than matrix size
// Post: A const vector according to the index value in m_data is returned
// Description: Returns a const vector according to the index value from m_data
//              which is not a row of the matrix but is the implementation's vector

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
class TriDiagMatrix : public AbstractMatrix<T>
{
  private:
    
    Vector<T>* m_data;
    int m_size;
    static T m_zero;

  public:

    // Default Constructor
    TriDiagMatrix<T>();

    // Size Constructor
    TriDiagMatrix<T>(const int size);

    // Destructor
    ~TriDiagMatrix<T>();

    // Assignment operator
    TriDiagMatrix<T>& operator= (const TriDiagMatrix<T>& rhs);

    // Copy constructor
    TriDiagMatrix<T>(const TriDiagMatrix<T> & cpy);

    //////////////////////
    // --- Mutators --- //
    //////////////////////

    // Input operator
    template <class U>
    friend std::istream& operator>> (std::istream& in, TriDiagMatrix<U>& mx);

    // LMatrix addition - more needed
    TriDiagMatrix<T> operator+ (const TriDiagMatrix<T>& mx) const;

    // LMatrix subtraction - more needed
    TriDiagMatrix<T> operator- (const TriDiagMatrix<T>& mx) const;

    // Scalar multiplication - only 1
    TriDiagMatrix<T> operator* (const T scalar) const;

    // Const vector return using function operator
    const Vector<T>& operator() (const int index) const;

    ///////////////////////
    // --- Inherited --- //
    ///////////////////////

    // Read-only subscript operator
    virtual const T& operator() (const int row, const int column) const;

    // Write subscript operator
    virtual T& operator() (const int row, const int column);

    // Vector return using function operator
    virtual Vector<T>& operator() (const int index);

    // Return size of matrix, assuming square
    virtual int getSize() const;

    // Matrix * vector dot product
    virtual Vector<T> operator* (const Vector<T>& rhs) const;
};

// Static T is 0
template <class T>
T TriDiagMatrix<T>::m_zero = 0;

#include "tridiagmatrix.hpp"

#endif
