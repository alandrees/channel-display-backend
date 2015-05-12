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

  this->line_buffers = new VectorBuffer;
  this->current_output = new VectorBuffer;

  for(int i = 0; i < this->height; i++){
    str1 = new LineBuffer;
    str2 = new LineBuffer;

    for(int j = 0; j < this->width; j++){
      str1->push_back(emptystring);
      str2->push_back(emptystring);
    }

    this->line_buffers->push_back(str1);
    this->current_output->push_back(str2);


  }
}
