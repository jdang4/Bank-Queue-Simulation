# Teller-Queue-Simulation

README for qSim.cpp by Jonathan Dang and Panagiotis Argyrakis (2/16/2018)

Summary: 
This program is an event-driven simulation that simulates customers arriving at a bank and standing line in front of one of the tellers. People would be arriving at random intervals and each person will wait in his/her line until they reach the head of the line. When they get to that point, the teller provides a service for a random amount of time and after that the person will leave.

How to run the program:
In the terminal the user should type in values for the number of customers, tellers, the simulation time, the average service time, and an optional seed value that would be used for starting the random number generator. If the program recieves less than 4 parameters or more than 5 (not counting the file name parameter) then the program will terminate. 
Here is the layout of what should be written in the terminal: "./qSim #customers #tellers simulationTime averageServiceTime <seed>"

Problems Encountered:
I had some difficulty with trying to start the assignment because I had a hard time trying to understand what exactly should I be doing. Also, I had some problems with trying to create a linked list, which was mainly due to my little experience in actually constructing them, but other than that I did not encounter many serious problems when doing this project.

qSim Class:
This class was basically the main program of this whole project. Within this, it called all the classes defined within this project. In this class, it basically created each customer and teller and giving them a random time. For customer it gave that object a random arrival time, and for a teller a random idle time. Next, qSim goes on to create a single event queue in a form of a linked list that consists of customer events and teller events and is organized according to the time of the event. The event with the earlier time would go ahead of the one with a later time. When each event is at the head, depending on the event it will preform an action (the action differs between the events) and is removed from the event queue. This will keep going until the event queue is empty. Once the event queue is empty, the statitics of the single event queue will be printed out. That is one of the two simulations that is shown in this program. The next one handles the situation where when a new customer enters the bank, they will look through all the tellers and go to the one with the shortest line. If multiple lines have the least number of customers in line, then the program will randomly pick one of those lines and that would be where the new customer goes. The multiple queue version basically does the same action as the single queue simulation. Once that is completed, it will also print out the statistics for the multiple queue one. 

Event Class:
This class is the base class to the CustomerEvent and TellerEvent class. In this class it basically holds the functions and data memebers that are associated with an event. It has a function to get the time of the event, adding an event to the event queue, and a get action function which will be used to distinguish between a customer event and a teller event. All the function prototypes and data memembers are stored within the header file so they can be used in other classes.

CustomerEvent Class:
This class is a subclass of the base class Event and it holds an action, an event, and an event queue variable. Inside this class it contains functions that inserts a customer event into the event queue, getting the serviceTime for each customer event, doing the actions when a customer interacts with a teller, and the action when they leave the bank. All the function prototypes and data members are stored inside the header file for this class (.h file) and inside the definitions file (.cpp file) it is where those functions are defined. The reason that the function prototypes and data members are stored in the header file is so that other classes can access them. 

TellerEvent Class:
This class is also a subclass of the base class Event and it holds an action, time of event, and the event queue variable. This class is similar to the CustomerEvent class, but it contains functions that are specific to a teller event. This also stores its function headers and data members inside the header file (.h file) so that it can be accessed by other classes. 

EventQueue Class:
This class is where all the events are stored into. It implements a linked list that sorts through all the Customer and Teller Events by time. How the linked list works is that it creates a structure Node and each node holds an event and two pointers that points to a node; one that points to the previous node and one that points to the node after the current one. By constructing the structure of the node made it easier to sort out the list. This class is implemented by having the entire event queue being filled with a customer event with its arrival event and throughout the program the execution events are added and removed from the event queue. All the function prototypes and data memembes were defined in the header file so that other classes would be able to use them. All the functions that were defined in the .cpp file were useful in designing how the EventQueue class should work.

TellerQueue Class:
This class is in charge of creating the teller queue. The teller queue is a list that holds all other teller queues. In the simulation where there is a single queue, the teller queue is not directly tied to a teller, but all the telers are retrieved from it. For the other simulation each teller queue is stored in the teller queue, making the big teller queue act almost like an array and the customers are gathered from that teller queue. This class was designed very similar to the event queue class. All the function prototypes and data members that are associated with this class were stored inside the header file so that other classes could have access to them. Inside the .cpp files is where the those functions were defined in.


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Test Cases:

One with a low number of customers, tellers, a low simulation time, and low average service time:

Command Line: "./qSim 5 5 10 5"

Output:

The number of customers entered: 5
The number of tellers entered: 5
The simulation time entered: 10
The average service time entered: 5

--------Single Line Simulation--------
Customers Served: 5
Time Required to Serve All Customers: 18.213 minutes 
Tellers: 5
Queuing System: Single Queue
Average Time Spent in Bank: 8.15013 minutes 
Standard Deviation: 1.3575 minutes 
Max Wait Time: 2.15796 minutes 
Teller Service Time: 33.8273 minutes 
Teller Idle Time: 66.4882 minutes 


--------Multiple Lines Simulation--------
Customers Served: 5
Time Required to Serve All Customers: 17.0003 minutes 
Tellers: 5
Queuing System: Multiple Queues
Average Time Spent in Bank: 7.67465 minutes 
Standard Deviation: 1.80369 minutes 
Max Wait Time: 1.17963 minutes 
Teller Service Time: 34.9727 minutes 
Teller Idle Time: 56.3002 minutes 

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

One with a medium number of customers, tellers, simulation time, and a low average service time:

Command Line: "./qSim 35 35 78 25"

Output:

The number of customers entered: 35
The number of tellers entered: 35
The simulation time entered: 78
The average service time entered: 25

--------Single Line Simulation--------
Customers Served: 35
Time Required to Serve All Customers: 115.173 minutes 
Tellers: 35
Queuing System: Single Queue
Average Time Spent in Bank: 28.7195 minutes 
Standard Deviation: 14.4806 minutes 
Max Wait Time: 0.443466 minutes 
Teller Service Time: 1001.1 minutes 
Teller Idle Time: 3113.48 minutes 


--------Multiple Lines Simulation--------
Customers Served: 35
Time Required to Serve All Customers: 120.338 minutes 
Tellers: 35
Queuing System: Multiple Queues
Average Time Spent in Bank: 23.4798 minutes 
Standard Deviation: 14.5139 minutes 
Max Wait Time: 0.754549 minutes 
Teller Service Time: 816.114 minutes 
Teller Idle Time: 3478.55 minutes 


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

One with a fairly large number of customers, tellers, a high simulation time, and a high average service time:

Command Line: "./qSim 120 120 180 100"

Output:

The number of customers entered: 120
The number of tellers entered: 120
The simulation time entered: 180
The average service time entered: 100

--------Single Line Simulation--------
Customers Served: 120
Time Required to Serve All Customers: 349.551 minutes 
Tellers: 120
Queuing System: Single Queue
Average Time Spent in Bank: 92.9112 minutes 
Standard Deviation: 54.7997 minutes 
Max Wait Time: 0.276199 minutes 
Teller Service Time: 11142.9 minutes 
Teller Idle Time: 31069.4 minutes 


--------Multiple Lines Simulation--------
Customers Served: 120
Time Required to Serve All Customers: 364.077 minutes 
Tellers: 120
Queuing System: Multiple Queues
Average Time Spent in Bank: 108.634 minutes 
Standard Deviation: 53.3144 minutes 
Max Wait Time: 0.578003 minutes 
Teller Service Time: 13028.3 minutes 
Teller Idle Time: 30905.4 minutes 

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Analysis on Single Queue vs Multiple Queues:

From comparing the average time to serve all customers between a single queue and a multiple queue it seems that overall a single queue is known to be better. The big difference is easily seen as the number of customers, tellers, simulation time, and average service time gets larger, but not so much when the values of those get smaller. When the values are small, the statistics between the single queue and multiple queues are pretty similar. Like the average time to serve all customers are fairly close with each other. Basing on my findings, overall, it seems to be better to use a single queue as it is shown to serve all the customers faster than having multiple of queues for any scenarios.
