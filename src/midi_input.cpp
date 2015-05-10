/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *   Implements the MidiInput class
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include "RtMidi.h"
#include "input.hpp"
#include "midi_input.hpp"

/**\fn MidiInput::MidiInput
 *
 * MidiInput class constructor
 *
 * @param port (int) midi input port instance to open
 * @param (RtMidiIn*) instance of RtMidiIn to pass to the
 *
 * @returns None
 */

MidiInput::MidiInput(int port, RtMidiIn* midiin){
  this->midiin = midiin;

  this->external_midiin = true;

  this->midi_instance = port;

  if(midiin->getPortCount() <= 0){
    std::cout << "Insufficent MIDI Ports.  Exiting.\n";
    exit( EXIT_FAILURE );
  }

  this->midiin->openPort(this->midi_instance);

  this->midiin->setCallback(this->fireMessageEvent, this);
  this->midiin->ignoreTypes(false, false, false);
}
