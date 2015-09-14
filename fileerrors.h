////////////////////////////////////////////////////////////////////////////////
//
// Programmer: Daniel Grooms
// Course: cs5201
// Date: 3/9/2015
// File Name: fileerrors.h
// Purpose: Define a NoFileErr error object
//
////////////////////////////////////////////////////////////////////////////////

#ifndef FILEERRORS_H
#define FILEERRORS_H

class NoFileErr
{
  public:
    
    // Pre: none
    // Post: A NoFileErr object is created
    // Description: Creates an error object to be thrown if no file is included
    //              as a command line argument for the executable
    NoFileErr(int input): m_int(input) {};
  private:
    int m_int;
};

#endif
