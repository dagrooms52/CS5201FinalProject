////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: cs5201
// File Name: gausselim.h
// Date: 3/8/2015
// Purpose: Define a GaussElim function object to solve a system of equations
//          of the input form (matrix, vector)
//
////////////////////////////////////////////////////////////////////////////////

#ifndef GAUSSELIM_H
#define GAUSSELIM_H

#include "vector.h"
#include "gserrors.h"
#include "abstractmatrix.h"
#include "matrix.h"

#include <iostream>
#include <cmath>

class GaussElim
{
  public:
    // Pre: None
    // Post: A GaussElim object is constructed
    // Description: Default constructor for GaussElim class
    GaussElim();

    // Pre: mx and vect are of same size, no row of mx is a zero vector
    // Post: Gaussian Elimination with Scaled Partial Pivoting is performed 
    //       on the inputs to solve the equation:
    //       [mx]*[b] = [vect]
    //       Returns the answer vector [b], with elements of magnitude less
    //       than .000001 (10^-6) rounded to zero.
    // Description: Performs Gaussian Elimination with Scaled Partial Pivoting
    //              on the mx and vect inputs, according to the formula 
    //              described in "Post"
    template <class T>
    Vector<T> operator()(const AbstractMatrix<T>& mx, const Vector<T> vect);
}; // GaussElim

#include "gausselim.hpp"

#endif

