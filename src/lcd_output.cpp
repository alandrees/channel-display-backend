/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *  Implementation of the lcd_output class
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include "lcd_output.hpp"
#include "wiringPi.h"

/**\fn LCDOutput::LCDOutput
 *
 * LCD Output class constructor
 *
 * @param width (int) width (character width) of the LCD screen
 * @param height (int) height (lines on the device) of the LCD screen
 * @param index (int) screen index in the controller
 *
 * @returns None
 */

LCDOutput::LCDOutput(int width, int height, int index){

  LineBuffer* str1;
  LineBuffer* str2;
  std::string emptystring = "";


  if(width > 0){
    this->width = width;
  }else{
    width = 20;
  }

  if(height > 0){
    this->height = height;
  }else{
    this->height = 4;
  }

  if(index >= 0){
    this->output_number = index;
  }else{
    this->output_number = 0;
  }

  for(int i = 0; i < this->height; i++){
    str1 = new LineBuffer;
    str2 = new LineBuffer;

    for(int j = 0; j < this->width; j++){
      str1->push_back(emptystring);
      str2->push_back(emptystring);
    }

    this->line_buffers.push_back(str1);
    this->current_output.push_back(str2);
  }
}


/**\fn LCDOutput::~LCDOutput
 *
 * LCD Output class destructor
 *
 * @param None
 *
 * @returns None
 */

LCDOutput::~LCDOutput(){
}


/**\fn LCDOutput::flushBuffer
 *
 * Flushes a line to the device
 *
 * @param index (int) index of the buffer to flush
 *
 * @returns None
 */

void LCDOutput::flushBuffer(int index){
  std::string outputstring = "";
  LineBuffer* buffervector;

  if(index >= 0){
    buffervector = this->line_buffers.at(index);
  }else{
    return;
  }
}


/**\fn LCDOutput::flushAll
 *
 * Flush all lines to the output LCD screen
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::flushAll(){
  /*
  for(int i = 0; i < this->height; i++){
    this->flushBuffer(i);
  }
  */
}


/**\fn LCDOutput::pushToBuffer
 *
 * Push a character onto the selected buffer
 *
 * @param buffer (int) buffer to push the character
 * @param position (int) position to put the character
 * @param character (std::string) character to push to the buffer
 *
 * @returns None
 */

void LCDOutput::pushToBuffer(int buffer, int position, std::string character){
  //this->line_buffers[buffer] = character;
}


/**\fn LCDOutput::bulkUpdate
 *
 * Update all the buffer lines
 *
 * @param full_buffer (std::vector<std::string*>) full buffer to overwrite current buffer with
 * @param flush_now (bool) flush the buffer to the output
 *
 * @returns None
 */

void LCDOutput::bulkUpdate(VectorBuffer full_buffer, bool flush_now){
  /*
  this->clearAll();

  //fixme: need to get iterators instead
  for(int i = 0; i < this->height; i++){
    for(int j = 0; i < this->width; j++){
      this->line_buffers[i][j] = full_buffer[i][j];
    }
  }

  if(flush_now == true){
    this->flushAll();
  }
  */
}


/**\fn LCDOutput::clearBuffer
 *
 * Clears a specific buffer
 *
 * @param index (integer) buffer index to clear
 *
 * @returns None
 */

void LCDOutput::clearBuffer(int index){
  /*
  for(int i = 0; i < this->width; i++){
    *(this->line_buffers->at(index)) = ' ';
  }
  */
}

/**\fn LCDOutput::clearAll
 *
 * Clears all the buffers for a given index
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::clearAll(){
  /*
  for(int i = 0; i < this->height; i++){
    this->clearBuffer(i);
  }
  */
}


/**\fn LCDOutput::getCurrentOutput
 *
 * Gets the currently displayed text
 *
 * @param None
 *
 * @returns (VectorBuffer) containing the buffer text
 */

VectorBuffer LCDOutput::getCurrentOutput(){
  VectorBuffer* a = new VectorBuffer;
  return *a;
}


/**\fn LCDOutput::outputToLCD
 *
 * Logic to send the data to the LCD screen
 *
 * @param line (int)
 * @param text (std::string)
 *
 * @returns (bool) True on success, False on any failure
 */

bool LCDOutput::outputToLCD(int line, std::string text){
  return true;
}
