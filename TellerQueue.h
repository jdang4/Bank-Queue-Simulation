/*
 * TellerQueue.h
 *
 *  Created on: Feb 12, 2018
 *      Author: jdang and pargyrakis
 */

#ifndef TELLERQUEUE_H_
#define TELLERQUEUE_H_

class TellerEvent;

class TellerQueue {

	struct node {
	TellerEvent *tellerEvent;
	int num; // number of tellers
	struct node *prev;
	};



public:

	// Constructor
	TellerQueue(EventQueue &eventQueue);

	// Destructor
	~TellerQueue();

	// Method Members
	void insertQueue(TellerEvent &event);
	int getQueueLength();
	int getPeopleInBank();
	TellerEvent *getEvent(int num);



private:

	// Data Members
	int nodelength;
	node* rootNode;

	// Method Members
	void insertQueue(TellerEvent *eventIn, node *comparedNode, int num);
	node* initTellerInQueue(TellerEvent *eventIn);
	node* getRootNode();
};



#endif
