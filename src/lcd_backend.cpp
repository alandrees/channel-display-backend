/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *  Implementation for the LCD backend class
 *
 * Dependencies:
 */

#include <cstdlib>
#include <iostream>
#include <queue>
#include "lcd_output.hpp"
#include "lcd_backend.hpp"

/**\fn LcdBackend::LcdBackend
 *
 * Lcd Backend object constructor
 *
 * @param None
 *
 * @returns None
 */

LcdBackend::LcdBackend(){
  this->busy = false;
}
