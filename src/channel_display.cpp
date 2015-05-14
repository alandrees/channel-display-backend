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
#include "midi_input.hpp"
#include "lcd_output.hpp"
#include "channel_display.hpp"
#include "callback.hpp"

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

  for(int i = 0; i < 8; i++){
    x = new LCDOutput(20, 4, i);
    this->output.push_back(x);
  }

  mc = this;

  this->input[0]->addMessageCallback(&MidiCallback::midiCallback, mc);
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


void ChannelDisplay::midiCallback(midi_message message){
  if(message.message.msgtype == ADD_CHARACTER){
    this->output[message.message.channel]->pushToBuffer(message.message.line,
							message.message.position,
							message.message.character);
    /*
    std::cout << "Add character " << midi_message.message.character;
    std::cout << " to output " << midi_message.message.channel;
    std::cout << " (" << " " << midi_message.message.line << ", " << midi_message.message.position << ")\n";
    */
  }else if(message.message.msgtype == CLEAR_BUFFER){
    this->output[message.message.channel]->clearAll();
    //std::cout << "Clear the output buffer for output " << midi_message.message.channel << "\n";
  }else if(message.message.msgtype == FLUSH_BUFFER){
    this->output[message.message.channel]->flushAll();
    //std::cout << "Flush the output buffer for output " << midi_message.message.channel << "\n";
  }else{
    std::cout << std::hex << (int)message.message.msgtype << " is not a command.\n";
  }
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
