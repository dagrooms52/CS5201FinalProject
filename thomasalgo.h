////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: cs5201
// File Name: thomasalgo.h
// Date: 4/20/2015
// Purpose: Define a ThomasAlgo function object to perform the Thomas
//          algorithm for Tri-Diagonal Matrices on input of the form:
//                (TriDiag, Vector)
//
////////////////////////////////////////////////////////////////////////////////

#ifndef THOMASALGO_H
#define THOMASALGO_H

#include "tridiagmatrix.h"
#include "gserrors.h"

#include <cmath>

class ThomasAlgo
{
  public:
    // Pre: None
    // Post: A ThomasAlgo object is constructed
    // Description: Default constructor for GaussElim class
    ThomasAlgo(){};

    // Pre: Size of mx = size of vect
    // Post: A vector which is the solution to mx * vector = vect is 
    //       returned, as the result of the Thomas Algorithm of TriDiagonal
    //       matrices
    // Description: Performs the Thomas Algorithm for TriDiagonal Matrices on 
    //              the inputs
    template <class T>
    Vector<T> operator()(const TriDiagMatrix<T>& mx, const Vector<T>& vect);
};

#include "thomasalgo.hpp"

#endif
