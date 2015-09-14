////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: CS5201
// Date: 3/3/2015
// File Name: matrix.hpp
// Purpose: Implement the matrix class
//
////////////////////////////////////////////////////////////////////////////////

#include "matrix.h"

#include <iostream>
using namespace std;

// Default constructor
template <class T>
Matrix<T>::Matrix()
{
  m_rows = 0;
  m_cols = 0;
  m_data = NULL;
}

// Size constructor
template <class T>
Matrix<T>::Matrix(const int size)
{
  m_rows = size;
  m_cols = m_rows;

  if(size < 1)
    throw(RangeErr(size));

  // New array of vectors
  m_data = new Vector<T> [size];
  for(int i = 0; i < size; i++)
  {
    Vector<T> init(size);
    m_data[i] = init; 
  }
}

// Destructor
template <class T>
Matrix<T>::~Matrix()
{
  m_rows = 0;
  m_cols = 0;

  if(m_data != NULL)
  {
    delete[] m_data;
  }
}

// Copy constructor
template <class T>
Matrix<T>::Matrix(const Matrix<T> & cpy)
{
  if(cpy.m_rows > 0 && cpy.m_data != NULL)
  {
    m_rows = cpy.m_rows;
    m_cols = m_rows;
    m_data = new Vector<T>[m_rows];
    for(int i = 0; i < m_rows; i++)
    {
      Vector<T> init(m_rows);
      init = cpy.m_data[i];
      m_data[i] = init;
    }
  }
  else
  {
    m_rows = 0; 
    m_cols = 0;
    m_data = NULL;
  }
}

// Overload assignment operator
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> & rhs)
{
  if(m_data != NULL)
    delete[] m_data;

  if(rhs.m_rows > 0 && rhs.m_data != NULL)
  {
    m_rows = rhs.m_rows;
    m_cols = m_rows;
    m_data = new Vector<T> [m_rows];

    for(int i = 0; i < m_rows; i++)
    {
      Vector<T> init(m_rows);
      init = rhs.m_data[i];
      m_data[i] = init;
    }
  }
  else
  {
    m_rows = 0;
    m_cols = 0;
    m_data = NULL;
  }

  return (*this);
}

// Assignment operator through interface
// + must be defined for Matrix + interface
template <class T>
Matrix<T>& Matrix<T>::operator=(const AbstractMatrix<T>& rhs)
{
  int size = rhs.getSize();

  Matrix<T> result(size);
  
  // Result is full of zero, from vector constructor
  result = result + rhs;
  (*this) = result;

  return (*this);
}

///////////////////////
// --- Accessors --- //
///////////////////////

// Get matrix size, assuming square matrix
template <class T>
int Matrix<T>::getSize() const
{
  return m_rows;
}

// Const () operator
template <class T>
const T& Matrix<T>::operator() (const int row, const int column) const
{
  if(m_data != NULL && row >= 0 && row < m_rows && column >=0 && column < m_rows)
  {
    return m_data[row][column];
  }
  else
  {
    throw(RangeErr(row));
  }
}

//////////////////////
// --- Mutators --- //
//////////////////////

// Input operator >>
template <class T>
istream& operator>> (istream& in, Matrix<T>& mx)
{
  if(mx.m_rows > 0 && mx.m_data != NULL)
  {
    for(int i = 0; i < mx.m_rows; i++)
    {
      in >> mx.m_data[i];
    }
  }

  return in;
}

// Read - write operator ()
template <class T>
T& Matrix<T>::operator() (const int row, const int column)
{
  if(m_data == NULL || row < 0 || row >= m_rows || column < 0 || column > m_rows)
  {
    throw(RangeErr(row));
  }

  return m_data[row][column];
}

// Vector return using function operator
template <class T>
Vector<T>& Matrix<T>::operator() (const int index)
{
  if(index < 0 || index > m_rows)
    throw(RangeErr(index));

  return m_data[index];
}

// Matrix + matrix addition operator
template <class T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& mx) const
{
  if(m_rows != mx.m_rows || m_data == NULL || mx.m_data == NULL)
  {
    throw(SizeEqualErr(m_rows, mx.m_rows));
  }

  Matrix<T> holder(m_rows);
  for(int i = 0; i < m_rows; i++)
  {
    holder(i) = m_data[i] + mx.m_data[i];
  }

  return holder;
}

// Matrix - matrix subtraction operator
template <class T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& mx) const
{
  if(m_rows != mx.m_rows || m_data == NULL || mx.m_data == NULL)
  {
    throw(SizeEqualErr(m_rows, mx.m_rows));
  }

  Matrix<T> holder(m_rows);
  for(int i = 0; i < m_rows; i++)
  {
    holder[i] = m_data[i] - mx.m_data[i];
  }

  return holder;
}

// Matrix transpose
template <class T>
Matrix<T> Matrix<T>::transpose() const
{
  Matrix<T> holder(m_rows);
  
  if(m_rows < 0 || m_data == NULL)
  {
    throw(RangeErr(1));
  }

  // Transpose is calculated by interchanging the rows with the columns, 
  // so interchanging indices i and j in the following loops
  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < m_rows; j++)
    {
      holder(i, j) = m_data[j][i];
    }
  }

  return holder;  
}


// Matrix * matrix dot product
template <class T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& rhs) const
{
  if(m_rows != rhs.m_rows || m_data == NULL || rhs.m_data == NULL)
  {
    throw(SizeEqualErr(m_rows, rhs.m_rows));
  }

  // Transpose of rhs allows for simple vector dot product
  // because a row of transpose is a column in original
  Matrix<T> mult(rhs);
  mult = mult.transpose();

  Matrix<T> holder(m_rows);
  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < m_rows; j++)
    {
      holder(i, j) = m_data[i] * mult.m_data[j];  
    }
  }

  return holder;
}

// Matrix * vector multiplication operator
template <class T>
Vector<T> Matrix<T>::operator* (const Vector<T>& rhs) const
{
  if(rhs.getSize() < 0 || rhs.getSize() != m_rows || m_data == NULL)
  {
    throw(SizeEqualErr(m_rows, rhs.getSize()));
  }

  Vector<T> hold(rhs.getSize());
  for(int i = 0; i < m_rows; i++)
  {
    hold[i] = m_data[i] * rhs;
  }

  return hold;
}

// Matrix * scalar multiplication operator
template <class T>
Matrix<T> Matrix<T>::operator* (const T scalar) const
{
  Matrix<T> holder(*this);
  for(int i = 0; i < m_rows; i++)
  {
    holder(i) = holder(i) * scalar;
  }
  
  return holder;
}

// Swap two rows of the matrix
template <class T>
void Matrix<T>::swap(const int index1, const int index2)
{
  if(m_data == NULL)
    throw(RangeErr(1));
  if(index1 < 0 || index1 > m_rows)
    throw(RangeErr(index1));
  if(index2 < 0 || index2 > m_rows)
    throw(RangeErr(index2));

  Vector<T> temp(m_data[index1]);
  m_data[index1] = m_data[index2];
  m_data[index2] = temp;

  return;
}

///////////////
// Interface //
///////////////

// Add matrix to other matrices through interface
template <class T>
Matrix<T> Matrix<T>::operator+ (const AbstractMatrix<T>& rhs) const
{
  if(m_rows != rhs.getSize())
    throw(SizeEqualErr(m_rows, rhs.getSize()));

  Matrix<T> answer(m_rows);

  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < m_rows; j++)
    {
      answer(i, j) = (*this)(i, j) + rhs(i, j);
    }
  }

  return answer;
}

// Subtract other matrices from calling object through interface
template <class T>
Matrix<T> Matrix<T>::operator- (const AbstractMatrix<T>& rhs) const
{
  if(m_rows != rhs.getSize())
    throw(SizeEqualErr(m_rows, rhs.getSize()));

  Matrix<T> answer(*this);

  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < m_rows; j++)
    {
      answer(i, j) -= rhs(i, j);
    }
  }

  return answer;
}

// Multiply the matrix with other matrices through the interface
template <class T>
Matrix<T> Matrix<T>::operator* (const AbstractMatrix<T>& rhs) const
{
  if(m_rows != rhs.getSize())
    throw(SizeEqualErr(m_rows, rhs.getSize()));

  Matrix<T> answer(rhs.getSize());

  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < m_rows; j++)
    {
      answer(i, j) = 0;
      for(int k = 0; k < m_rows; k++)
      {
        answer(i, j) += (*this)(i, k) * rhs(k, j);
      }
    }
  }

  return answer;
}
