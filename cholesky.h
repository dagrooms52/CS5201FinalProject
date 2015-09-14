////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: cs5201
// File Name: cholesky.h
// Date: 4/20/2015
// Purpose: Define a Cholesky function object to perform the Cholesky
//          Decomposition for Symmetric Matrices on input of the form:
//                (SymMatrix, Vector)
//
////////////////////////////////////////////////////////////////////////////////

#ifndef CHOLESKY_H
#define CHOLESKY_H

#include "symmatrix.h"
#include "gserrors.h"

#include <cmath>

class Cholesky
{
  public:
    // Pre: None
    // Post: A Cholesky object is constructed
    // Description: The default constructor for Cholesky class
    Cholesky(){};

    // Pre: mx and vect are the same size
    // Post: A vector that solves mx * vector = vect is returned
    // Description: Performs the Cholesky Decomposition for Symmetric
    //              Matrices on the input, as well as forward and backward
    //              substitution on the resulting matrices from the 
    //              decomposition, returning the resulting vector.
    template <class T>
    Vector<T> operator()(const SymMatrix<T>& mx, const Vector<T>& vect);
};

#include "cholesky.hpp"

#endif
