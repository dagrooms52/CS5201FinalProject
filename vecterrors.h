////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: cs5201
// Date: 3/9/2015
// File Name: vecterrors.h
// Purpose: Define error objects for errors commonly encountered in the Vector
//          class member functions
//
////////////////////////////////////////////////////////////////////////////////


#ifndef VECTERRORS_H
#define VECTERRORS_H

class RangeErr
{
  public:
    
    // Pre: None
    // Post: A RangeErr object is constructed
    // Description: Constructs an error object to be thrown when an index 
    //              outside of its appropriate range is found
    RangeErr(int i): m_index(i) {};

    // Pre: None
    // Post: The out-of-range index is returned
    // Description: Returns the index that is out of range
    int badIndex() {return m_index;}
  
  private:
    int m_index;
};

class SizeEqualErr
{
  public:
    
    // Pre: None
    // Post: A SizeEqualErr object is constructed
    // Description: Constructs an error to be thrown when two objects supposed
    //              to have equal size do not
    SizeEqualErr(int i, int j): m_size1(i), m_size2(j) {};
    
    // Pre: None
    // Post: returns size of first object
    // Description: Returns the size of the first object
    int badSize1() {return m_size1;}
    
    // Pre: None
    // Post: returns size of second object
    // Description: Returns the size of the second object
    int badSize2() {return m_size2;}
  
  private:
    int m_size1;
    int m_size2;
};



#endif
