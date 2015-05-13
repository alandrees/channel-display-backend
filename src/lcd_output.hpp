/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *  Header file for the lcd_output class
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "output.hpp"


#ifndef LCD_OUTPUT_HPP
#define LCD_OUTPUT_HPP

typedef std::vector<std::string> LineBuffer;
typedef std::vector<LineBuffer*> VectorBuffer;

class LCDOutput : Output{
  VectorBuffer line_buffers; /**current buffer filled by the updated input*/
  VectorBuffer current_output; /**current output buffer filled by flipping the line_buffer to the LCD output*/
  int output_number; /**determines the LCD index to output to*/
  int height; /**height of the device, in lines*/
  int width; /**width of the device, in characters*/
  bool outputToLCD(int, std::string);

public:
  LCDOutput(int, int, int);
  ~LCDOutput();
  void flushBuffer(int);
  void flushAll();
  void pushToBuffer(int, int, std::string);
  void bulkUpdate(VectorBuffer, bool);
  void clearBuffer(int);
  void clearAll();
  VectorBuffer getCurrentOutput();
};
#endif
