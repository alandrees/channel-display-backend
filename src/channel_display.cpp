/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *  Application entry point and implementation of the ChannelDisplay class
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "midi_input.hpp"
#include "lcd_output.hpp"
#include "channel_display.hpp"
#include "callback.hpp"
#include "wiringPi.h"
#include "mcp23017.h"

/**\fn ChannelDisplay::ChannelDisplay
 *
 * ChannelDisplay class constructor
 *
 * @param None
 *
 * @returns None
 */

ChannelDisplay::ChannelDisplay(){
  this->iotype = I2C;
  this->commonConstructor();
}


/**\fn ChannelDisplay::ChannelDisplay
 *
 * Class constructor for passing the IO type to the class
 *
 * @param io_type (integer) io type to use
 *
 * @returns None
 */

ChannelDisplay::ChannelDisplay(int io_type){
  this->iotype = io_type;

  this->commonConstructor();
}


/**\fn ChannelDisplay::commonConstructor
 *
 * Common constructor functionality to be executed between all the overloaded constructors
 *
 * @param None
 *
 * @returns None
 */

void ChannelDisplay::commonConstructor(){
  MidiInput* in = 0;
  MidiCallback* mc = 0;

  in = new MidiInput(1);

  this->input.push_back(in);

  LCDOutput *x = 0;

  int lcd_count = LCD_COUNT;

  int i = 0;

  if(lcd_count > 16){
    lcd_count = 16;
  }

  if(this->iotype == I2C){
    this->initI2C();
  }

  for(i = 0; i < LCD_COUNT; i++){
    x = new LCDOutput(LCD_WIDTH, LCD_HEIGHT, i);

    if(this->iotype == I2C){
      std::cout << "pin base [" << i << "]: " <<MCP_PIN_BASE + (i * 8);
      x->setOutputPins(MCP_PIN_BASE + (i * 8));
    }

    this->output.push_back(x);
  }

  mc = this;

  this->input[0]->addMessageCallback(&MidiCallback::midiCallback, mc);

  if(this->initGPIO()){
    this->enableOutputs();
  }else{
    this->disableOutputs();
  }
}


/**\fn ChannelDisplay::~ChannelDisplay
 *
 * ChannelDisplay class destructor
 *
 * @param None
 *
 * @returns None
 */

ChannelDisplay::~ChannelDisplay(){
  for(unsigned int i = 0; i < this->output.size(); i++){
    this->output[i]->clearAll();
  }

  digitalWrite(LCD_RS, 0);
  digitalWrite(LCD_ES, 0);
  digitalWrite(LCD_D4, 0);
  digitalWrite(LCD_D5, 0);
  digitalWrite(LCD_D6, 0);
  digitalWrite(LCD_D7, 0);
}


/**\fn ChannelDisplay::midiCallback
 *
 * Callback to be executed on midi receipt
 *
 * @param ch (int) channel (device)
 * @param type (int) message type
 * @param pos (int) position
 * @param line (int) line
 * @param character (char) character
 *
 * @returns None
 */

void ChannelDisplay::midiCallback(int ch, int type, int pos, int line, char character){
  if(type == ADD_CHARACTER){
    this->output[ch]->pushToBuffer(line,
				   pos,
				   character);
  }else if(type == CLEAR_BUFFER){
    this->output[ch]->clearAll();
  }else if(type == FLUSH_BUFFER){
    this->lcd_queue.pushToQueue(this->output[ch]);
  }else{
    std::cout << std::hex << (int)type << " is not a command.\n";
  }
}



/**\fn ChannelDisplay::initGPIO
 *
 * Initializes the Raspberry Pi's GPIO
 *
 * @param None
 *
 * @returns (bool) true if GPIO setup was ok, false otherwise
 */

bool ChannelDisplay::initGPIO(){
  std::cout << "Bringing Up GPIO Interface..." << std::flush;

  wiringPiSetup();

  /*LCD Output pins*/
  pinMode(11, OUTPUT);

  pinMode(10, OUTPUT);

  pinMode(6, OUTPUT);

  pinMode(5, OUTPUT);

  pinMode(4, OUTPUT);

  pinMode(1, OUTPUT);

  /*Address Select pins*/
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(7, OUTPUT);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  pullUpDnControl(11, PUD_DOWN);

  pullUpDnControl(10, PUD_DOWN);

  pullUpDnControl(6, PUD_DOWN);

  pullUpDnControl(5, PUD_DOWN);

  pullUpDnControl(4, PUD_DOWN);

  pullUpDnControl(1, PUD_DOWN);

  pullUpDnControl(8, PUD_DOWN);

  pullUpDnControl(9, PUD_DOWN);

  pullUpDnControl(7, PUD_DOWN);

  std::cout << "done!\n";

  return true;
}


/**\fn ChannelDisplay::enableOutputs
 *
 * Enables the outputs
 *
 * @param None
 *
 * @returns None
 */

void ChannelDisplay::enableOutputs(){
  unsigned int i;

  for(i = 0; i < this->output.size(); i++){
    this->output[i]->enableOutput();
  }

  std::cout << this->output.size() << " outputs enabled\n";
}


/**\fn ChannelDisplay::disableOutputs
 *
 * Disables the outputs
 *
 * @param None
 *
 * @returns None
 */

void ChannelDisplay::disableOutputs(){
  unsigned int i;

  for(i = 0; i < this->output.size(); i++){
    this->output[i]->disableOutput();
  }

  std::cout << this->output.size() << " outputs disabled\n";
}
