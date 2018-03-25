/*
 * EventQueue.cpp
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang
 */

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "Event.h"
#include "EventQueue.h"
#include "TypesOfAction.h"


/**
 * The constructor of the EventQueue class
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
EventQueue::EventQueue() {

	Event * eventStart = new Event(*this, -10);

	rootNode = new node();

	rootNode->event = eventStart;
	rootNode->next = NULL;
	rootNode->prev = NULL;

	nodelength = 0;
}

/**
 * This is the destructor of the EventQueue class
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
EventQueue::~EventQueue() {

	int nodel = nodelength;

	for(int i=nodel; i >0; i--) {

		getHeadEvent();
	}
}

/**
 * This will return the length of the linked list
 * @return It returns the length of the queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
int EventQueue::getQueueLength() {

	return nodelength;
}

/**
 * This inserts an event into the event queue
 * @param &event The pointer to the event being inserted in the queue
 * @return It returns nothing
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
void EventQueue::insertQueue(Event &event) {

	insertQueue(&event, rootNode);
}


/**
 * This inserts an element into the event queue based on time
 * @param eventIn The event to be inserted into the queue
 * @param comparedNode The node which is to be compared to event time
 * @return It returns nothing
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
void EventQueue::insertQueue(Event *eventIn, node *comparedNode){

	node *insertNode = initEventInQueue(eventIn);

	if(comparedNode -> event -> getTime() <= insertNode -> event -> getTime() &&
			(comparedNode -> prev == NULL ||
			 comparedNode -> prev -> event -> getTime() > insertNode -> event -> getTime()) ){
		// eventIn needs to be inserted after comparedNode because eventIn has a time that is larger or equal
		// and than previous node

		nodelength++;
		insertNode -> next = comparedNode; // Set new node previous to the old node

		if(comparedNode->prev!=NULL){
			insertNode -> prev = comparedNode->prev;
			comparedNode -> prev -> next = insertNode;
		}

		comparedNode -> prev = insertNode; // Sets the old previous node to next field to the new node

	}


	else if(comparedNode -> event -> getTime() <= eventIn -> getTime() &&
			 comparedNode -> prev -> event -> getTime() <= insertNode -> event -> getTime()){
		// comparedNode is earlier in even queue so continue searching
		delete(insertNode);

		insertQueue(eventIn, comparedNode -> prev); // trusting the natural recursion

	}
}

/**
 * This determines the number of customers left in the event
 * @return It returns the number of customers left in the event queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
int EventQueue::numOfCustsInEventQueue() {
	int length = 0;
	node* Node = rootNode;

	//for each node in the queue
	for (int i = 0; i < nodelength; i++) {
		Node = Node -> prev;
		//see if the event is a customer
		if (Node->event->getActionType() >= -3) {

			length++;
		}
	}
	//Loop Invariant: at this point the number of customers in the event queue is returned

	return length;

}

/**
 * This returns the pointer to event at the head of the event queue
 * @return It returns the pointer to the head event in the event queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
Event *EventQueue::getHeadEvent() {

	Event *eventIn = rootNode -> prev -> event;

	node* prevNode = rootNode -> prev;

	rootNode -> prev = rootNode -> prev -> prev;

	delete(prevNode);

	//update the total size of the linked list
	nodelength--;

	return eventIn;

}

/**
 * This basically initializes the event queue
 * @param *eventIn the event to be inserted into the queue
 * @return It returns nothing
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
EventQueue::node* EventQueue::initEventInQueue(Event *eventIn) {

	node *Node = new node;
	// this fill in the data with the current event
	Node -> event = eventIn;

	//sets both previous nodes to NULL
	Node -> next = NULL;
	Node -> prev = NULL;

	return Node;
}

