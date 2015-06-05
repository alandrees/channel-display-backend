/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *  Header file for the LCD Backend class prototype
 *
 * Dependencies:
 */

#include <cstdlib>
#include <iostream>
#include <queue>
#include "lcd_output.hpp"

#ifndef LCD_BACKEND_HPP
#define LCD_BACKEND_HPP
class LcdBackend{
  bool busy; /**flag to determine if the LCD Output bus is busy or not*/
  std::queue<LCDOutput*> lcd_queue;
  void fireObject(LCDOutput*);

public:
  LcdBackend();
  ~LcdBackend();

  void pushToQueue(LCDOutput*);
};
#endif
