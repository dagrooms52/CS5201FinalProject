///////////////////////////////////////////////////////////////////////////////
//
// Programmers: Matthew Lindner, Daniel Grooms
// Course: CS5201
// Date: 5/7/2015
// File Name: dirfuncs.hpp
// Purpose: Functions pertaining to the assigned Dirichlet problem
//
///////////////////////////////////////////////////////////////////////////////

#include "dirheader.h"

//u(x, 0) = sin(x)
//u(0, y) = sin(y)
//u(x, pi) = 0
//u(pi, y) = 0

// The given boundaries
template <class T>
T boundary(const T& x, const T& y)
{
  T ret_val = 0;
  
  if (y == 0)
    ret_val = .25 * sin(x);
  else if (x == 0)
    ret_val = .25 * sin(y);
  else if (y == M_PI)
    ret_val = 0;
  else if (x == M_PI)
    ret_val = 0;
  
  return ret_val;
}

// Populate matrix A and vector vect
template <class T, T T_Function(const T&, const T&)>
void populate(SymMatrix<T> & mx, Vector<T> & vect, const int meshSize)
{
  
  // Size check
  if (mx.getSize() != vect.getSize())
  {
    throw(SizeEqualErr(mx.getSize(), vect.getSize()));
  }
  
  if (meshSize < 2)
  {
    throw(RangeErr(meshSize));
  }
  
  for (int row = 0; row < mx.getSize(); row++)
  {
    // Fill A
    for (int column = 0; column <= row; column++)
    {
      if (row == column)
      { 
        mx(row, column) = 1;
      }
      // If this point is either to the left or right 
	    // (which implies it is on the same row)
      else if ((row == column + 1 || row == column - 1) && (row % \
	      (meshSize - 1) > column % (meshSize - 1)))
      {
        mx(row, column) = -.25;
      }
      // If this point is either above or below 
	    // (which implies it is on the same column)
      else if (((column - (meshSize - 1) == row) || (row - (meshSize - 1) \
	      == column)) && (row % (meshSize - 1) == column % (meshSize - 1)))
      {
        mx(row, column) = -.25;
      }
    }
    
    // Fill B
    // If this point is next to the "bottom" of the Dirichlet boundary
    if (row < meshSize - 1)
    {
      vect[row] += T_Function(((M_PI * (row + 1)) / meshSize), 0);
    }
    // If this point is next to the "top" of the Dirichlet boundary
    if (row > pow(meshSize - 1, 2) - meshSize)
    {
      vect[row] += T_Function(M_PI * (row + 1), M_PI);
    }
    
    // If this point is next to the "left" of the Dirichlet boundary
    if (row % (meshSize - 1) == 0)
    {
      vect[row] += T_Function(0, (((row / (meshSize - 1)) + 1) * M_PI / meshSize) );
    }
    // If this point is next to the "right" of the Dirichlet boundary
    if (row % (meshSize - 1) == meshSize - 2)
    {
      vect[row] += T_Function(M_PI, ((((row - ceil(static_cast<double>(meshSize) / 2)) / \
          (meshSize - 1)) + 1) * M_PI / meshSize) );
    }
  }
  
  return;
}

// The actual value of the given PDE at (x, y)
template <class T>
T actualSolution(const T& x, const T& y)
{
  return ((1 / sinh(M_PI)) * ((sin(x)*sinh(M_PI - y)) + ((sin(y) * \
      sinh(M_PI - x)))));
}

// Calculates the actual value of the PDE at our intersection points,
// Outputs the actual values,
// Returns the difference between the actual values, and the approximate values
template <class T, T T_actual(const T&, const T&)>
double compare(Vector<T> & approx, const int meshSize)
{
  Norm norm;
  int size = approx.getSize();
  Vector<T> actual(size);
  T x, y;
  double error;
  
  for (int i = 0; i < size; i++)
  {
    x = M_PI * (((i % (meshSize - 1)) + 1) / (T)meshSize);
    y = M_PI * (((i / (meshSize - 1)) + 1) / (T)meshSize);
    actual[i] = T_actual(x, y);
  }
  
  if(norm(actual) == 0)
    throw(DivZeroErr(0));
  error = abs( (norm(approx) - norm(actual) ) / norm(actual) );

  return error;
}
