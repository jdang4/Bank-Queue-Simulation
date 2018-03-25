/*
 * Event.cpp
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang and pargyrakis
 */

#include "Event.h"
#include "EventQueue.h"
#include "TypesOfAction.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


/**
 * This is the constructor of the Event class
 * @param &eventQueue A pointer to the main event queue
 * @param time The current time of the event
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */

Event::Event(EventQueue &eventQueue, float time): initTime(time), eventQueue(eventQueue) {
	action = 0;
	netTime = time;
}

/**
 * This is the destructor of the Event class
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
Event::~Event() {

}

/**
 * It returns the time of the event
 * @return It returns the time of the event
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
float Event::getTime() {

	return netTime;
}

/**
 * adds the event to the event queue
 * @return It returns nothing
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
void Event::addEvent() {

	eventQueue.insertQueue(*this);
}


/**
 * This gets the action type required for the event
 * @return It looks into the TypesOfAction header and returns the correct the integer value of
 * action
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
int Event::getActionType() {

	return action;
}

