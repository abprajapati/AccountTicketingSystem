#pragma once

#ifndef TICKET_H_
#define TICKET_H_


#define TICKETSFILE "tickets.txt"
#define TICKETSARCFILE "tickets_arc.txt"



#define LENGTH_OF_DISPLAY_NAME 30
#define SIZE_OF_MASSAGE 150
#define SIZE_OF_SUBJECT 30
#define MESSAGES_COUNT 20
#define NUMBER_OF_NEW_MASSAGE 1
#define LIMIT_RAMAIN 3
#define INDICATOR_ACTIVE_TICKET 1
#define INDICATOR_CLOSED_TICKET 0

// declaring structures 

struct Message
{
	char authorAccountType;
	char nameDisplay[LENGTH_OF_DISPLAY_NAME + 1];
	char detailOfMassage[SIZE_OF_MASSAGE + 1];
};

struct Ticket
{
	int uniqueNumber;
	int accountNumOfCustomer;
	int statusOfTicket;
	char lineOfSubject[SIZE_OF_SUBJECT + 1];
	int messageCount;
	struct Message detailsOfMassage[MESSAGES_COUNT];


};

// function for searching the array got in argument 2 about a match on a desired ticket number

int ticketIndexByTickNumberFinding(int ticketNumber, const struct Ticket dataOfTicket[], int maximumElements, int promptTicketNumber);

// function to save the details of the current updated tickets in tickets.txt file

int currentTicketsSaving(const struct Ticket dataOfTicket[], int maximumElements);

// function to load data of the tickets from tickets.txt

int loadTickets(struct Ticket dataOfTicket[], int maximumElements);

// function to closed removed ticket archive in tickets_arc.txt

int removedClosedTicketsArchive(const struct Ticket* dataOfTicket);

  // function to get closed tickets archive in tickets_arc.txt

void closedTicketsArchive(const struct Ticket* dataOfTicket);



#endif
