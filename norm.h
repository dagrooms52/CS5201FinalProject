////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// File Name: norm.h
// Course: CS5201
// Date: 2/24/2015
// Purpose: Definition of the Norm functor
//
////////////////////////////////////////////////////////////////////////////////

#ifndef NORM_H
#define NORM_H

#include "vector.h"

// Function: Norm()
// Pre: None
// Post: Norm is constructed
// Description: Default constructor for Norm

// Function: operator()
// Pre: None
// Post: Returns sum of magnitude of elements in vector
// Description: Takes the norm of the elements in the vector

class Norm
{
public:
// Default constructor
Norm();

// Declaration of Norm functor for a vector
template <class T>
double operator()(const Vector<T>& vect);

}; // Norm

#include "norm.hpp"

#endif
