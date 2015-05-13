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
  void midiCallback(std::vector<unsigned char>*){throw 20;}
};

typedef void (MidiCallback::*output_callback)(std::vector<unsigned char>*); /** typedef defining a type for the midiCallback object method pointer*/
#endif
