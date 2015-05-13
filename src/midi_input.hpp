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
#include "output.hpp"
#include "callback.hpp"

#ifndef MIDI_INPUT_HPP
#define MIDI_INPUT_HPP

typedef std::vector<unsigned char>*  rtmidi_message; /**typedef for rtmidi midi message*/

struct CallbackMessage {
  output_callback cb; /** callback function */
  MidiCallback* o; /** output object reference */
  int id; /** identifier */
};

union midi_message{
  struct messageParts{
    unsigned int channel : 4;
    unsigned int msgtype : 4;
    unsigned int position : 5;
    unsigned int line : 3;
    unsigned char character;
  } message;
  unsigned char msg[3];
};


class MidiInput: private Input{
private:
  RtMidiIn *midiin = 0; /** RtMidiIn object reference */
  int midi_instance = 0; /** midi I/O instance to use */
  bool external_midiin = false; /** boolean determining if we need to clean up midiin or not */
  int callback_ids = 0; /** integer counter to keep track of the callback ids */


  std::list<CallbackMessage> message_callbacks; /** std::list of CallbackMessage structures*/

  static void fireMessageEvent(double, std::vector<unsigned char>*, void *);

public:
  MidiInput(int, RtMidiIn*);
  MidiInput(int);
  MidiInput();
  ~MidiInput();

  int addMessageCallback(msg_callback);
  void removeMessageCallback(int);
};
#endif
