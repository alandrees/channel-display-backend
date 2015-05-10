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


/**\fn MidiInput::fireMidiEvent
 *
 * Fires the callback list registered with the input source to collect the midi messages for a given output
 *
 * @param deltatime (double)
 * @param message (std::vector<unsigned char>)
 * @param userData (void*)
 *
 * @returns None
 */

void MidiInput::fireMessageEvent(double deltatime, std::vector<unsigned char> *message, void *userData){
  MidiInput* input_object = (MidiInput*)userData;

  std::list<CallbackMessage>::iterator i = input_object->message_callbacks.begin();

  msg_callback cb = 0;

  for(i; i != input_object->message_callbacks.end(); ++i){
    cb = *i->cb;
    cb(message);
  }

}


/**\fn MidiInput::addMessageCallback
 *
 * Adds a MIDI message callback function to the list of functions to handle midi input messages
 *
 * @param (void*) Function pointer for the callback message
 *
 * @returns (int) Integer ID refering of the callback function
 */

int MidiInput::addMessageCallback(msg_callback callback){
  CallbackMessage cb;

  cb.cb = callback;
  cb.id = this->callback_ids++;

  this->message_callbacks.push_back(cb);

  return cb.id;
}
