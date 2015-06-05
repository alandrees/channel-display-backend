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


/**\fn LcdBackend::~LcdBackend
 *
 * Lcd Backend object destructor
 *
 * @param None
 *
 * @returns None
 */

LcdBackend::~LcdBackend(){
  if(!this->lcd_queue.empty()){
    std::cout << "Queue not Empty at destruction.\n";
  }
}


/**\fn LcdBackend::pushToQueue
 *
 * Pushes an LcdOutput object on to the queue for it to have it's output buffer flushed
 *
 * @param output (LcdOutput*) LcdOutput object pointer to push to the queue
 *
 * @returns None
 */

void LcdBackend::pushToQueue(LCDOutput* output){
  LCDOutput* pop;
  this->lcd_queue.push(output);

  if(!this->busy){
    pop = this->lcd_queue.front();
    this->lcd_queue.pop();
    this->fireObject(pop);
  }
}


/**\fn LcdBackend::fireObject
 *
 * Handles the interaction with the LcdOutput object
 *
 * @param object (LcdOutput*)
 *
 * @returns None
 */

void LcdBackend::fireObject(LCDOutput* object){
  LCDOutput* pop;
  this->busy = true;

  object->flushAll();

  if(this->lcd_queue.size() > 0){
    pop = this->lcd_queue.front();
    this->lcd_queue.pop();
    std::cout << pop->getOutputIndex() << "\n";
    this->fireObject(pop);
  }else{
    this->busy = false;
  }
}
