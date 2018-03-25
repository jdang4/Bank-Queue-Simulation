/*
 * TellerEvent.h
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang and pargyrakis
 */

#ifndef TELLEREVENT_H_
#define TELLEREVENT_H_

#include "Event.h"
#include "TellerQueue.h"

class CustomerEvent;
class EventQueue;
class TellerQueue;

class TellerEvent: public Event {

public:

	// Constructor
	TellerEvent(EventQueue &eventQueue, float time, TellerQueue &Tqueue);

	// Destructor
	~TellerEvent();

	// Member Functions
	float idle(float currentTime);
	int queueLength();
	void insertTellerToQueue();
	float getNextCustomer(float CurrentTime, float averageServiceTime);
	void addCustToQueue(CustomerEvent *cust);

	// Data Members
	TellerQueue &tQueue;

	EventQueue *tellerQueue;
};



#endif
