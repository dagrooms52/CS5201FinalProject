////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Date: 3/8/2015
// Course: CS5201
// File Name: vector.h
// Purpose: To implement a vector class
//
////////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR_H
#define VECTOR_H

#include "vecterrors.h"

#include <iostream>

// Function: Vector<T>()
// Pre: None
// Post: A vector object is created, m_ptrToData is NULL, m_size is 0
// Description: Creates an empty vector object

// Function: Vector<T>(size, fill)
// Pre: int size > 0
// Post: A vector of size "size" is created, each value in array = fill 
// Description: Creates a vector of specified size, filled with "fill" value

// Function: Vector(size)
// Pre: int size > 0
// Post: A vector of size "size" is created
// Description: Creates an empty vector with the specified size

// Function: ~Vector()
// Pre: None
// Post: If Vector.m_ptrToData != NULL, delete m_ptrToData
// Description: Deletes the dynamic array pointed to by m_ptrToData

// Function: operator=(Vector<T>)
// Pre: rhs.m_size > 0, rhs.m_ptrToData != NULL
// Post: The calling Vector has the same size as rhs, m_ptrToData points to
//       an array with equivalent data via deep copy
// Description: Performs deep copy of rhs vector into calling vector

// Function: operator=(T fill)
// Pre: m_size > 0, m_ptrToData != NULL
// Post: Each element in array pointed to by m_ptrToData = fill value
// Description: Fills the calling vector with the T value

// Function: Vector(Vector<T> cpy)
// Pre: None
// Post: If cpy size > 0 and cpy ptrToData != NULL, performs deep copy of
//       data in cpy.m_ptrToData. If not, creates empty vector with
//       m_size = 0, m_ptrToData = NULL
// Description: Performs deep copy of passed vector into calling vector

// Function: getSize()
// Pre: None
// Post: returns size of calling object
// Description: Returns the size of the calling vector

// Function: operator[] const
// Pre: int index >= 0, index < m_size
// Post: const value at m_ptrToData is returned
// Description: Returns a const reference to the value at the given index 
//              of the calling vector

// Function: operator<<
// Pre: vector size > 0
// Post: Vector is output to the stream in form (1, 2, ..., n) 
// Description: Outputs the vector in readable format

// Function: isMultiple()
// Pre: The two vectors have equal size
// Post: Returns true if a constant k * other = calling vector, false otherwise
// Description: Applies a formula to return true if the passed vector is a
//              multiple of the calling vector, false otherwise

// Function: operator==
// Pre: != must be defined for T != T, both vectors are of equal size
// Post: Return true if each corresponding element of both vectors is equal, 
//       false otherwise
// Description: Returns true if vectors are equal, if the elements at equal 
//              positions are equal

// Function: operator!=
// Pre: != must be defined for T != T, both vectors are of equal size
// Post: Return opposite of similar == call; false if each corresponding element
//       of both vectors is equal, true otherwise
// Description: Returns the opposite of the == call between the two vectors
//              False if the vectors are equal, true otherwise

// Function: max()
// Pre: abs(T) must be defined for T
// Post: Returns the largest of the absolute values of all values in the vector
// Description: The maximum absolute value in the vector is returned

// Function: operator[]
// Pre: int index >= 0, index < m_size
// Post: reference to value at m_ptrToData[index] is returned
// Description: Returns a reference to the value at the given vector index

// Function: operator>>
// Pre: 0 <= m_numElts < m_size
// Post: m_ptrToData[m_numElts] = stream input
// Description: Fills vector from position 0 with stream input

// Function: operator*(Vector<T>)
// Pre: Both vector sizes are equal, both ptrToData != NULL
// Post: Returns a type T variable, the sum of the multiplication of each 
//       corresponding element of the two vectors
// Description: Computes the dot product of the two vectors

// Function: operator*(double scalar)
// Pre: m_size > 0, T * double is defined
// Post: Returns a Vector<T> whose elements are the product of the corresponding
//       elements of the calling vector and the passed scalar
// Description: Scalar multiplication of a vector, each element is multiplied
//              by the scalar and a copy is returned

// Function: operator-(Vector<T> vect)
// Pre: Calling vector.m_size > 0 and m_ptrToData != NULL, T * -1 is defined
// Post: Returns a vector whose elements are the opposite of the corresponding
//       elements of the calling vector
// Description: Returns a copy of the calling vector whose elements are 
//              opposite of those of the calling vector

// Function: operator-(Vector<T> rhs) const
// Pre: m_size of calling vector and rhs are equal and > 0,
//      both m_ptrToData != NULL
// Post: A vector is returned with size = m_size such that a value at 
//       index i = calling vector[i] - rhs[i] for all indices i
// Description: Returns a vector as the result of subtraction of the 
//              passed vector from the calling vector

// Function: operator+
// Pre: m_size of calling vector and rhs are equal and > 0, 
//      both m_ptrToData != NULL
// Post: A vector is returned with size = m_size such that a value at 
//       index i = calling vector[i] + rhs[i] for all indices i
// Description: Returns a vector as the result of addition of the calling 
//              vector and the passed vector

// Function: swap(int index1, int index2)
// Pre: indices both > 0, both < m_size
// Post: values at index1 and index2 are switched in array pointed to by 
//       m_ptrToData
// Description: Swaps the values of the vector at the specified indices

template <class T>
class Vector
{
  private:
    T* m_ptrToData;
    int m_size;
    int m_numElts;

  public:
    
    // Default constructor
    Vector<T>();

    // Fill constructor
    Vector<T>(const int size, const T fill);

    // Empty constructor with size
    Vector<T>(const int size);

    // Destructor
    ~Vector<T>();

    // Vector = operator
    Vector<T>& operator= (const Vector<T> & rhs);

    // Scalar = operator
    Vector<T>& operator= (const T& fill);

    // Copy constructor
    Vector<T>(const Vector<T> & cpy);

    ///////////////////////
    // --- Accessors --- //
    ///////////////////////

    // Get the vector's size, number of elements
    int getSize() const;

    // Read-only operator[]
    const T& operator[] (const int index) const;

    // Output operator
    template <class U>
    friend std::ostream& operator<< (std::ostream& out, const Vector<U>& vect);

    // Check if one vector is a multiple of another
    bool isMultiple(const Vector<T>& other) const;

    // == operator
    bool operator== (const Vector<T>& rhs) const;

    // != operator
    bool operator!= (const Vector<T>& rhs) const;

    // Max -> return max of absolute of all values in vector
    T max() const;

    //////////////////////
    // --- Mutators --- //
    //////////////////////

    // Read-write operator[]
    T& operator[] (const int index);
    
    // >> input operator
    template <class U>
    friend std::istream& operator>> (std::istream& in, Vector<U>& vect);

    // Dot product between two vectors
    T operator* (const Vector<T>& rhs) const;

    // Scalar multiplication of a vector
    Vector<T> operator* (const double scalar) const;

    // Unary opposite, opposite of vect
    template <class U>
    friend Vector<U> operator- (const Vector<U>& vect);

    // Binary -, subtraction operator for two vectors
    Vector<T> operator- (const Vector<T>& rhs) const;

    // Addition operator for two vectors
    Vector<T> operator+ (const Vector<T>& vect) const;
 
    // Swaps the element at index 1 with that at index 2
    void swap (const int index1, const int index2);

}; // Vector<T>

#include "vector.hpp"

#endif
