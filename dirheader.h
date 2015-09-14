///////////////////////////////////////////////////////////////////////////////
//
// Programmers: Matthew Lindner, Daniel Grooms
// Course: CS5201
// Date: 5/7/2015
// File Name: dirheader.h
// Purpose: Include header for functions pertaining to the assigned 
//          Dirichlet problem
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DIRHEADER_H
#define DIRHEADER_H

#include "symmatrix.h"
#include "vector.h"
#include "norm.h"
#include "gserrors.h"
#include <cmath>
#include <iostream>

// Pre: None
// Post: The value of the Dirichlet problem at the given boundary is returned
//       Returns 0 if the (x, y) pair is not on the domain boundary
// Description: Returns the value of the given Dirichlet problem for Poisson
//              equation on the boundary of the problem domain
template <class T>
T boundary(const T& x, const T& y);

// Pre: Size of mx equals size of vect, meshSize is greater than 1
// Post: mx and vect are populated with appropriate values from the Dirichlet
//       problem calculations
// Description: Populates the passed matrix and vector with the values 
//              according to the application of the Dirichlet problem 
template <class T, T T_Function(const T&, const T&)>
void populate(SymMatrix<T> & mx, Vector<T> & vect, const int meshSize);

// Pre: None
// Post: The value of the actual solution to the given Dirichlet problem is 
//       returned at the passed (x, y) pair
// Description: Returns the correct value of the mesh at the given point
template <class T>
double actualSolution(const T& x, const T& y);

// Pre: norm(actual) is not equal to zero, or actual has a nonzero member
// Post: Percent error of the approximated mesh versus the true values is 
//       returned
// Description: Returns the true percent error of the approximated mesh using
//              a function callback to compare the approximation with the 
//              actual solution
template <class T, T T_actual(const T&, const T&)>
double compare(Vector<T> & approx, const int meshSize);

#include "dirfuncs.hpp"

#endif


