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

/**\fn ChannelDisplay::ChannelDisplay
 *
 * ChannelDisplay class constructor
 *
 * @param None
 *
 * @returns None
 */

ChannelDisplay::ChannelDisplay(){
  MidiInput* in = 0;
  MidiCallback* mc = 0;

  in = new MidiInput(1);

  this->input.push_back(in);

  LCDOutput *x = 0;

  for(int i = 0; i < LCD_COUNT; i++){
    x = new LCDOutput(LCD_WIDTH, LCD_HEIGHT, i);
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
    this->output[ch]->clearBuffer();

    this->output[ch]->pushToBuffer(0,0,"O");
    this->output[ch]->pushToBuffer(0,1,"F");
    this->output[ch]->pushToBuffer(0,2,"F");
    this->output[ch]->pushToBuffer(0,3,"L");
    this->output[ch]->pushToBuffer(0,4,"I");
    this->output[ch]->pushToBuffer(0,5,"N");
    this->output[ch]->pushToBuffer(0,6,"E");

    this->output[ch]->flushAll();
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
    this->output[ch]->flushAll();
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

  pinMode(11, OUTPUT);

  pinMode(10, OUTPUT);

  pinMode(6, OUTPUT);

  pinMode(5, OUTPUT);

  pinMode(4, OUTPUT);

  pinMode(1, OUTPUT);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  pullUpDnControl(11, PUD_DOWN);

  pullUpDnControl(10, PUD_DOWN);

  pullUpDnControl(6, PUD_DOWN);

  pullUpDnControl(5, PUD_DOWN);

  pullUpDnControl(4, PUD_DOWN);

  pullUpDnControl(1, PUD_DOWN);

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


/**\fn main
 *
 * Standard application entry point
 *
 * @param argc (int) argument count
 * @param argv (char**) array of char arrays representing the arguments
 *
 * @returns (int) return code for the application
 */

int main(int argc, char** argv){

  ChannelDisplay* app = new ChannelDisplay;
  char input;

  std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
  std::cin.get(input);

  delete app;

  return 0;
}
