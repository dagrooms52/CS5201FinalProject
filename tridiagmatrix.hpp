////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: CS5201
// Date: 4/20/2015
// File Name: tridiagmatrix.hpp
// Purpose: To implement the Tri-Diagonal Matrix class TriDiagMatrix
//
////////////////////////////////////////////////////////////////////////////////

#include "tridiagmatrix.h"

using namespace std;

// Size constructor
template <class T>
TriDiagMatrix<T>::TriDiagMatrix(const int size)
{
  if(size > 0)
  {
    m_size = size;
    m_data = new Vector<T> [3];
    Vector<T> mid(size);
    Vector<T> bot(size - 1);
    m_data[0] = bot;
    m_data[1] = mid;
    m_data[2] = bot;
  }
  else
  {
    throw(RangeErr(size));
  }
}

// Destructor
template <class T>
TriDiagMatrix<T>::~TriDiagMatrix<T>()
{
  if(m_data != NULL)
    delete[] m_data;
}

// Assignment operator
template <class T>
TriDiagMatrix<T>& TriDiagMatrix<T>::operator= (const TriDiagMatrix<T>& rhs)
{
  if(m_data != NULL)
    delete[] m_data;

  if(rhs.getSize() > 0)
  {
    m_size = rhs.getSize();
    m_data = new Vector<T> [3];
    for(int i = 0; i < 3; i++)
    {
      m_data[i] = rhs.m_data[i];
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
TriDiagMatrix<T>::TriDiagMatrix(const TriDiagMatrix<T> & cpy)
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

// Input operator
template <class T>
istream& operator>> (istream& in, TriDiagMatrix<T>& mx)
{
  T buffer;
  int size = mx.getSize();

  if(size > 0)
  {
    for(int i = 0; i < size; i++)
    {
      for(int j = 0; j < size; j++)
      {
        if(i > (j + 1) || j > (i + 1))
          in >> buffer;
        else
          in >> mx(i, j);
      }
    }
  }

  return in;
}

// TriDiagMatrix addition
template <class T>
TriDiagMatrix<T> TriDiagMatrix<T>::operator+ (const TriDiagMatrix<T>& mx) const
{
  if(m_size != mx.getSize())
    throw(SizeEqualErr(m_size, mx.getSize()));

  TriDiagMatrix<T> holder(m_size);
  for(int i = 0; i < 3; i++)
  {
    // Add each vector
    holder(i) = m_data[i] + mx.m_data[i];
  }

  return holder;
}

// TriDiagMatrix subtraction
template <class T>
TriDiagMatrix<T> TriDiagMatrix<T>::operator- (const TriDiagMatrix<T>& mx) const
{
  if(m_size != mx.getSize())
    throw(SizeEqualErr(m_size, mx.getSize()));

  TriDiagMatrix<T> holder(*this);
  for(int i = 0; i < m_size; i++)
  {
    holder(i) = holder(i) - mx(i);
  }

  return holder;
}

/*
// TriDiagMatrix multiplication
template <class T>
Matrix<T> TriDiagMatrix<T>::operator* (const TriDiagMatrix<T>& rhs) const
{
  if(m_size != rhs.getSize())
    throw(SizeEqualErr(m_size, rhs.getSize()));

  Matrix<T> answer = (*this);
  Matrix<T> right = rhs;

  return (answer * rhs);
}
*/

// Scalar multiplication
template <class T>
TriDiagMatrix<T> TriDiagMatrix<T>::operator* (const T scalar) const
{
  TriDiagMatrix<T> holder(*this);
  for(int i = 0; i < 3; i++)
  {
    holder(i) = holder(i) * scalar;
  }

  return holder;
}

// Read-only function operator
template <class T>
const T& TriDiagMatrix<T>::operator() (const int row, const int column) const
{
  if(row < 0 || row >= m_size)
    throw(RangeErr(row));
  if(column < 0 || column >= m_size)
    throw(RangeErr(column));

  if(row == column)
    return m_data[1][row];
  else if(row == column + 1)
    return m_data[2][column];
  else if(column == row + 1)
    return m_data[0][row];
  else
    return m_zero;
}

// Write function operator
template <class T>
T& TriDiagMatrix<T>::operator() (const int row, const int column)
{
  if(row < 0 || row >= m_size)
    throw(RangeErr(row));
  if(column < 0 || column >= m_size)
    throw(RangeErr(column));

  if(row == column)
    return m_data[1][row];
  else if(row == column + 1)
    return m_data[2][column];
  else if(column == row + 1)
    return m_data[0][row];
  else
    return m_zero;
}

// Vector return using function operator
template <class T>
Vector<T>& TriDiagMatrix<T>::operator() (const int index)
{
  if(index < 0 || index > 2)
    throw(RangeErr(index));

  return m_data[index];
}

// Const vector return using function operator
template <class T>
const Vector<T>& TriDiagMatrix<T>::operator() (const int index) const
{
  if(index < 0 || index > 2)
    throw(RangeErr(index));

  return m_data[index];
}

// Return size of matrix assuming a square matrix
template <class T>
int TriDiagMatrix<T>::getSize() const
{
  return m_size;
}

// Matrix * vector dot product
template <class T>
Vector<T> TriDiagMatrix<T>::operator* (const Vector<T>& rhs) const
{
  if(rhs.getSize() != m_size)
    throw(SizeEqualErr(rhs.getSize(), m_size));

  Vector<T> answer(m_size);

  for(int i = 0; i < m_size; i++)
  {
    for(int j = (i==0?0:i-1); j < (i==m_size-1?i+1:i+2); j++)
    {
      answer[i] += rhs[j] * (*this)(j, i);
    }
  }

  return answer;
}
