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
#include <chrono>
#include <thread>
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

  this->enable_output = false;
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
    buffervector = this->line_buffers[index];
  }else{
    return;
  }

  for(int i = 0; i < this->width; i++){
    outputstring = outputstring + this->line_buffers[index]->at(i);
  }

  this->outputToLCD(index, outputstring);

  //this->copyToOutput
  //this->blankBuffer
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
  for(int i = 0; i < this->height; i++){
    this->flushBuffer(i);
  }

  this->sendCmd(0b00000010);

  digitalWrite(LCD_D4, 0);
  digitalWrite(LCD_D5, 0);
  digitalWrite(LCD_D6, 0);
  digitalWrite(LCD_D7, 0);

}


/**\fn LCDOutput::pushToBuffer
 *
 * Push a character onto the selected buffer
 *
 * @param buffer (int) buffer to push the character
 * @param position (int) position to put the character
 * @param character (unsigned char) character to push to the buffer
 *
 * @returns None
 */

void LCDOutput::pushToBuffer(int line, int position, unsigned char character){
  std::string newchar = "";

  newchar = character;

  this->line_buffers[line]->at(position) = newchar;
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


/**\fn LCDOutput::enableOutput()
 *
 * Enables the output
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::enableOutput(){
  if(this->enable_output != true){
    this->clearAll();
  }

  this->enable_output = true;
}


/**\fn LCDOutput::disableOutput()
 *
 * Disables the output
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::disableOutput(){
  if(this->enable_output != false){
    this->clearAll();
  }

  this->enable_output = false;
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
  if(LCDOutput::enable_output == true){

  }else{
    return false;
  }

  return true;
}
