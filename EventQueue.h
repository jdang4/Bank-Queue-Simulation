/*
 * EventQueue.h
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang and pargyrakis
 */

#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

class Event;

class EventQueue {

	// Creating the linked list
	struct node {
		Event *event;      // the data type of the linked list
		struct node *next; // the next node
		struct node *prev; // the previous node
	};

public:

	// Constructor
	EventQueue();

	// Destructor
	~EventQueue();

	// Member Functions

	int numOfCustsInEventQueue();

	void insertQueue(Event &eventIn);

	int getQueueLength();

	Event* getHeadEvent();



private:

	// Member Functions
	void insertQueue(Event *eventIn, node *comparedNode);
	node* initEventInQueue(Event *eventIn);

	// Data Members
	node* rootNode; // The rootNode of the EventQueue
	int nodelength;

};



#endif
