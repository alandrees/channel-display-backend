/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *  Callback class definition to allow for base class pointer for the RtMidi
 *  callback function
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#ifndef CALLBACK_HPP
#define CALLBACK_HPP

class MidiCallback{
public:
  virtual void midiCallback(int ch, int type, int pos, int line, char character){throw 20;}
};

typedef void (MidiCallback::*output_callback)(int, int, int, int, char); /** typedef defining a type for the midiCallback object method pointer*/
#endif
