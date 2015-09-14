////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// File Name: norm.hpp
// Course: CS 5201
// Date: 2/11/2015
// Purpose: Norm class definition
//          Norm is a functor to compute the norm of a Vector of Vectors
//
////////////////////////////////////////////////////////////////////////////////

#include "norm.h"
#include <cmath>

using namespace std;

Norm::Norm()
{
  return;
}

template <class T>
double Norm::operator()(const Vector<T>& vect)
{
  int size = vect.getSize();
  double sum = 0.0;

  // Sums squares of each element of the vector
  for(int i = 0; i < size; i++)
  {
    sum += vect[i] * vect[i];
  }

  sum = sqrt(sum);

  return sum;
}
