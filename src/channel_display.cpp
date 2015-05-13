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

  in = new MidiInput();

  this->input.push_back(in);

  LCDOutput *x = 0;

  for(int i = 0; i < 8; i++){
    x = new LCDOutput(20, 4, i);
    this->output.push_back(x);
  }

  mc = this;

  this->input[0]->addMessageCallback(&MidiCallback::midiCallback, mc);
}
