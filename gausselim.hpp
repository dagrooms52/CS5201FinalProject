////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: cs5201
// File Name: gausselim.hpp
// Date: 3/8/2015
// Purpose: GaussElim member function implementation
//
////////////////////////////////////////////////////////////////////////////////

#include "gausselim.h"

using namespace std;

// Default constructor
GaussElim::GaussElim()
{
  return;
}

template <class T>
Vector<T> GaussElim::operator()(const AbstractMatrix<T>& matrix, const Vector<T> vect)
{
  // Copy matrix and vector inputs to perform calculations
  Matrix<T> mx(matrix.getSize());
  mx = matrix;
  Vector<T> rhs = vect;

  int size = mx.getSize();
  int max, row;

  Vector<T> answer(size);

  if(mx.getSize() != rhs.getSize())
  {
    throw(VectSizeErr(rhs.getSize()));
  }

  // Forward elimination loop
  for(int i = 0; i < size - 1; i++)
  {
    // Pivot calculation
    max = 0;
    row = 0;
    for(int j = i; j < size; j++)
    {
      if(mx(j).max() == 0)
      {
        throw(ZeroVectorErr(0));
      }
      
      if((abs(mx(j, i)) / mx(j).max()) > max)
      {
        max = abs(mx(j, i)) / mx(j).max();
        row = j;
      }
    }
    mx.swap(i, row);
    rhs.swap(i, row);

    // Forward elimination
    for(int j = i + 1; j < size; j++)
    {
      for(int k = i + 1; k < size; k++)
      {
        mx(j, k) = mx(j, k) - (mx(i, k) * (mx(j, i) / mx(i, i)));
      }
      // Update rhs vector
      rhs[j] = rhs[j] - (rhs[i] * (mx(j, i) / mx(i, i)));
      mx(j, i) = 0; 
    }
  }

  // Backward substitution loop
  for(int i = size - 1; i >= 0; i--)
  {
    answer[i] = rhs[i];
    for(int j = size - 1; j >= i; j--)
    {
      if(i == j)
      {
        if(mx(i, j) == 0)
        {
          throw(DivZeroErr(0));
        }
        answer[i] = answer[i] / mx(i, j);
      }
      else
      {
        answer[i] = answer[i] - (mx(i, j) * answer[j]);
      }
    }
  }

  // Rounding loop, tolerance = 10 ^ -6
  for(int i = 0; i < answer.getSize(); i++)
  {
    if(abs(answer[i]) < .000001)
      answer[i] = 0;
  }
  
  return answer;
}
