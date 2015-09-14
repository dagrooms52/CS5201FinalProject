////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Date: 3/8/2015
// Course: CS5201
// File Name: vector.hpp
// Purpose: To implement a vector class
//
////////////////////////////////////////////////////////////////////////////////

#include "vector.h"

#include <cmath>
#include <iostream>
using namespace std;

// --- Constructors -- //


// Default constructor  
template <class T>
Vector<T>::Vector()
{
  m_size = 0;
  m_numElts = 0;
  m_ptrToData = NULL;
}

// Fill constructor
template <class T>
Vector<T>::Vector(const int size, const T fill)
{
  m_size = size;
  m_numElts = size;
  m_ptrToData = new T [m_size];
  for(int i = 0; i < m_size; i++)
  {
    m_ptrToData[i] = fill;
  }
}

// Constructor with size
template <class T>
Vector<T>::Vector(const int size)
{
  m_size = size;
  m_numElts = 0;
  m_ptrToData = new T [m_size];
  for(int i = 0; i < size; i++)
    m_ptrToData[i] = 0;
}

// Destructor
template <class T>
Vector<T>::~Vector()
{
  if(m_ptrToData != NULL)
  {
    delete[] m_ptrToData;
  }
}

// Vector equal operator
template <class T>
Vector<T>& Vector<T>::operator= (const Vector<T>& rhs)
{
  if(m_ptrToData != NULL)
  {
    delete[] m_ptrToData;
  }

  if(rhs.m_size > 0 && rhs.m_ptrToData != NULL)
  {
    m_numElts = rhs.m_numElts;
    m_size = rhs.m_size;
    m_ptrToData = new T [m_size];

    for(int i = 0; i < m_size; i++)
    {
      m_ptrToData[i] = rhs.m_ptrToData[i];
    }
  }

  return (*this);
}

// Fill equal operator
template <class T>
Vector<T>& Vector<T>::operator= (const T& fill)
{

  if(m_size > 0 && m_ptrToData != NULL)
  { 
    m_numElts = m_size;
    for(int i = 0; i < m_size; i++)
    {
      m_ptrToData[i] = fill;
    }
  }

  return (*this);
}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector<T>& cpy)
{
  if(cpy.m_size > 0 && cpy.m_ptrToData != NULL)
  {
    m_numElts = cpy.m_numElts;
    m_size = cpy.m_size;
    m_ptrToData = new T[m_size];
    for(int i = 0; i < m_size; i++)
    {
      m_ptrToData[i] = cpy.m_ptrToData[i];
    }
  }
  else
  {
    m_size = 0;
    m_ptrToData = NULL;
  }
}

// Get size of vector
template <class T>
int Vector<T>::getSize() const
{
  return m_size;
}

// Read-only subscript operator
template <class T>
const T& Vector<T>::operator[] (const int index) const
{
  if(index < 0 || index >= m_size)
    throw(RangeErr(index));

  return m_ptrToData[index];
}

// Output operator
template <class T>
ostream& operator<< (ostream& out, const Vector<T>& vect)
{
  if(vect.m_size > 0)
  {
    out << "(";
    for(int i = 0; i < vect.m_size; i++)
    {
      out << vect.m_ptrToData[i];
      if(i != vect.m_size - 1)
        out << ", ";
    }
    out << ")";
  }

  return out;
}

// Check if vector is a multiple of passed vector
template <class T>
bool Vector<T>::isMultiple(const Vector<T>& other) const
{
  // Formula: A is multiple of B if:
  // (u . v) * u == (u . u) * v

  Vector<T> hold1(m_size);
  Vector<T> hold2(m_size);
  double dot1, dot2;

  if(m_size == other.m_size)
  {
    dot1 = (*this) * other;
    hold1 = (*this) * dot1;

    dot2 = (*this) * (*this);
    hold2 = (other) * dot2;
  }
  else
  {
    throw(SizeEqualErr(m_size, other.m_size));
  }

  return (hold1 == hold2);
}

// Vector equality operator
template <class T>
bool Vector<T>::operator==(const Vector<T>& rhs) const
{
  bool check = true;

  if(m_size == rhs.m_size)
  {
    for(int i = 0; i < m_size; i++)
    {
      if (m_ptrToData[i] != rhs.m_ptrToData[i])
        check = false;
    }
  }
  else
    throw(SizeEqualErr(m_size, rhs.m_size));

  return check;
}

// Vector not-equal operator
template <class T>
bool Vector<T>::operator!= (const Vector<T>& rhs) const
{
  return (!(*this == rhs));
}

// Get maximum of absolute of values in vector
template <class T>
T Vector<T>::max() const
{
  if(m_size < 0 || m_ptrToData == NULL)
  {
    throw(RangeErr(0));
  }

  T max = abs(m_ptrToData[0]);
  for(int i = 0; i < m_size; i++)
  {
    if(abs(m_ptrToData[i]) > max)
    {
      max = abs(m_ptrToData[i]);
    }
  }

  return max;
}

//////////////////////
// --- Mutators --- //
//////////////////////

// Read-write subscript operator
template <class T>
T& Vector<T>::operator[] (const int index)
{
  if(index < 0 || index >= m_size)
    throw(RangeErr(index));

  return m_ptrToData[index];
}

// Input operator
template <class T>
istream& operator>> (istream& in, Vector<T>& vect)
{
  // Stacks input front to back
  if(vect.m_numElts < vect.m_size && vect.m_numElts >= 0)
  {
    for(int i = 0; i < vect.m_size; i++)
    {  
      in >> vect.m_ptrToData[vect.m_numElts];
      vect.m_numElts++;
    }
  }

  return in;
}

template <class T>
T Vector<T>::operator* (const Vector<T>& rhs) const
{
  T sum = 0.0;

  if(m_size != rhs.m_size)
  {
    throw(SizeEqualErr(m_size, rhs.m_size));
  }

  for(int i = 0; i < m_size; i++)
  {
    sum += (m_ptrToData[i] * rhs.m_ptrToData[i]);
  }

  return sum;
}


template <class T>
Vector<T> Vector<T>::operator* (const double scalar) const
{
  Vector<T> copy(*this);

  for(int i = 0; i < m_size; i++)
  {
    copy[i] *= scalar;
  }

  return copy;
}

template <class T>
Vector<T> operator- (const Vector<T>& vect)
{
  Vector<T> copy(vect);
  
  if(copy.m_size > 0 && copy.m_ptrToData != NULL)
    copy = (-1) * copy;

  return copy;
}

template <class T>
Vector<T> Vector<T>::operator- (const Vector<T>& rhs) const
{
  Vector<T> copy(*this);

  if(copy.m_ptrToData != NULL && rhs.m_size > 0 && \
     rhs.m_ptrToData != NULL && copy.m_size == rhs.m_size)
  {
    for(int i = 0; i < copy.m_size; i++)
    {
      copy.m_ptrToData[i] = copy.m_ptrToData[i] - rhs.m_ptrToData[i];
    }
  }
  else
    throw(SizeEqualErr(m_size, rhs.m_size));

  return copy;
}

template <class T>
Vector<T> Vector<T>::operator+ (const Vector<T>& rhs) const
{
  Vector<T> copy(*this);
 
  if(copy.m_ptrToData != NULL && rhs.m_size > 0 && \
     rhs.m_ptrToData != NULL && copy.m_size == rhs.m_size)
  {
    for(int i = 0; i < copy.m_size; i++)
    {
      copy.m_ptrToData[i] = copy.m_ptrToData[i] + rhs.m_ptrToData[i];
    }
  }
  else
    throw(SizeEqualErr(m_size, rhs.m_size));
  
  return copy;
}

template <class T>
void Vector<T>::swap(const int index1, const int index2)
{
  // Check that indices are within bounds
  if(index1 < 0 || index1 >= m_size)
    throw(RangeErr(index1));
  else if(index2 < 0 || index2 >= m_size)
    throw(RangeErr(index2));
  
  T holder = m_ptrToData[index1];
  m_ptrToData[index1] = m_ptrToData[index2];
  m_ptrToData[index2] = holder;
  
  return;
}
