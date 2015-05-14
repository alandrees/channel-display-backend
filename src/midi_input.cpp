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
#include "callback.hpp"

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


/**\fn MidiInput::fireMessageEvent
 *
 * Fires the callback list registered with the input source to collect the midi messages for a given output
 *
 * @param deltatime (double) ???
 * @param message (rtmidi_message) midi message bytes sent
 * @param userData (void*) a pointer to a structure of user data to be passed to the function
 *
 * @returns None
 */

void MidiInput::fireMessageEvent(double deltatime, rtmidi_message message, void *userData){
  MidiInput* input_object = (MidiInput*)userData;

  midi_message msg;

  msg.msg[0] = (*message)[0];
  msg.msg[1] = (*message)[1];
  msg.msg[2] = (*message)[2];

  std::list<CallbackMessage>::iterator i;

  CallbackMessage cb;

  for(i = input_object->message_callbacks.begin(); i != input_object->message_callbacks.end(); ++i){
  }

}


/**\fn MidiInput::addMessageCallback
 *
 * Adds a MIDI message callback function to the list of functions to handle midi input messages
 *
 * @param callback (void*) Function pointer for the callback message
 * @param output (Output*) Pointer to execute the callback with
 *
 * @returns (int) Integer ID refering of the callback function
 */

int MidiInput::addMessageCallback(output_callback callback, MidiCallback* output){
  CallbackMessage cb;

  cb.cb = callback;
  cb.id = this->callback_ids++;
  cb.o = output;

  this->message_callbacks.push_back(cb);

  return cb.id;
}


/**\fn MidiInput::removeMessageCallback
 *
 * Removes a MIDI message callback function from the list of functions
 *
 * @param id (int) message callback function id to remove
 *
 * @returns None
 */

void MidiInput::removeMessageCallback(int id){
  /*  std::list<CallbackMessage>::iterator i = this->message_callbacks.begin();

  for(i; i != this->message_callbacks.end(); ++i){
    if(*i.id == id){
      this->message_callbacks.erase(i);
    }
    }*/
}
