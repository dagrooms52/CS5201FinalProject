## Programmer: Daniel Grooms
## Course: CS5201
## Date: 3/8/2015
## File name: makefile
## Purpose: Build an executable for the project

#Compiler macro
CXX = /usr/bin/g++

#Executable macro
EXE = driver

#Only compiles when not using CXXFLAGS
#CXXFLAGS = -g -Wall -W -pedantic-errors

#Generate sources and headers
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

#Generate object
OBJECTS = $(SOURCES:%.cpp=%.o)

default: all

all: $(EXE)

#Makes all .o files from their respective .cpp files
%.o: %.cpp
	$(CXX) -c $< -o $@

#Makes driver from all objects
$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

#Dependancies
#driver.o: driver.cpp norm.h cylinderPoint.h cylinderPoint.hpp norm.hpp

#Clean command; -f flag forces remove, to avoid error outputs
clean:
	-@rm -f core > /dev/null 2>&1
	-@rm -f $(EXE) > /dev/null 2>&1
	-@rm -f ${OBJECTS} > /dev/null 2>&1
