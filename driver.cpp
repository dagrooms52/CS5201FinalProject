////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms, Matthew Lindner
// Course: CS5201
// Date: 5/7/2015
// File Name: driver.cpp
// Purpose: Driver of the solution for the final program's Dirichlet problem
//
////////////////////////////////////////////////////////////////////////////////

#include "abstractmatrix.h"
#include "cholesky.h"
#include "dirheader.h"
#include "gausselim.h"

#include <cmath>
#include <iostream>

using namespace std;

int main()
{
  // Variable declarations

  int size, mxSize;
  long double error;

  Cholesky cho;
  GaussElim gauss;
  
  Vector<long double> choAnswer;
  Vector<long double> gaussAnswer;

  // Take input for the Dirichlet mesh size
  // Compute matrix and vector size, and initialize these structures
  
  cout << "Mesh size (greater than 1): ";

  do
  {
    cin >> size;

    if(size < 2)
      cout << "Please input a mesh size greater than 1" << endl;
  
  }while(size < 2);
  
  mxSize = pow(size - 1, 2);

  SymMatrix<long double> sym(mxSize);
  Vector<long double> symRhs(mxSize, 0);

  // Populate the values of the matrix and vector via references

  populate<long double, boundary>(sym, symRhs, size);

  // Output of the populated symmetric matrix and associated vector

  cout << endl << "Populated Matrix:" << endl;
  cout << sym << endl << endl;

  cout << "Populated Vector" << endl;
  cout << symRhs << endl << endl;

  // Cholesky decomposition solution of the symmetric matrix and vector

  cout << "--------------------------------------" << endl << endl;
  cout << "Cholesky Decomposition of the matrix: " << endl;
  try
  {
    choAnswer = cho(sym, symRhs);
    for(int i = 0; i < size-1; i++)
    {
      cout << "[";
      for(int j = 0; j < size-1; j++)
      {
        cout << choAnswer[(size-1) * i + j];
        if(j < size - 2)
          cout << ", ";
        else
          cout << "]" << endl;
      }
    }

    cout << endl;
  
    error = compare<long double, actualSolution>(choAnswer, size);
    cout << "Error of Cholesky solution mesh: " << error * 100.0 << "%" << endl << endl;

  }
  catch(VectSizeErr e)
  {
    cerr << "Error: Vector size not equal to matrix size in Cholesky Decomposition" << endl;
  }
  catch(ZeroVectorErr z)
  {
    cerr << "Error: Zero vector in input matrix in Cholesky Decomposition" << endl;
  }
  catch(RangeErr e)
  {
    cerr << "Range error in Cholesky Decomposition, bad range: " << e.badIndex();
    cerr << endl;
  }
  catch(SizeEqualErr s)
  {
    cerr << "Size error in Cholesky Decomposition, bad sizes: ";
    cerr << s.badSize1() << " " << s.badSize2() << endl;
  }
  catch(DivZeroErr d)
  {
    cerr << "Division by zero in Cholesky Decomposition." << endl;
  }

  // Gaussian elimination of the same symmetric matrix and vector

  cout << "-----------------------------------" << endl << endl;
  cout << "Gaussian Elimination of the matrix: " << endl;

  try
  {
    gaussAnswer = gauss(sym, symRhs);

    for(int i = 0; i < size-1; i++)
    {
      cout << "[";
      for(int j = 0; j < size-1; j++)
      {
        cout << gaussAnswer[(size-1) * i + j];
        if(j < size - 2)
          cout << ", ";
        else
          cout << "]" << endl;
      }
    }

    cout << endl;

    error = compare<long double, actualSolution>(gaussAnswer, size);
    cout << "Error of Gaussian solution mesh: " << error * 100.0 << "%" << endl << endl;

  }
  catch(VectSizeErr e)
  {
    cerr << "Error: Vector size not equal to matrix size in \
        Gaussian Elimination" << endl;
  }
  catch(ZeroVectorErr z)
  {
    cerr << "Error: Zero vector in input matrix in Gaussian Elimination" \
        << endl;
  }
  catch(RangeErr e)
  {
    cerr << "Range error in Gaussian ELimination, bad range: " << \
        e.badIndex() << endl;
  }
  catch(SizeEqualErr s)
  {
    cerr << "Size error in Gaussian Elimination, bad sizes: ";
    cerr << s.badSize1() << " " << s.badSize2() << endl;
  }
  catch(DivZeroErr d)
  {
    cerr << "Division by zero in Gaussian Elimination." << endl;
  }                  

  return 0;
}
