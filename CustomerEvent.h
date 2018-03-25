/*
 * CustEvent.h
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang and pargyrakis
 */

#ifndef CUSTOMEREVENT_H_
#define CUSTOMEREVENT_H_

#include "Event.h"
class CustomerEvent: public Event{

public:

	// Constructor
	CustomerEvent(EventQueue &eventQueue, float time);

	// Destructor
	~CustomerEvent();

	// Function Members

	float custLeaveBank();

	float getServiceTime();

	void timeWithTeller(float currentTime, float TellTime);

	// Data Members

	float serviceTime;
};



#endif
