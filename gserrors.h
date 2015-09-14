////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: cs5201
// Date: 3/9/2015
// File Name: gserrors.h
// Purpose: Define error object for errors commonly encountered in Gaussian 
//          Elimination function
//
////////////////////////////////////////////////////////////////////////////////


#ifndef GSERRORS_H
#define GSERRORS_H

class DivZeroErr
{
  public:
    
    // Pre: None
    // Post: A DivZeroErr object is constructed
    // Description: Constructs an error object to be thrown when division by
    //              zero is detected
    DivZeroErr(int input): m_int(input) {};
  private:
    int m_int;
};

class ZeroVectorErr
{
  public:
    
    // Pre: None
    // Post: A ZeroVectorErr object is constructed
    // Description: Constructs an error object to be thrown when a vector
    //              whose elements all equal zero is encountered and 
    //              could negatively affect the program using it.
    ZeroVectorErr(int input): m_int(input) {};
  private:
    int m_int;
};

class VectSizeErr
{
  public:

    // Pre: None
    // Post: A VectSizeErr object is constructed
    // Description: Construct an error object to be thrown when a vector
    //              is encountered whose size is not applicable to the use
    //              of the vector
    VectSizeErr(int i): m_size(i) {};
    
    // Pre: None
    // Post: Size of error vector is returned
    // Description: Returns the size of the vector that caused the error
    //              to be thrown
    int getSize() {return m_size;}
  private:
    int m_size;
};

#endif
