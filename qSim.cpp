/*
 * qSim.cpp
 *
 *  Created on: Feb 8, 2018
 *      Author: jdang and pargyrakis
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <climits>

#include "CustomerEvent.h"
#include "Event.h"
#include "EventQueue.h"
#include "TellerQueue.h"
#include "TypesOfAction.h"
#include "TellerEvent.h"

using namespace std;


int main(int argc, char *argv[]) {

	// Checks whether enough commands have been entered
	if (argc < 5) {
		cout << "\nERROR: Incorrect Command Line Input \n";
		cout << "The format is: ";
		cout << "./qSim #customers #tellers simulationTime averageServiceTime (optional) <seed>";
		exit(0);
	}

	cout << "\nThe number of customers entered: " << argv[1] << "\n";
	int customers = atoi(argv[1]);

	if (customers < 0) {
		cout << "Invalid input for number of customers\n";
		exit(0);
	}

	cout << "The number of tellers entered: " << argv[2] << "\n";
	int tellers = atoi(argv[2]);

	if (tellers < 0) {
		cout << "ERROR: Invalid input for number of tellers\n";
		exit(0);
	}

	// Checks whether a correct number of customers and tellers has been entered
	if (customers == 0 || tellers == 0) {
		// No customers or tellers were entered
		cout << "ERROR: Not Enough Customers or Tellers\n";
		exit(0);
	}

	cout << "The simulation time entered: " << argv[3] << "\n";
	int simulationTime = atoi(argv[3]);

	if (simulationTime < 0) {
		cout << "ERROR: invalid simulation time\n";
		exit(0);
	}

	cout << "The average service time entered: " << argv[4] << "\n";
	float averageServiceTime = atoi(argv[4]);

	if (averageServiceTime < 0) {
		cout << "ERROR: invalid average service time\n";
		exit(0);
	}

	// Sets random seed if user specifies otherwise use a random seed
	if (argc >= 6 && atoi(argv[5]) != 0) {
		// User has specified a random seed so use it
		srand(atoi(argv[5]));

		cout << "The random seed entered entered: " << argv[5] << "\n";
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Single Line Simulation

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initializing necessary objects
	EventQueue *eventQueue = new EventQueue(); // Event Queue Constructor
	TellerQueue *tellerQueue = new TellerQueue(*eventQueue); // TellerQueue Constructor

	// creates customers number of CustomerEvents
	for (int i = 1; i < customers + 1; i++) {
		// Generate a random arrival time
		float arrivalTime = simulationTime * (rand() / float(RAND_MAX));

		//cout << "The random arrival time of customer: " << i << " is " << arrivalTime << "\n";

		new CustomerEvent(*eventQueue, arrivalTime); // Initialize a new CustEvent
		// LOOP-INVARIANT: at this point, i number of CustomerEvents are in the event queue
	}

	// creates tellers number of TellerEvent
	for (int i = 1; i < tellers + 1; i++) {
		// Generates a random idle time for a teller
		float idleTime = 599/60 * ( rand() / float(RAND_MAX) ) + 1 / 60;

		//cout << "The random idle time of Teller: " << i << " is " << idleTime << "\n";

		// Create a new teller event with the random idle time and insert in teller
		(new TellerEvent(*eventQueue, idleTime, *tellerQueue))->insertTellerToQueue();
		// Loop Invariant: at this point, the teller event is initialized with a random idle time and inserted in the teller queue
	}

	float idleTime = 0.0;
	float currentTime = 0;
	bool noCustAtStartOfDay = false;
	bool firstRun = true;

	// Create Event object nextEvent which is the next event from the event queue
	Event *nextEvent = eventQueue->getHeadEvent();

	// this ensures that the nextEvent does not have an arrival time of 0
	if (nextEvent->getTime() != 0) {
		// nextEvent time is not 0, so start idling of tellers
		TellerEvent * teller;

		for (int i = 0; i < tellers; i++) {
			// Start idling all tellers
			teller = tellerQueue->getEvent(i + 1);
			idleTime = idleTime + teller->idle(currentTime);
			// Loop Invariant: at this time, the idleTime is equal to the idle time of i Tellers together
		}

		nextEvent->addEvent(); // returns next event to the event queue
		noCustAtStartOfDay = true;
	}

	float servTime = 0;
	float averageTimeInBank = 0;
	float custBankTimes[customers];
	float tempTimeOfAction;
	int custBankCount = 0;
	float maxTimeInLine = 0;
	float stdDev = 0;
	int action;


	while (tellerQueue -> getPeopleInBank() !=0 || eventQueue->numOfCustsInEventQueue() != 0) {

		// this conditional statement gets the first event from the event queue and toggles the boolean flags depending on the initial condition
		if (firstRun == false) {
			// Currently nextEvent is not updated so this updates it
			nextEvent = eventQueue->getHeadEvent();
		}

	    else if (noCustAtStartOfDay) {
			nextEvent = eventQueue->getHeadEvent(); // gets the next event
			noCustAtStartOfDay =  false;
			firstRun = false;
		}

	    else if (firstRun) {
			firstRun = false;
		}

		action = nextEvent->getActionType(); // gets the action of the next event
		currentTime = nextEvent->getTime();  // sets the time of the program to the time of the next event

		// this controls what methods are called, which is based on the action of the event from the event queue
		if (action == CustArrive) {
			// the event is a customer arrival, insert customer into a teller queue
			tellerQueue->getEvent(0)->tellerQueue->insertQueue(*nextEvent);
		}

		// if the event is a teller
		else if (action <= TellerIdle) {
			// gets the time of the Teller Event
			tempTimeOfAction = static_cast<TellerEvent*>(nextEvent)->getNextCustomer(currentTime,averageServiceTime);

			// if teller event is an idle event
			if (nextEvent->getActionType() == TellerIdle) {
				// next event from event queue is an idling teller
				idleTime = idleTime + tempTimeOfAction; /* increments idleTime with the next action idle time*/
			}

			else {
				// the Teller event is a customer service event
				servTime = servTime + tempTimeOfAction; // increments the service time with the service time of the next event
			}
		}

		else if (action == CustService) {

			// sets customer's time in bank
			float timeInBank = (static_cast<CustomerEvent*>(nextEvent))->custLeaveBank();

			// sets customers time in bank
			float timeInLine = timeInBank - (static_cast<CustomerEvent*>(nextEvent))->getServiceTime();

			if (timeInLine > maxTimeInLine) {
				maxTimeInLine = timeInLine;
			}

			// Perform statistics calculations
			averageTimeInBank = averageTimeInBank + timeInBank;
			custBankTimes[custBankCount] = timeInBank;
			custBankCount++;

			// deletes the nextEvent object
			delete nextEvent;
			// Loop Invariant: at this point, an event from the event queue has been processed and the nextEv object has been deleted
		}
	}

	// updates the idle time of the tellers if end of day is not yet reached
	if (currentTime < simulationTime) {

		idleTime = idleTime + tellers * (simulationTime - currentTime);
	}


	for (int i = 0; i < customers; i++) {

		stdDev = stdDev + (custBankTimes[i] - (averageTimeInBank/customers)) * (custBankTimes[i] - (averageTimeInBank/customers) );
		// Loop Invariant: at this point, i is less than the number of customers
	}

	stdDev = sqrt(stdDev / customers);

	cout << endl;
	cout << "--------Single Line Simulation--------" << "\n";
	cout << "Customers Served: " << customers << "\n";
	cout << "Time Required to Serve All Customers: " << currentTime << " minutes \n";
	cout << "Tellers: " << tellers << "\n";
	cout << "Queuing System: Single Queue" << "\n";
	cout << "Average Time Spent in Bank: " << (averageTimeInBank/customers) << " minutes \n";
	cout << "Standard Deviation: " << stdDev << " minutes \n";
	cout << "Max Wait Time: " << maxTimeInLine << " minutes \n";
	cout << "Teller Service Time: " << servTime << " minutes \n";
	cout << "Teller Idle Time: " << idleTime << " minutes \n";
	cout << endl;
	cout << endl;

	// Free the objects used
	delete eventQueue;
	delete tellerQueue;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Multiple Lines Simulation

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Controls setting of random seed
	if (argc >= 6 && atoi(argv[5]) != 0) {

		srand(atoi(argv[5]));
	}

	// Initializing necessary objects
	eventQueue = new EventQueue();
	tellerQueue = new TellerQueue(*eventQueue);

	// Initializing all customers
	for (int i = 0; i < customers; i++) {

		float arrivalTime = simulationTime * (rand() / float(RAND_MAX));
		new CustomerEvent(*eventQueue, arrivalTime);
		// Loop Invariant: at this point,  a customer object has been initialized with a random arrival time
	}

	// Initializing all tellers
	for (int i = 0; i < tellers; i++) {
		float idleTime = ( (599/60) * (rand()/float(RAND_MAX)) ) + 1/60;
		// Prevent 0 idle time
		(new TellerEvent(*eventQueue, idleTime, *tellerQueue))->insertTellerToQueue();
		// Loop Invariant: at this point, a teller event has been created with a random idle time
	}

	currentTime = 0;
	noCustAtStartOfDay = false;
	firstRun = true;
	nextEvent = eventQueue->getHeadEvent();
	idleTime = 0;

	// Double-checks if there are customers with an arrival time of 0
	if (nextEvent->getTime() != 0) {
		// No customer with arrival time 0
		TellerEvent *teller;

		// Set all tellers to idle with idle times
		for (int i = 0; i < tellers; i++) {

			teller = tellerQueue->getEvent(i + 1);
			idleTime = idleTime + teller->idle(currentTime);
			// Loop-invariant: at this point the idleTime is now the sum idle time of all previously called tellers' idle time
		}

		nextEvent->addEvent(); // Return the next event to the queue
		noCustAtStartOfDay = true;
	}

	// reseting the variables and statistics
	averageTimeInBank = 0;
	custBankCount = 0;
	servTime = 0;
	maxTimeInLine = 0;
	tempTimeOfAction = 0;
	stdDev = 0;
	action = -10;

	// This loop sorts through all events in the event queue until all customers have left the bank
	while (tellerQueue -> getPeopleInBank() != 0 || eventQueue->numOfCustsInEventQueue() != 0) {

		// Controls action on first event in event queue
		if (firstRun == false) {
			// If this is not the first run, get the next event from the event queue
			nextEvent = eventQueue->getHeadEvent();
		}

	    else if (noCustAtStartOfDay) {
	    	// There is no customer with time of 0
			nextEvent = eventQueue->getHeadEvent(); // get the next customer
			// Set boolean flags
			noCustAtStartOfDay =  false;
			firstRun = false;
		}

	    else if (firstRun) {
	    	// This is the first run, so reset flag and do not get new event
			firstRun = false;
		}

		action = nextEvent->getActionType(); // gets the action type of next the event
		currentTime = nextEvent->getTime(); // sets the current time

		// Performs action based on the action type of the event
		if (action == CustArrive){
			int leastCustLine = INT_MAX; // Find the teller queue with least amount of customer events

			int i; // Counting the variables

			TellerQueue *TellCust = new TellerQueue(*eventQueue);

			// This for loop gets smallest teller queue length
			for (i = 1; i <= tellerQueue->getQueueLength(); i++) {

				if ( (tellerQueue -> getEvent(i)) -> queueLength() < leastCustLine) {
					leastCustLine = (tellerQueue->getEvent(i))->queueLength();
				}
				// Loop Invariant: at this point, the length of the teller queue has been checked
			}

			// Finds all the teller queues which have this size of line as determined in loop above
			for (i = 1; i <= tellerQueue->getQueueLength(); i++) {
				if ( (tellerQueue->getEvent(i)) -> queueLength() == leastCustLine ) {

					TellCust->insertQueue( *(tellerQueue->getEvent(i)) );
				}
				// Loop Invariant: at this point the teller's queue length has been checked and the minimum size has been found
			}

			// Get a random teller queue
			int randNum = rand() % (TellCust->getQueueLength()) + 1;
			TellCust->getEvent(randNum)->tellerQueue->insertQueue(*nextEvent);

			// Deletes the used objects
			delete TellCust;
		}

		else if (action <= TellerIdle) {

			// gets the time of the next Teller Event action
			tempTimeOfAction = static_cast<TellerEvent*>(nextEvent) -> getNextCustomer(currentTime, averageServiceTime);

			// Controls time of action based on action type
			if (nextEvent->getActionType() == TellerIdle) {

				idleTime = idleTime + tempTimeOfAction;
			}

			else {

				servTime = servTime + tempTimeOfAction;
			}
		}

		else if (action == CustService) {
			// Update variables later used to calculate statistics
			float timeInBank = (static_cast<CustomerEvent*>(nextEvent))->custLeaveBank();

			float timeInLine = timeInBank - (static_cast<CustomerEvent*>(nextEvent)) -> getServiceTime();

			// Update the maximum time spent in line
			if (timeInLine > maxTimeInLine) {
				maxTimeInLine = timeInLine;
			}

			// adds the time in bank to a total
			averageTimeInBank = averageTimeInBank + timeInBank;
			custBankTimes[custBankCount] = timeInBank;
			custBankCount++;

			// delete used objects
			delete nextEvent;
		}
	}

	// start idling tellers if simulation has not ended yet
	if (currentTime < simulationTime) {

		idleTime = idleTime + tellers * (simulationTime - currentTime);
	}

	// calculates the standard deviation
	for (int i = 0; i < customers; i++) {
		stdDev = stdDev + (custBankTimes[i] - averageTimeInBank / customers) * (custBankTimes[i] - averageTimeInBank / customers);
		// Loop Invariant: at this point, i is less than the number of customers
	}

	stdDev = sqrt(stdDev / customers);

	cout << "--------Multiple Lines Simulation--------" << "\n";
	cout << "Customers Served: " << customers << "\n";
	cout << "Time Required to Serve All Customers: " << currentTime << " minutes \n";
	cout << "Tellers: " << tellers << "\n";
	cout << "Queuing System: Multiple Queues"<<"\n";
	cout << "Average Time Spent in Bank: " << (averageTimeInBank / customers) << " minutes \n";
	cout << "Standard Deviation: " << stdDev << " minutes \n";
	cout << "Max Wait Time: " << maxTimeInLine << " minutes \n";
	cout << "Teller Service Time: " << servTime << " minutes \n";
	cout << "Teller Idle Time: " << idleTime << " minutes \n";
	cout << endl;

	// frees all the used objects
	delete eventQueue;
	delete tellerQueue;
}


