////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: cs5201
// File Name: cholesky.hpp
// Date: 4/20/2015
// Purpose: Define a Cholesky function object to perform the Cholesky
//          Decomposition for Symmetric Matrices on input of the form:
//                (SymMatrix, Vector)
// 
////////////////////////////////////////////////////////////////////////////////

#include "cholesky.h"
#include "lmatrix.h"
#include "umatrix.h"

template <class T>
Vector<T> Cholesky::operator()(const SymMatrix<T>& mx, const Vector<T>& vect)
{
  int size = mx.getSize();
  if(size != vect.getSize())
    throw(VectSizeErr(vect.getSize()));

  // L Matrix
  LMatrix<T> decomp(size);
  UMatrix<T> transpose(size);
  Vector<T> answer(size);
  Vector<T> inter(size);

  decomp(0, 0) = sqrt(mx(0, 0));

  for(int i = 1; i < size; i++)
  {
    for(int j = 0; j <= i; j++)
    {
      // stuff here
      decomp(i, j) = mx(i, j);

      for(int k = 0; k < j; k++)
      {
        decomp(i, j) -= (decomp(j, k) * decomp(i, k));
      }

      if(i == j)
      {
        decomp(i, j) = sqrt(abs(decomp(i, j)));
      }
      else
      {
        if(decomp(j, j) == 0)
          throw(DivZeroErr(0));
        decomp(i, j) = (decomp(i, j) / decomp(j, j));
      }
    }
  }
  // decomp done

  // get decomp transpose
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j <= i; j++)
    {
      transpose(j, i) = decomp(i, j);
    }
  }

  // LT * x = y

  // solve Ly = b
  // inter = y
  // vect = b

  for(int i = 0; i < size; i++)
  {
    inter[i] = vect[i];

    for(int j = 0; j < i; j++)
    {
      inter[i] -= (decomp(i, j) * inter[j]);  
    }

    if(decomp(i, i) == 0)
      throw(DivZeroErr(0));
    inter[i] = (inter[i] / decomp(i, i));
  }

  // solve Ux = y
  // inter = y
  // answer = x
  // transpose = U
  
  for(int i = size - 1; i >= 0; i--)
  {
 
    answer[i] = inter[i];

    for(int j = i + 1; j < size; j++)
    {
      answer[i] -= (transpose(i, j) * answer[j]);
    }
    
    if(transpose(i, i) == 0)
      throw(DivZeroErr(0));
    answer[i] = (answer[i] / transpose(i, i));
  }
 
  return answer;
}

