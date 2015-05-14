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
    /*
    std::cout << "Add character " << character;
    std::cout << " to output " << ch;
    std::cout << " (" << " " << line << ", " << pos << ")\n";
    */
  }else if(type == CLEAR_BUFFER){
    this->output[ch]->clearAll();
    /*
    std::cout << "Clear the output buffer for output " << ch << "\n";
    */
  }else if(type == FLUSH_BUFFER){
    this->output[ch]->flushAll();
    /*
    std::cout << "Flush the output buffer for output " << ch << "\n";
    */
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
  wiringPiSetupSys();

  std::chrono::milliseconds timespan(1000);

  std::cout << "Bringing Up GPIO Interface...";

  //export the pins
  system("echo 7 > /sys/class/gpio/export");
  system("echo 8 > /sys/class/gpio/export");
  system("echo 25 > /sys/class/gpio/export");
  system("echo 24 > /sys/class/gpio/export");
  system("echo 23 > /sys/class/gpio/export");
  system("echo 18 > /sys/class/gpio/export");

  std::this_thread::sleep_for(timespan);

  //set the pin direction
  system("echo out > /sys/class/gpio/gpio7/direction");
  system("echo out > /sys/class/gpio/gpio8/direction");
  system("echo out > /sys/class/gpio/gpio25/direction");
  system("echo out > /sys/class/gpio/gpio24/direction");
  system("echo out > /sys/class/gpio/gpio23/direction");
  system("echo out > /sys/class/gpio/gpio18/direction");

  std::cout << "done!\n";

  return true;
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
