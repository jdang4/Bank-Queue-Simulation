/*
 * TellerQueue.cpp
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang and pargyrakis
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Event.h"
#include "EventQueue.h"
#include "TypesOfAction.h"
#include "TellerQueue.h"
#include "TellerEvent.h"

/**
 * It is the constructor of the teller queue class
 * @param &eventQueue It is the pointer to the main event queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
TellerQueue::TellerQueue(EventQueue &eventQueue) {

	// Initializes the root teller event
	TellerEvent * tellerEventStart = new TellerEvent(eventQueue,-10, *this);

	rootNode = new node();
	rootNode -> tellerEvent = tellerEventStart;
	rootNode -> num = 0;
	rootNode -> prev = NULL;
	nodelength = 0;
}

/**
 * This is the destructor of the teller queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
TellerQueue::~TellerQueue() {

	node* tellNode;
	// Sorts through all the teller queues to delete all the nodes
	for(int i = nodelength; i >= 0; i--) {
		tellNode = rootNode;
		for(int j = 0; j < nodelength; j++) {
			tellNode = tellNode -> prev;
		}

		delete tellNode->prev;
	}
}

/**
 * This gets the root node of the teller queue
 * @return It returns the root node of the teller queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
TellerQueue::node* TellerQueue::getRootNode() {

	return rootNode;
}


/**
 * This gets the length of the teller queue
 * @return It returns the length of the teller queue
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
int TellerQueue::getQueueLength() {

	return nodelength;
}

/**
 * Inserts a teller queue into the queue in respect to time
 * @param *event The teller event that is being inserted
 * @param *comparedNode The node which the inserted teller event will be compared to
 * @param num Inserts the teller number referring to the teller queue number
 * @return It returns nothing
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
void TellerQueue::insertQueue(TellerEvent *event, node *comparedNode, int num) {
	// the node to be inserted
	node* insertNode = initTellerInQueue(event);

	// this controls where to insert inserted node
	if(comparedNode-> prev == NULL) {

		// updates the members of the node
		insertNode -> num = num;
		comparedNode -> prev = insertNode;
		nodelength++;
	}

	else {

		insertQueue(event, comparedNode -> prev, ++num);
		// Free used objects
		free(insertNode);
	}
}

/**
 * This inserts a teller into the teller queue and assign it to the next id
 * @param &event The teller event to be inserted
 * @return It returns nothing
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
void TellerQueue::insertQueue(TellerEvent &event) {

	insertQueue(&event, rootNode, 1);
}

/**
 * This gets the next event from the teller queue
 * @param num This is the queue number referring to which teller queue to grab
 * @return This returns a pointer to the teller event
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
TellerEvent *TellerQueue::getEvent(int num) {
	node* tellNode = rootNode;
	// Increment through the teller queues to get desired teller queue
	for(int i = 0; i < num; i++) {
		tellNode = tellNode -> prev;
	}

	TellerEvent *tellEvent = tellNode -> tellerEvent;

	return tellEvent;
}

/**
 * This initializes the teller queue
 * @param *event The teller event that is going to be inserted in the teller queue
 * @return It returns a reference to the node
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
TellerQueue::node* TellerQueue::initTellerInQueue(TellerEvent *event) {

	node *Node = new node;
	Node -> tellerEvent = event;
	Node -> prev = NULL;
	Node -> num = -20;
	return Node;
}

/**
 * This counts up all the customers that are currently inside the teller queues
 * @return It return the number of customers in the teller queues
 *
 * @author Jonathan Dang and Panagiotis Argyrakis
 */
int TellerQueue::getPeopleInBank() {
	int length = 0;
	node* tellNode = rootNode;
	length = length + tellNode->tellerEvent->tellerQueue->getQueueLength();

	// Increment through all the teller queues to get the teller queue length
	for(int i = 0; i < nodelength; i++) {
		tellNode = tellNode -> prev;
		length = length + tellNode->tellerEvent->tellerQueue->getQueueLength();
	}

	return length;
}

