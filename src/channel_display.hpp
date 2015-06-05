/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *  Header file for the main Channel Display application
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "midi_input.hpp"
#include "lcd_output.hpp"
#include "lcd_backend.hpp"
#include "callback.hpp"

#ifndef CHANNEL_DISPLAY_HPP
#define CHANNEL_DISPLAY_HPP

#define LCD_COUNT 8
#define LCD_WIDTH 20
#define LCD_HEIGHT 4

class ChannelDisplay : MidiCallback{
  enum command : int {
    ADD_CHARACTER=0xb,
      CLEAR_BUFFER=0xa,
      FLUSH_BUFFER=0xc
      };

  std::vector<MidiInput*>  input; /**Input object**/
  std::vector<LCDOutput*> output; /**Output object**/
  LcdBackend lcd_queue;
  bool initGPIO();

public:
  ChannelDisplay();
  ~ChannelDisplay();
  void midiCallback(int, int, int, int, char);
  void enableOutputs();
  void disableOutputs();
};
#endif
