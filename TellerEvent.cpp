/*
 * TellerEvent.cpp
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang
 */

#include "TellerEvent.h"
#include "TypesOfAction.h"
#include "Event.h"
#include "EventQueue.h"
#include "TellerQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "CustomerEvent.h"


/**
 * The constructor of the TellerEvent class
 * @param EventQueue &eventQueue The pointer to the main event queue which the CustEvent is stored in declaration
 * @param time The idle time of the teller
 * @param &Tqueue THe pointer to the teller queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
TellerEvent::TellerEvent(EventQueue &eventQueue, float time, TellerQueue &Tqueue) : Event(eventQueue, time), tQueue(Tqueue) {

	tellerQueue = new EventQueue();
	action = TellerIdle;
	netTime = time;

}

/**
 * This is the destructor
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
TellerEvent::~TellerEvent() {

	delete(this);
}

/**
 * This is in charge of adding the teller event to list of all tellers
 * @return This returns nothing
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
void TellerEvent::insertTellerToQueue() {

	tQueue.insertQueue(*this);
}

/**
 * This is in charge of adding an event to idle
 * @param currentTime The current time of the simulation that is used to calculate the time of the event
 * @return This returns the time of the Idle event
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
float TellerEvent::idle(float currentTime) {

	action = TellerIdle;
	netTime = currentTime + initTime;
	addEvent();

	return initTime;
}

/**
 * This is in charge of getting the length of the teller queue
 * @return It returns the length of the teller queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
int TellerEvent::queueLength() {

	return tellerQueue->getQueueLength();
}

/**
 * This is in charge of getting the next customer event from the teller queue with a specific time
 * @param currentTime The current time of the simulation
 * @param averageServiceTime The service time of the program
 * @return This returns the time for the next custmoer event in the teller queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
float TellerEvent::getNextCustomer(float currentTime, float averageServiceTime) {

	action = TellerGetCust;
	CustomerEvent *cust;

	if (queueLength() != 0) {
		// this gets the next event from the teller queue
		cust = static_cast<CustomerEvent*>(tellerQueue->getHeadEvent());
	}

	else {

		int i;

		TellerQueue *TellCust = new TellerQueue(eventQueue);

		// looks at all the tellers with lines greater than 0
		for (i = 0; i <= tQueue.getQueueLength(); i++) {
			if (( tQueue.getEvent(i)) -> queueLength() != 0 ) {
				// adds the teller to queue of tellers with non-zero queues
				TellCust->insertQueue(*tQueue.getEvent(i));
			}
		}

		if (TellCust->getQueueLength() == 0) {

			return idle(currentTime);
		}

		else {

			// gets a customer from a random teller queue which is not 0
			int randNum = rand() % (TellCust->getQueueLength())+1;
			cust = static_cast<CustomerEvent*>(TellCust->getEvent(randNum)->tellerQueue->getHeadEvent());
		}

		delete TellCust;
	}

	// If the action is a get customer action
	if (action == TellerGetCust) {
		// Service the customer and return to event queue
		float serviceTime = 2*averageServiceTime*rand()/float(RAND_MAX);
		cust->timeWithTeller(currentTime,serviceTime);
		netTime = currentTime + serviceTime;
		addEvent();
		return serviceTime; // return the time taken to service
	}

	return 0; // this acts as a default return value
}


/**
 * This is in charge of adding a customer event to the teller queue
 * @param *cust This is the customer event to be added into the queue
 * @return This returns nothing
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
void TellerEvent::addCustToQueue(CustomerEvent *cust){
	// If action type is a customer arrival then insert the customer event into the queue
	if (cust->getActionType() == CustArrive) {

		tellerQueue->insertQueue(*cust);
	}
}
