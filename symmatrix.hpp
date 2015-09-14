////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: CS5201
// Date: 4/20/2015
// File Name: symmatrix.hpp
// Purpose: To implement the Symmetric Matrix class SymMatrix
//
////////////////////////////////////////////////////////////////////////////////

#include "symmatrix.h"

using namespace std;

// Size constructor
template <class T>
SymMatrix<T>::SymMatrix(const int size)
{
  if(size > 0)
  {
    m_size = size;
    m_data = new Vector<T> [size];
    for(int i = 0; i < size; i++)
    {
      Vector<T> init(i + 1);
      m_data[i] = init;
    }
  }
}

// Destructor
template <class T>
SymMatrix<T>::~SymMatrix<T>()
{
  if(m_data != NULL)
    delete[] m_data;
}

// Assignment operator
template <class T>
SymMatrix<T>& SymMatrix<T>::operator= (const SymMatrix<T>& rhs)
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
SymMatrix<T>::SymMatrix(const SymMatrix<T> & cpy)
{
  if(cpy.getSize() > 0)
    *this = cpy;
  else
  {
    m_size = 0;
    m_data = NULL;
  }
}

// Input operator
template <class T>
istream& operator>> (istream& in, SymMatrix<T>& mx)
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

// SymMatrix addition
template <class T>
SymMatrix<T> SymMatrix<T>::operator+ (const SymMatrix<T>& mx) const
{
  if(m_size != mx.getSize())
    throw(SizeEqualErr(m_size, mx.getSize()));
  
  SymMatrix<T> holder(m_size);
  for(int i = 0; i < m_size; i++)
  {
    // this is efficient - each aligning vector is of the same size
    holder(i) = m_data[i] + mx.m_data[i];
  }
  
  return holder;
}

// SymMatrix subtraction
template <class T>
SymMatrix<T> SymMatrix<T>::operator- (const SymMatrix<T>& mx) const
{
  if(m_size != mx.getSize())
    throw(SizeEqualErr(m_size, mx.getSize()));
  
  SymMatrix<T> holder(m_size);
  for(int i = 0; i < m_size; i++)
  {
    // this is efficient - each aligning vector is of the same size
    holder(i) = m_data[i] - mx.m_data[i];
  }
  
  return holder;
}

// SymMatrix multiplication
template <class T>
SymMatrix<T> SymMatrix<T>::operator* (const SymMatrix<T>& rhs) const
{
  if(m_size != rhs.getSize())
  {
    throw(SizeEqualErr(m_size, rhs.getSize()));
  }
  
  Matrix<T> holder(m_size);
  for(int i = 0; i < m_size; i++)
  {
    for(int j = 0; j < m_size; j++)
    {
      holder(i, j) = 0;
      for(int k = 0; k < m_size; k++)
      {
        holder(i, j) += (*this)(k, j) * rhs(i, k);
      }
    }
  }
  
  return holder;
}

// Scalar multiplication
template <class T>
SymMatrix<T> SymMatrix<T>::operator* (const T scalar) const
{
  SymMatrix<T> answer(*this);
  for(int i = 0; i < m_size; i++)
  {
    answer(i) = answer(i) * scalar;
  }

  return answer;
}

// Read-only function operator
template <class T>
const T& SymMatrix<T>::operator() (const int row, const int column) const
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
    return m_data[column][row];
  }
  else
  {
    return m_data[row][column];
  }

}
// Write function operator
template <class T>
T& SymMatrix<T>::operator() (const int row, const int column)
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
    return m_data[column][row];
  }
  else
  {
    return m_data[row][column];
  }

}

// Vector return function operator
template <class T>
Vector<T>& SymMatrix<T>::operator() (const int index)
{
  if(index < 0 || index >= m_size)
    throw(RangeErr(index));

  return m_data[index];
}

// Return size of matrix assuming square
template <class T>
int SymMatrix<T>::getSize() const
{
  return m_size;
}

// Matrix * vector dot product
template <class T>
Vector<T> SymMatrix<T>::operator* (const Vector<T>& rhs) const
{
  if(m_size != rhs.getSize())
    throw(SizeEqualErr(m_size, rhs.getSize()));

  Vector<T> answer(m_size);

  for(int i = 0; i < m_size; i++)
  {
    answer[i] = 0;
    for(int j = 0; j < m_size; j++)
    {
      answer[i] += rhs[j] * (*this)(i, j);
    }
  }

  return answer;
}
