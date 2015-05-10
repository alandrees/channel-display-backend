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


/**\fn MidiInput::MidiInput
 *
 * Overloaded MidiInput class constructor which creates an internal-only RtMidiIn object
 *
 * @param port (int) midi input port instance to open
 *
 * @returns None
 */

MidiInput::MidiInput(int port){
  try{
    this->midiin = new RtMidiIn();
  }
  catch ( RtMidiError &error){
    error.printMessage();
    exit( EXIT_FAILURE );
  }

  this->external_midiin = false;

  this->midi_instance = port;

  if(midiin->getPortCount() <= 0){
    std::cout << "Insufficent MIDI Ports.  Exiting.\n";
    exit( EXIT_FAILURE );
  }

  this->midiin->openPort(this->midi_instance);

  this->midiin->setCallback(this->fireMessageEvent, this);
  this->midiin->ignoreTypes(false, false, false);
}

/**\fn MidiInput::MidiInput
 *
 * Overloaded MidiInput class constructor which creates an internal-only RtMidiIn object and defaults to device 0
 *
 * @param None
 *
 * @returns None
 */

MidiInput::MidiInput(){
  try{
    this->midiin = new RtMidiIn();
  }
  catch ( RtMidiError &error){
    error.printMessage();
    exit( EXIT_FAILURE );
  }

  this->external_midiin = false;

  this->midi_instance = 0;

  if(midiin->getPortCount() <= 0){
    std::cout << "Insufficent MIDI Ports.  Exiting.\n";
    exit( EXIT_FAILURE );
  }

  this->midiin->openPort(this->midi_instance);

  this->midiin->setCallback(this->fireMessageEvent, this);
  this->midiin->ignoreTypes(false, false, false);
}


/**\fn MidiInput::~MidiInput
 *
 * MidiInput class destructor
 *
 * @param None
 *
 * @returns None
 */

MidiInput::~MidiInput(){
  if((this->midiin != 0) && this->external_midiin == false){
    delete this->midiin;
  }
}
