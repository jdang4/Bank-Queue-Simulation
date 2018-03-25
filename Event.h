/*
 * Event.h
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang and pargyrakis
 */

#ifndef EVENT_H_
#define EVENT_H_

class EventQueue;
class Event {


public:

  // Constructor
  Event(EventQueue &eventQueue, float time);

  // Destructor
  ~Event();

  // Function Members

  float getTime();

  void addEvent();

  int getActionType();



  // Data Members
  int action;
  const float initTime;
  float netTime;
  EventQueue &eventQueue;



};



#endif
