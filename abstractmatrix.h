////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: CS5201
// Date: 3/19/2015
// File Name: abstractmatrix.h
// Purpose: To define an abstract base matrix class that will be used as an 
//          interface for all derivations of matrices
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ABSTRACTMATRIX_H
#define ABSTRACTMATRIX_H

#include "vector.h"

#include <iostream>

template <class T>
class AbstractMatrix
{
  public:
    
    // Read-only subscript operator
    virtual const T& operator() (const int row, const int column) const = 0;

    // Read-write subscript operator
    virtual T& operator() (const int row, const int column) = 0;

    // Vector return using function operator
    virtual Vector<T>& operator() (const int index) = 0;
    
    // Return size of matrix, assuming square
    virtual int getSize() const = 0;

    // Matrix * vector dot product
    virtual Vector<T> operator* (const Vector<T>& rhs) const = 0;

    // Ensure pure virtual
    virtual ~AbstractMatrix() {};

};

// Function: operator<<
// Pre: << is defined for Vector<T>
// Post: Matrix is output row by row, one vector per row
// Description: Outputs any matrix derived from the interface with one vector of 
//              data per row, for readable output
template <class T>
std::ostream& operator<< (std::ostream& out, const AbstractMatrix<T>& mx)
{
  int size = mx.getSize();

  out << "[";
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      out << mx(i, j);
      if( j < size - 1)
        out << ", ";
    }    
    if(i < size - 1)
      out << endl;
  }
  out << "]";

  return out;
}

#endif
