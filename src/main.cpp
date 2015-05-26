/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *  Implements the application entry point
 *
 * Dependencies:
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "channel_display.hpp"

/**\fn main
 *
 * Standard application entry point
 *
 * @param argc (int) argument count
 * @param argv (char**) array of char arrays representing the arguments
 *
 * @returns (int) return code for the application
 */

int main(int argc, char** argv){

  ChannelDisplay* app = new ChannelDisplay;
  char input;

  std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
  std::cin.get(input);

  delete app;

  return 0;
}
