/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *   Header file for the output base class
 *
 */



#include <iostream>
#include <string>
#include <cstdlib>

#ifndef OUTPUT_HPP
#define OUTPUT_HPP
class Output
{
private:
  int instance; /**Instance of current object*/
protected:
  static int instances; /**Number of input instances*/
public:
  Output();
  ~Output();
};
#endif
