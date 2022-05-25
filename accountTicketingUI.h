#pragma once

------------------------------------------------------------------------------------

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_
// declaring macros
#define PROMPT 1
#define DONOT_PROMPT 0

#include"ticket.h"
#include"account.h"
#include"commonHelpers.h"

 // declaring structures

struct AccountTicketingData
{
	struct Account* getAccount;   
	const int maximumSizeOfAccount; 
	struct Ticket* getTicket;     
	const int maximumSizeOfTicket;  
};

// declaring functions

// function to display a formated table header and display three column headers

void displayAccountSummaryHeader(void);

// function to display a formated table and display seven column headers

void displayAccountDetailHeader(void);

// function to display a formated record that align to respective header as defined in earlier described function "displayAccountSummaryHeader"

void displayAccountSummaryRecord(const struct Account* dataOfAccount);

// function to display a formated record that align to respective header as defined in earlier described function "displayAccountDetailHeader"

void  displayAccountDetailRecord(struct Account* dataOfAccount);

// function for the entry point to the logic

void  applicationStartup(struct AccountTicketingData* ticketOfAccount);

// function to display a logic menu

int menuLogin(const struct Account dataOfAccount[], int maximumElements);

// function to display the agent's menu options until user wishes to logout

void  menuAgent(struct AccountTicketingData* ticketOfAccount, struct Account* accountInformation);

// function to display the menu menu option of customer until the user want to logout

void  menuCustomer(struct Ticket* dataOfTicket, struct Account* accountInformation, int maximumElements);

// function to search the array received in argument 2 for the match on desired account number

int findAccountIndexByAcctNum(int accountNumber, const struct Account dataOfAccount[], int maximumElements, int promptAccountNumber);

// function to display the summary of all the valid account records(if number is greater than 0)

void displayAllAccountSummaryRecords(struct Account dataOfAccount[], int maximumElements);

// function to display detailed view of all and valid account record( if number is greater than 0)

void displayAllAccountDetailRecords(struct Account dataOfAccount[], int maximumElements);

// the function will stop the execution until user enter the "enter" key
 
void pauseExecution(void);

// function to display the header of the ticket

void displayHeaderOfTicket(void);

// function to display for the new ticket

void displayMessageForNewTicket(const struct AccountTicketingData* ticketNew);

// function to display the active ticket

void displayMessageForActiveTicket(const struct AccountTicketingData* ticketNew);

// function to display the customer ticket

void displayMassageForCustomerTicket(const  struct Ticket* ticketDisplay, const struct Account* accountInformation, int maximumElements);

// function to display the header of the customer ticket

void displayHeaderForCustomerTicket(void);

// function to generate or create new tickets for customer

void forNewTicketCreation(struct Ticket* ticketForNewCustomer, const struct Account* accountInformation, int maximumElements);

// function to display closed agent massages

void displayMessageForAgentTicket(const struct AccountTicketingData* ticketNewAgent);

// function to check the ticket number and cater the index

void customerTicketModification(struct Ticket* ticketForNewCustomer, struct Account* accountInformation, int maximumElements);

// function to romove tickets and the account associated with that ticket

int ticketsRemoving(const struct AccountTicketingData* ticketOfAccount, struct Account* accountInformation, int* allRemovedTickets);

// function to check agent ticket number and cater index for that ticket number

void modificationOfAgentTicket(const struct AccountTicketingData* ticketNewAgent, struct Account* accountInformation);

// function to check the user login name and password

int userLoginAndPasswordChecking(const struct Account* dataOfAccount, int maximumElements);

// function to cater menu for modifying customer ticket

void modifyCustomerTicketMenu(struct Ticket* dataOfTicket, struct Account* accountInformation);

// function caters Agent for modification of cuastomer ticket

void modifyAgentTicketMenu(struct Ticket* dataOfTicket, struct Account* accountInformation);


#endif
