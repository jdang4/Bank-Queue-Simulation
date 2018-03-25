/*
 * CustomerEvent.cpp
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang and pargyrakis
 */

#include "CustomerEvent.h"

#include "TypesOfAction.h"
#include "Event.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/**
 * This is the constructor of the CustomerEvent class
 * @param &eventQueue A pointer to the main event queue which the customer event is stored in the declaration
 * @param time The arrival time of the customer event
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
CustomerEvent::CustomerEvent(EventQueue &eventQueue, float time): Event(eventQueue, time) {
	netTime = time;
	action = CustArrive;
	serviceTime = 0;
	addEvent(); // Add customer arrival to event queue

}

/**
 * This is the destructor of the CustEvent class
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
CustomerEvent::~CustomerEvent() {

}

/**
 * Returns the service time of the Customer Event
 * @return It returns the serviceTime data member of the class CustEvent
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
float CustomerEvent::getServiceTime() {

	return serviceTime;
}

/**
 * Sets action of the event to leave
 * @return It returns the difference between the event's net time and the time in the event
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
float CustomerEvent::custLeaveBank() {
	action = CustLeave;
	return netTime - initTime;

}

/**
 * This changes the event action to Customer Service and calculates the net time
 * @param currentTime The current time of the program
 * @param TellTime The time of the teller's service time
 * @return This returns nothing
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
void CustomerEvent::timeWithTeller(float currentTime, float tellerTime) {
	netTime = currentTime + tellerTime;
	serviceTime = tellerTime;
	action = CustService;
	addEvent(); // Adds customer to teller to event queue
}


