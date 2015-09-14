////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: CS5201
// Date: 3/30/2015
// File Name: lmatrix.hpp
// Purpose: To implement the Lower Triangle Matrix class LMatrix
//
////////////////////////////////////////////////////////////////////////////////

#include "lmatrix.h"

#include <iostream>
using namespace std;

// Default constructor
template <class T>
LMatrix<T>::LMatrix()
{
  m_data = NULL;
  m_size = 0;
}

// Size Constructor
template <class T>
LMatrix<T>::LMatrix(const int size)
{
  m_size = size;

  if(size < 1)
    throw(RangeErr(size));

  m_data = new Vector<T> [size];
  for(int i = 0; i < size; i++)
  {
    Vector<T> init(i + 1);
    m_data[i] = init;
  }
}

// Destructor
template <class T>
LMatrix<T>::~LMatrix<T>()
{
  if(m_data != NULL)
  {
    delete[] m_data;
  }
}

// Assignment operator
template <class T>
LMatrix<T>& LMatrix<T>::operator= (const LMatrix<T>& rhs)
{
  if(m_data != NULL)
    delete[] m_data;

  if(rhs.getSize() > 0)
  {
    m_size = rhs.getSize();
    m_data = new Vector<T> [m_size];

    for(int i = 0; i < m_size; i++)
    {
      Vector<T> init(i + 1);
      init = rhs.m_data[i];
      m_data[i] = init;
    }
  }
  else
  {
    m_size = 0;
    m_data = NULL;
  }

  return (*this);
}

// Copy constructor
template <class T>
LMatrix<T>::LMatrix(const LMatrix<T> & cpy)
{
  if(cpy.getSize() > 0)
  {
    *this = cpy;
  }
  else
  {
    m_size = 0;
    m_data = NULL;
  }
}

//////////////////////
// --- Mutators --- //
//////////////////////

// Input operator
template <class T>
istream& operator>> (istream& in, LMatrix<T>& mx)
{
  T buffer;
  int size = mx.getSize();

  if(size > 0 && mx.m_data != NULL)
  {
    for(int i = 0; i < size; i++)
    {
      for(int j = 0; j < size; j++)
      {
        // Separates input over the diagonal into buffer
        if(j > i)
          in >> buffer;
        else
          in >> mx(i, j);
      }
    }
  }

  return in;
}

// LMatrix addition - more needed
template <class T>
LMatrix<T> LMatrix<T>::operator+ (const LMatrix<T>& mx) const
{
  if(m_size != mx.getSize())
    throw(SizeEqualErr(m_size, mx.getSize()));

  LMatrix<T> holder(m_size);
  for(int i = 0; i < m_size; i++)
  {
    // this is efficient - each aligning vector is of the same size
    holder(i) = m_data[i] + mx.m_data[i];
  }

  return holder;
}

// LMatrix subtraction - more needed
template <class T>
LMatrix<T> LMatrix<T>::operator- (const LMatrix<T>& mx) const
{
  if(m_size != mx.getSize())
    throw(SizeEqualErr(m_size, mx.getSize()));

  LMatrix<T> holder(m_size);
  for(int i = 0; i < m_size; i++)
  {
    holder(i) = m_data[i] - mx.m_data[i];
  }

  return holder;
}

// LMatrix multiplication - more needed
template <class T>
LMatrix<T> LMatrix<T>::operator* (const LMatrix<T>& rhs) const
{
  if(m_size != rhs.getSize())
    throw(SizeEqualErr(m_size, rhs.getSize()));

  LMatrix<T> answer(m_size);
  
  for(int i = 0; i < m_size; i++)
  {
    for(int j = 0; j <= i; j++)
    {
      answer(i, j) = 0; 
      
      for(int k = 0; k <= i; k++)
      {
        answer(i, j) += (*this)(i, k) * rhs(k, j);
      }
    }
  }

  return answer;
}

// Scalar multiplication - only 1
template <class T>
LMatrix<T> LMatrix<T>::operator* (const T scalar) const
{
  LMatrix<T> holder(*this);
  for(int i = 0; i < m_size; i++)
  {
    holder(i) = holder(i) * scalar;
  }

  return holder;
}

///////////////////////
// --- Inherited --- //
///////////////////////

// Read-only subscript operator
template <class T>
const T& LMatrix<T>::operator() (const int row, const int column) const
{
  if(row < 0 || row >= m_size)
  {
    throw(RangeErr(row));
  }
  if(column < 0 || column >= m_size)
  {
    throw(RangeErr(column));
  }

  if(column > row)
  { 
    return m_zero;
  }
  else
  {
    return m_data[row][column];
  }
}

// Read-write subscript operator
template <class T>
T& LMatrix<T>::operator() (const int row, const int column)
{
  if(row < 0 || row >= m_size)
  {
    throw(RangeErr(row));
  }
  if(column < 0 || column >= m_size)
  {
    throw(RangeErr(column));
  }

  if(row < column)
  {
    return m_zero;
  }
  else
  {
    return m_data[row][column];
  }
}

// Vector return using function operator
template <class T>
Vector<T>& LMatrix<T>::operator() (const int index)
{
  if(index < 0 || index >= m_size)
  {
    throw(RangeErr(index));
  }

  return m_data[index];
}

// Return size of matrix, assuming square
template <class T>
int LMatrix<T>::getSize() const
{
  return m_size;
}

// Matrix * vector dot product
template <class T>
Vector<T> LMatrix<T>::operator* (const Vector<T>& rhs) const
{
  if(rhs.getSize() != m_size)
  {
    throw(SizeEqualErr(rhs.getSize(), m_size));
  }
  
  Vector<T> answer(m_size);

  for(int i = 0; i < m_size; i++)
  {
    answer[i] = 0;
    for(int j = 0; j < i; j++)
    {
      answer[i] += m_data[i][j] * rhs[j];
    }
  }

  return answer;
}
