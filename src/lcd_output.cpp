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

  this->selectThis();

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
  for(int i = 0; i < this->width; i++){
    this->line_buffers[index]->at(i) = ' ';
  }
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
  for(int i = 0; i < this->height; i++){
    this->clearBuffer(i);
  }
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
    this->initializeLCD();
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
 * @param line (int) line to output
 * @param text (std::string) string of text to output
 *
 * @returns (bool) True on success, False on any failure
 */

bool LCDOutput::outputToLCD(int line, std::string text){
  int line_addr = 0;

  if(getenv(LCD_DEBUG)){
    std::cout << "LCD Output Number: " << this->output_number << " " << text << "\n";
  }

  if(LCDOutput::enable_output == true){
    if(line == 0){
      line_addr = LINE_1;
    }else if(line == 1){
      line_addr = LINE_2;
    }else if(line == 2){
      line_addr = LINE_3;
    }else if(line == 3){
      line_addr = LINE_4;
    }

    if(getenv(LCD_DEBUG)){
      std::cout << "LINE CMD" << line << "\n";
    }

    this->sendCmd(line_addr);

    for(unsigned int i = 0; i < text.length(); i++){
      this->sendChar((unsigned char)text[i]);
    }

  }else{
    return false;
  }

  return true;
}


/**\fn LCDOutput::toggleCmd
 *
 * Toggles the RS pin to command mode
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::toggleCmd(){
  digitalWrite(LCD_RS, 0);
  std::this_thread::sleep_for(std::chrono::microseconds(10));
}


/**\fn LCDOutput::toggleChar
 *
 * Toggles the RS pin to character mode
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::toggleChar(){
  digitalWrite(LCD_RS, 1);
  std::this_thread::sleep_for(std::chrono::microseconds(10));
}


/**\fn LCDOutput::sendCmd
 *
 * Sets the command
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::sendCmd(unsigned char cmd, bool init){
  bitfield b;
  b.byte = cmd;

  if(getenv(LCD_DEBUG)){
    std::cout << "sendCmd " << std::hex << (int)cmd << " ";
    std::cout << b.pins.b7 << b.pins.b6 << b.pins.b5 << b.pins.b4 << b.pins.b3 << b.pins.b2 << b.pins.b1 << b.pins.b0 << "\n";
  }

  this->toggleCmd();

  this->sendBits(b, init);
}


/**\fn LCDOutput::sendChar
 *
 * Send a character to the LCD unit
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::sendChar(unsigned char character){
  bitfield b;
  b.byte = character;

  if(getenv(LCD_DEBUG)){
    std::cout << "sendChar: " << character << " " << std::hex << (int)character << " ";
    std::cout << b.pins.b7 << b.pins.b6 << b.pins.b5 << b.pins.b4 << b.pins.b3 << b.pins.b2 << b.pins.b1 << b.pins.b0 << "\n";
  }

  this->toggleChar();

  this->sendBits(b, false);
}


/**\fn LCDOutput::sendBits
 *
 * Set the output pins to their corresponding 4-bit chunk
 *
 * @param b (bitfield) bitfield union representing the field
 * @param init (bool) flag determining if we should send all 8 bits in 4-bit mode, or just 4 bits (in 8-bit mode for initialization)
 *
 * @returns None
 */

void LCDOutput::sendBits(bitfield b, bool init){
  digitalWrite(LCD_D4, 0);
  digitalWrite(LCD_D5, 0);
  digitalWrite(LCD_D6, 0);
  digitalWrite(LCD_D7, 0);

  if(b.pins.b4){
    digitalWrite(LCD_D4, 1);
  }

  if(b.pins.b5){
    digitalWrite(LCD_D5, 1);
  }

  if(b.pins.b6){
    digitalWrite(LCD_D6, 1);
  }

  if(b.pins.b7){
    digitalWrite(LCD_D7, 1);
  }

  this->sendNibble();

    if(!init){
    digitalWrite(LCD_D4, 0);
    digitalWrite(LCD_D5, 0);
    digitalWrite(LCD_D6, 0);
    digitalWrite(LCD_D7, 0);

    if(b.pins.b0){
      digitalWrite(LCD_D4, 1);
    }

    if(b.pins.b1){
      digitalWrite(LCD_D5, 1);
    }

    if(b.pins.b2){
      digitalWrite(LCD_D6, 1);
    }

    if(b.pins.b3){
      digitalWrite(LCD_D7, 1);
    }

    this->sendNibble();
  }
}

/**\fn LCDOutput::initializeLCD
 *
 * Send initialization commands to the LCD screen
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::initializeLCD(){
  std::cout << "initalizeLCD #" << this->output_number << "\n";

  if(getenv(LCD_DEBUG)){
    std::cout << "LCD DEBUG ENABLED\n";
  }

  if(getenv(LED_DEBUG)){
    std::cout << "LED DEBUG ENABLED\n";
  }

  std::this_thread::sleep_for(std::chrono::microseconds(100000));

  this->sendCmd((unsigned char)0b00111111, true); //fs
  std::this_thread::sleep_for(std::chrono::microseconds(4500));

  this->sendCmd((unsigned char)0b00111111, true); //fs
  std::this_thread::sleep_for(std::chrono::microseconds(120));

  this->sendCmd((unsigned char)0b00111111, true);  //fs
  std::this_thread::sleep_for(std::chrono::microseconds(120));

  this->sendCmd((unsigned char)0b00100000, true); //enter 4bit mode
  std::this_thread::sleep_for(std::chrono::microseconds(120));

  /*4bit mode starts here*/

  if(getenv(LCD_DEBUG)){
    std::cout << "4BIT MODE ENABLE (DOUBLE CLK STROBE PER MSG)\n";
  }

  this->sendCmd((unsigned char)0b00101000); //function set
  std::this_thread::sleep_for(std::chrono::microseconds(60));

  this->sendCmd((unsigned char)0b00001000); //display on/off
  std::this_thread::sleep_for(std::chrono::microseconds(60));

  this->sendCmd((unsigned char)0b00000001); //clear display
  std::this_thread::sleep_for(std::chrono::microseconds(3500));

  this->sendCmd((unsigned char)0b00000010); //return cursor home
  std::this_thread::sleep_for(std::chrono::microseconds(3500));

  this->sendCmd((unsigned char)0b00000111); //entry mode set
  std::this_thread::sleep_for(std::chrono::microseconds(60));

  this->sendCmd((unsigned char)0b00001100); //display on/off
  std::this_thread::sleep_for(std::chrono::microseconds(60));
}


/**\fn LCDOutput::sendNibble
 *
 * Sends the nibble currently output to the GPIO
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::sendNibble(){
  int i = 1;

  if(getenv(LED_DEBUG)){
    i = 2000000;
  }

  std::this_thread::sleep_for(std::chrono::microseconds(100));

  digitalWrite(LCD_ES, 1);
  std::this_thread::sleep_for(std::chrono::microseconds(i));

  digitalWrite(LCD_ES, 0);
  std::this_thread::sleep_for(std::chrono::microseconds(100));

  if(getenv(LED_DEBUG)){
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}


/**\fn LCDOutput::selectThis
 *
 * Function to set the address select bits for the current LCD output
 *
 * @param None
 *
 * @returns None
 */

void LCDOutput::selectThis(){

  int bits[4];

  int index = this->output_number;

  for(int i = 0; i < 3; i++){
    bits[i] = index & (1 << i) ? 1 : 0;
  }

  digitalWrite(LCD_RS, 0);
  digitalWrite(LCD_ES, 0);
  digitalWrite(LCD_D4, 0);
  digitalWrite(LCD_D5, 0);
  digitalWrite(LCD_D6, 0);
  digitalWrite(LCD_D7, 0);

  digitalWrite(AS_1, bits[0]);
  digitalWrite(AS_2, bits[1]);
  digitalWrite(AS_4, bits[2]);
}


/**\fn LCDOutput::getOutputIndex
 *
 * Returns the output index of a given lcd output
 *
 * @param None
 *
 * @returns (int) integer representing the index of the lcd output object
 */

int LCDOutput::getOutputIndex(){
  return this->output_number;
}
