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

#define LINE_1 0x80
#define LINE_2 0xC0
#define LINE_3 0x94
#define LINE_4 0xD4

#define LCD_RS 11
#define LCD_ES 10
#define LCD_D4 6
#define LCD_D5 5
#define LCD_D6 4
#define LCD_D7 1

#define AS_1 7
#define AS_2 9
#define AS_4 8

#define EPULSE 50 //in microseconds
#define EDELAY 50 //in microseconds

#define LCD_CHAR 1
#define LCD_CMD 0

#define LCD_DEBUG "LCD_DEBUG"
#define LED_DEBUG "LED_DEBUG"

typedef std::vector<std::string> LineBuffer;
typedef std::vector<LineBuffer*> VectorBuffer;

union bitfield{
  struct{
    unsigned int b0 : 1;
    unsigned int b1 : 1;
    unsigned int b2 : 1;
    unsigned int b3 : 1;
    unsigned int b4 : 1;
    unsigned int b5 : 1;
    unsigned int b6 : 1;
    unsigned int b7 : 1;
  } pins;
  unsigned char byte;
};

class LCDOutput : Output{
  VectorBuffer line_buffers; /**current buffer filled by the updated input*/
  VectorBuffer current_output; /**current output buffer filled by flipping the line_buffer to the LCD output*/
  int output_number; /**determines the LCD index to output to*/
  int height; /**height of the device, in lines*/
  int width; /**width of the device, in characters*/
  bool enable_output; /**set to false if there is a problem bringing up the GPIO interface*/

  bool outputToLCD(int, std::string);
  void toggleCmd();
  void toggleChar();
  void sendCmd(unsigned char, bool init = false);
  void sendChar(unsigned char);
  void sendBits(bitfield, bool);
  void sendNibble();
  void initializeLCD();
  void selectThis();

public:
  LCDOutput(int, int, int);
  ~LCDOutput();
  void flushBuffer(int);
  void flushAll();
  void pushToBuffer(int, int, unsigned char);
  void bulkUpdate(VectorBuffer, bool);
  void clearBuffer(int);
  void clearAll();
  VectorBuffer getCurrentOutput();
  void enableOutput();
  void disableOutput();
};
#endif
