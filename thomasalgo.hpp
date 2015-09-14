////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: cs5201
// File Name: thomasalgo.hpp
// Date: 4/20/2015
// Purpose: Define a ThomasAlgo function object to perform the Thomas
//          algorithm for Tri-Diagonal Matrices on input of the form:
//                (TriDiag, Vector)
//
///////////////////////////////////////////////////////////////////////////////

#include "thomasalgo.h"

using namespace std;

template <class T>
Vector<T> ThomasAlgo::operator()(const TriDiagMatrix<T>& mx, const Vector<T>& vect)
{

  int size = mx.getSize();
  if(size != vect.getSize())
    throw(VectSizeErr(vect.getSize()));

  // c vector
  const Vector<T> top = mx(0);
  // b vector
  const Vector<T> mid = mx(1);
  // a vector starts at a2, index at -1
  const Vector<T> bot = mx(2);

  // x vector
  Vector<T> answer(size);
  
  // d vector is input "vect"

  // c prime vector
  Vector<T> topPrime(size - 1);
  if(mid[0] == 0)
    throw(DivZeroErr(0));
  topPrime[0] = top[0] / mid[0];

  // d prime vector
  Vector<T> rhsPrime(size);
  if(mid[0] == 0)
    throw(DivZeroErr(0));
  rhsPrime[0] = vect[0] / mid[0];

  // Forward sweep - modifies topPrime and rhsPrime
  for(int i = 1; i < size - 1; i++)
  {
    if(!(mid[i] - (bot[i-1] * topPrime[i-1])))
      throw(DivZeroErr(0));
    topPrime[i] = top[i] / (mid[i] - (bot[i-1] * topPrime[i-1]));
  }

  for(int i = 1; i < size; i++)
  {
    if(!(mid[i] - (bot[i-1] * topPrime[i-1])))
      throw(DivZeroErr(0));
    rhsPrime[i] = ((vect[i] - (bot[i-1] * rhsPrime[i-1]))/(mid[i] - 
                  (bot[i-1] * topPrime[i-1])));
  }

  // Back Substitution - modifies answer
  answer[size - 1] = rhsPrime[size - 1];
  for(int i = size - 2; i >= 0; i--)
  {
    answer[i] = rhsPrime[i] - (topPrime[i] * answer[i+1]);
  }

  return answer;
}
