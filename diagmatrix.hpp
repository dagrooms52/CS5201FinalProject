////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: CS5201
// Date: 4/20/2015
// File Name: diagmatrix.hpp
// Purpose: To implement the Diagonal Matrix class DiagMatrix
//
////////////////////////////////////////////////////////////////////////////////

#include "diagmatrix.h"

using namespace std;

// Size constructor
template <class T>
DiagMatrix<T>::DiagMatrix(const int size)
{
  if(size > 0)
  {
    m_size = size;
    m_data = new Vector<T>(size);
  }
  else
  {
    m_size = 0;
    m_data = NULL;
  }
}

// Assignment operator
template <class T>
DiagMatrix<T>& DiagMatrix<T>::operator= (const DiagMatrix<T>& rhs)
{
  if(m_data != NULL)
    delete m_data;

  if(rhs.getSize() > 0)
  {
    m_size = rhs.getSize();
    m_data = new Vector<T>(m_size);
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
DiagMatrix<T>::DiagMatrix(const DiagMatrix<T> & cpy)
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
istream& operator>> (istream& in, DiagMatrix<T>& mx)
{
  T buffer;
  int size = mx.getSize();

  if(size > 0)
  {
    for(int i = 0; i < size; i++)
    {
      for(int j = 0; j < size; j++)
      {
        if(j != i)
          in >> buffer;
        else
          in >> mx(i, i);
      }
    }
  }
  
  return in;
}

// DiagMatrix addition
template <class T>
DiagMatrix<T> DiagMatrix<T>::operator+ (const DiagMatrix<T>& mx) const
{
  if(m_size != mx.getSize())
    throw(SizeEqualErr(m_size, mx.getSize()));

  DiagMatrix<T> holder(m_size);
  // holder.*m_data is holder's only data vector, for which addition is defined
  holder.*m_data = holder.*m_data + mx.*m_data;

  return holder;
}

// DiagMatrix subtraction
template <class T>
DiagMatrix<T> DiagMatrix<T>::operator- (const DiagMatrix<T>& mx) const
{
  if(m_size != mx.getSize())
    throw(SizeEqualErr(m_size, mx.getSize()));

  DiagMatrix<T> holder(m_size);
  holder.*m_data = holder.*m_data + mx.*m_data;

  return holder;
}

// DiagMatrix multiplication
template <class T>
DiagMatrix<T> DiagMatrix<T>::operator* (const DiagMatrix<T>& rhs) const
{
  if(m_size != rhs.getSize())
    throw(SizeEqualErr(m_size, rhs.getSize()));

  DiagMatrix<T> answer(m_size);

  for(int i = 0; i < m_size; i++)
  {
    answer(i, i) = (*this)(i, i) * rhs(i, i);
  }

  return answer;
}

// Scalar multiplication
template <class T>
DiagMatrix<T> DiagMatrix<T>::operator* (const T scalar) const
{
  DiagMatrix<T> answer(m_size);

  answer.*m_data = answer.*m_data * scalar;

  return answer;
}

///////////////////////
// --- Inherited --- //
///////////////////////

// Read-only function operator
template <class T>
const T& DiagMatrix<T>::operator() (const int row, const int column) const
{
  if(row < 0 || row >= m_size)
    throw(RangeErr(row));
  if(column < 0 || column >= m_size)
    throw(RangeErr(column));

  if(column != row)
    return m_zero;
  else
    return (*m_data)[row];
}

// Write function operator
template <class T>
T& DiagMatrix<T>::operator() (const int row, const int column)
{
  if(row < 0 || row >= m_size)
    throw(RangeErr(row));
  if(column < 0 || column >= m_size)
    throw(RangeErr(column)); 

  if(column != row)
    return m_zero;
  else
    return (*m_data)[row];
}

// Vector return function operator
template <class T>
Vector<T>& DiagMatrix<T>::operator() (const int index)
{
  if(index < 0 || index >= m_size)
    throw(RangeErr(index));

  return (*m_data);
}

// Return size of matrix, assuming a square matrix
template <class T>
int DiagMatrix<T>::getSize() const
{
  return m_size;
}

// Matrix dot product with vector
template <class T>
Vector<T> DiagMatrix<T>::operator* (const Vector<T>& rhs) const
{
  if(rhs.getSize() != m_size)
    throw(SizeEqualErr(rhs.getSize(), m_size));

  Vector<T> answer(rhs);

  for(int i = 0; i < m_size; i++)
  {
    answer[i] = answer[i] * (*m_data)[i];
  }

  return answer;
}
