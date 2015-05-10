/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *  Header file for the Input base class
 *
 */


#include <iostream>
#include <string>
#include <cstdlib>

#ifndef INPUT_HPP
#define INPUT_HPP
class Input
{
private:
  int instance; /**Instance of current object*/
protected:
  static int instances; /**Number of input instances*/
public:
  Input();
  ~Input();
};
#endif
