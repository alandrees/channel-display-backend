/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *   Midi Input class definition
 *
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include "RtMidi.h"
#include "input.hpp"

#ifndef MIDI_INPUT_HPP
#define MIDI_INPUT_HP

typedef void (*msg_callback)(std::vector<unsigned char>*); /**typedef for the message passing callback*/

struct CallbackMessage {
  msg_callback cb; /** callback function */
  int id; /** identifier */
};
#endif
