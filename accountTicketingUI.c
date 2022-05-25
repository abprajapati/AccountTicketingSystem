
#define _CRT_SECURE_NO_WARNINGS

// System Library
#include<stdio.h>
#include<string.h>

// User-defined library
#include "account.h"
#include"commonHelpers.h"
#include"accountTicketingUI.h"


// declaring functions

// function to display a formated table header and display three column headers

void displayAccountSummaryHeader()
{

	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

// function to display a formated table and display seven column headers

void displayAccountDetailHeader()
{

	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

// function to display a formated record that align to respective header as defined in earlier described function "displayAccountSummaryHeader"

void displayAccountSummaryRecord(const struct Account* dataOfAccount)
{

	printf("%05d %-9s %5d", dataOfAccount->customerAccountNumber, dataOfAccount->typeOfAccount == 'A' ? "AGENT" : "CUSTOMER", dataOfAccount->demo.customerBirthYear);
	putchar('\n');
}

// function to display a formated record that align to respective header as defined in earlier described function "displayAccountDetailHeader"

void displayAccountDetailRecord(struct Account* dataOfAccount)
{

	int i, keep = 0;

	keep = strlen(dataOfAccount->login.passwordOfUser);
	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s ", dataOfAccount->customerAccountNumber, dataOfAccount->typeOfAccount == 'A' ? "AGENT" : "CUSTOMER", dataOfAccount->demo.customerBirthYear, dataOfAccount->demo.totalHouseholdIncome, dataOfAccount->demo.customerCountry, dataOfAccount->login.nameOfCustomer, dataOfAccount->login.loginNameOfUser);

	for (i = 0; i < keep; i++)
	{
		if ((i + 1) % 2 == 0)
		{

			printf("*");
		}
		else
		{

			printf("%c", dataOfAccount->login.passwordOfUser[i]);
		}
	}

	putchar('\n');
}

// function to display the menu menu option of customer until the user want to logout

void  menuCustomer(struct Ticket* dataOfTicket, struct Account* accountInformation, int maximumElements)
{
	int optionForCustomer = 0, info = 0, record = 1, minimum = 0, maximum = 4;

	while (record)
	{
		printf("CUSTOMER: %s (%d)\n", accountInformation->login.nameOfCustomer, accountInformation->customerAccountNumber);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		optionForCustomer = getIntFromRange(minimum, maximum);
		putchar('\n');

		switch (optionForCustomer)
		{

		case 1:
			displayAccountDetailHeader();
			displayAccountDetailRecord(accountInformation);
			putchar('\n');
			pauseExecution();
			break;

		case 2:
			forNewTicketCreation(dataOfTicket, accountInformation, maximumElements);
			break;

		case 3:
			customerTicketModification(dataOfTicket, accountInformation, maximumElements);
			break;

		case 4:
			displayMassageForCustomerTicket(dataOfTicket, accountInformation, maximumElements);
			break;

		case 0:

			info = currentTicketsSaving(dataOfTicket, maximumElements);
			printf("Saving session modifications...\n");
			printf("   %d tickets saved.\n", info);
			printf("### LOGGED OUT ###\n\n");
			record = 0;
			break;
		}
	} 

}

// function to display the header of the ticket

void displayHeaderOfTicket(void)
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

// function to display for the new ticket

void displayMessageForNewTicket(const struct AccountTicketingData* ticketNew)
{

	int i = 0, j = 0, record = 1, info = 1, count = 0, ticketNumber;

	while (record)
	{

		info = 1;
		displayHeaderOfTicket();
		for (i = 0; i < ticketNew->maximumSizeOfTicket; i++)
		{
			if (ticketNew->getTicket[i].messageCount == NUMBER_OF_NEW_MASSAGE && ticketNew->getTicket[i].uniqueNumber != 0)
			{

				printf("%06d %5d %-15s %-6s %-30s %5d\n", ticketNew->getTicket[i].uniqueNumber, ticketNew->getTicket[i].accountNumOfCustomer, ticketNew->getTicket[i].detailsOfMassage->nameDisplay, ticketNew->getTicket[i].statusOfTicket == 1 ? "ACTIVE" : "CLOSED", ticketNew->getTicket[i].lineOfSubject, ticketNew->getTicket[i].messageCount);
			}

		}

		printf("------ ----- --------------- ------ ------------------------------ --------");
		printf("\n\n");
		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		do
		{

			ticketNumber = getInteger();
			if (ticketNumber == 0)
			{
				putchar('\n');
				record = 0;
				info = 0;
			}
			else if (ticketNumber < 0)
			{
				printf("ERROR: Value must be positive or zero: ");
			}
			else
			{
				putchar('\n');
				info = 0;
			}

		} while (info);
		info = 1;


		if (ticketNumber != 0)
		{

			count = 0;
			for (i = 0; i < ticketNew->maximumSizeOfTicket && info; i++)
			{
				if (ticketNew->getTicket[i].uniqueNumber == ticketNumber && ticketNew->getTicket[i].uniqueNumber != 0)
				{

					printf("================================================================================\n");
					printf("%06d (%s) Re: %s\n", ticketNew->getTicket[i].uniqueNumber, ticketNew->getTicket[i].statusOfTicket == 1 ? "ACTIVE" : "CLOSED", ticketNew->getTicket[i].lineOfSubject);
					printf("================================================================================\n");

					for (j = 0; j < ticketNew->getTicket[i].messageCount; j++)
					{
						printf("%s (%s):\n", ticketNew->getTicket[i].detailsOfMassage[j].authorAccountType == 'A' ? "AGENT" : "CUSTOMER", ticketNew->getTicket[i].detailsOfMassage[j].nameDisplay);
						printf("   %s\n\n", ticketNew->getTicket[i].detailsOfMassage[j].detailOfMassage);

						count++;

						if (count % 5 == 0)
						{

							pauseExecution();
						}
					}

					if (count % 5 != 0)
					{
						pauseExecution();
					}
					info = 0;

				}
			}
		}

		if (ticketNumber != 0)
		{
			if (info)
			{
				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();

			}
		}

	} 
}

// function to display the active ticket

void displayMessageForActiveTicket(const struct AccountTicketingData* ticketNew)
{
	int i = 0, j = 0, record = 1, info = 1, keep = 0, ticketNumber;

	do
	{
		info = 1;
		displayHeaderOfTicket();

		for (i = 0; i < ticketNew->maximumSizeOfTicket; i++)
		{
			if (ticketNew->getTicket[i].statusOfTicket == INDICATOR_ACTIVE_TICKET && ticketNew->getTicket[i].uniqueNumber != 0)
			{
				printf("%06d %5d %-15s %-6s %-30s %5d\n", ticketNew->getTicket[i].uniqueNumber, ticketNew->getTicket[i].accountNumOfCustomer, ticketNew->getTicket[i].detailsOfMassage->nameDisplay, ticketNew->getTicket[i].statusOfTicket == 1 ? "ACTIVE" : "CLOSED", ticketNew->getTicket[i].lineOfSubject, ticketNew->getTicket[i].messageCount);

			}

		}

		printf("------ ----- --------------- ------ ------------------------------ --------");
		printf("\n\n");
		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		do
		{
			ticketNumber = getInteger();

			if (ticketNumber == 0)
			{
				putchar('\n');
				record = 0;
				info = 0;
			}
			
			else if (ticketNumber < 0)
			{

				printf("ERROR: Value must be positive or zero: ");
			}
			else
			{
				putchar('\n');
				info = 0;
			}

		} while (info);
		info = 1;

		if (ticketNumber != 0)
		{

			keep = 0;
			for (i = 0; i < ticketNew->maximumSizeOfTicket && info; i++)
			{
				if (ticketNew->getTicket[i].uniqueNumber == ticketNumber && ticketNew->getTicket[i].uniqueNumber != 0)
				{
					printf("================================================================================\n");
					printf("%06d (%s) Re: %s\n", ticketNew->getTicket[i].uniqueNumber, ticketNew->getTicket[i].statusOfTicket == 1 ? "ACTIVE" : "CLOSED", ticketNew->getTicket[i].lineOfSubject);
					printf("================================================================================\n");

					for (j = 0; j < ticketNew->getTicket[i].messageCount; j++)
					{
						printf("%s (%s):\n", ticketNew->getTicket[i].detailsOfMassage[j].authorAccountType == 'A' ? "AGENT" : "CUSTOMER", ticketNew->getTicket[i].detailsOfMassage[j].nameDisplay);
						printf("   %s\n\n", ticketNew->getTicket[i].detailsOfMassage[j].detailOfMassage);

						keep++;

						if (keep % 5 == 0)
						{
							pauseExecution();
						}
					}

					if (keep % 5 != 0)
					{
						pauseExecution();
					}
					info = 0;
				}
			}
		}

		if (ticketNumber != 0)
		{
			if (info)
			{

				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();
			}
		}

	} while (record);
}

// function to display the header of the customer ticket

void displayHeaderForCustomerTicket(void)
{

	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}

// function to display the customer ticket

void displayMassageForCustomerTicket(const struct Ticket* ticketDisplay, const struct Account* accountInformation, int maximumElements)
{

	int i = 0, j = 0, keep = 0, record = 1, info = 1, ticketNumber, indexNumber = 0;

	while (record)
	{

		info = 1;
		displayHeaderForCustomerTicket();

		for (i = 0; i < maximumElements; i++)
		{
			if (ticketDisplay[i].accountNumOfCustomer == accountInformation->customerAccountNumber && ticketDisplay[i].uniqueNumber != 0)
			{

				printf("%06d %-6s %-30s %5d\n", ticketDisplay[i].uniqueNumber, ticketDisplay[i].statusOfTicket == 1 ? "ACTIVE" : "CLOSED", ticketDisplay[i].lineOfSubject, ticketDisplay[i].messageCount);
			}

		}

		printf("------ ------ ------------------------------ --------");
		printf("\n\n");


		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		while (info)
		{
			ticketNumber = getInteger();


			if (ticketNumber < 0)
			{
				printf("ERROR: Value must be positive or zero: ");
			}
			else if (ticketNumber == 0)
			{
				putchar('\n');
				record = 0;
				info = 0;
			}
			else
			{
				putchar('\n');
				info = 0;
			}

		}
		info = 1;

		if (ticketNumber != 0)
		{

			indexNumber = ticketIndexByTickNumberFinding(ticketNumber, ticketDisplay, maximumElements, DONOT_PROMPT);

			if (ticketDisplay[indexNumber].accountNumOfCustomer != accountInformation->customerAccountNumber && indexNumber != -1)
			{
				printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
				pauseExecution();
				info = 0;
			}

			if (ticketDisplay[indexNumber].accountNumOfCustomer == accountInformation->customerAccountNumber && indexNumber != -1)
			{

				keep = 0;
				for (i = 0; i < maximumElements && info; i++)
				{

					if (ticketDisplay[i].uniqueNumber == ticketNumber && ticketDisplay[i].uniqueNumber != 0)
					{

						printf("================================================================================\n");
						printf("%06d (%s) Re: %s\n", ticketDisplay[i].uniqueNumber, ticketDisplay[i].statusOfTicket == 1 ? "ACTIVE" : "CLOSED", ticketDisplay[i].lineOfSubject);
						printf("================================================================================\n");

						for (j = 0; j < ticketDisplay[i].messageCount; j++)
						{

							printf("%s (%s):\n", ticketDisplay[i].detailsOfMassage[j].authorAccountType == 'A' ? "AGENT" : "CUSTOMER", ticketDisplay[i].detailsOfMassage[j].nameDisplay);
							printf("   %s\n\n", ticketDisplay[i].detailsOfMassage[j].detailOfMassage);

							keep++;

							if (keep % 5 == 0)
							{
								pauseExecution();
							}

						}

						if (keep % 5 != 0)
						{
							pauseExecution();
						}
						info = 0;

					}

				}

			}

			if (info)
			{
				printf("ERROR: Invalid ticket number.\n\n");
				pauseExecution();

			}
		}

	} 
}

// the function will stop the execution until user enter the "enter" key

void pauseExecution(void)
{

	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}

// function to search the array received in argument 2 for the match on desired account number

int findAccountIndexByAcctNum(int accountNumber, const struct Account dataOfAccount[], int maximumElements, int promptAccountNumber)
{

	int i, foundIndex;

	if (promptAccountNumber)
	{

		printf("Enter the account#: ");
		accountNumber = getPositiveInteger();
		putchar('\n');
	}

	for (i = 0, foundIndex = -1; foundIndex < 0 && i < maximumElements; i++)
	{

		if (accountNumber == dataOfAccount[i].customerAccountNumber)
		{
			foundIndex = i;
		}

	}

	return foundIndex;
}

// function for the entry point to the logic

void  applicationStartup(struct AccountTicketingData* ticketOfAccount)
{

	int indexNumber;
	do
	{

		indexNumber = menuLogin(ticketOfAccount->getAccount, ticketOfAccount->maximumSizeOfAccount);

		if (indexNumber != -1)
		{
			if (ticketOfAccount->getAccount[indexNumber].typeOfAccount == 'C')
			{

				menuCustomer(ticketOfAccount->getTicket, &ticketOfAccount->getAccount[indexNumber], ticketOfAccount->maximumSizeOfTicket);
			}
			else if (ticketOfAccount->getAccount[indexNumber].typeOfAccount == 'A')
			{

				menuAgent(ticketOfAccount, &ticketOfAccount->getAccount[indexNumber]);
			}
			
		}
		else
		{
			printf("==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n");
			
		}
	} while (indexNumber != -1);

}


// function to display a logic menu

int menuLogin(const struct Account dataOfAccount[], int maximumElements)
{
	int getOption, minimum = 0, maximum = 1, record = 1, indexNumber = 0;
	char ch = 0;

	do
	{

		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n\n");
		printf("Selection: ");

		getOption = getIntFromRange(minimum, maximum);
		putchar('\n');

		switch (getOption)
		{

		case 0:
			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			ch = getCharOption("yYnN");

			if (ch == 'y' || ch == 'Y')
			{
				indexNumber = -1;
				record = 0;
			}
			else
			{
				record = 1;
			}
			putchar('\n');
			break;

		case 1:
			indexNumber = userLoginAndPasswordChecking(dataOfAccount, maximumElements);

			if (indexNumber > 0)
			{
				record = 0;
			}
			break;
		}
	} while (record);

	return indexNumber;
}

// function to display the agent's menu options until user wishes to logout

void  menuAgent(struct AccountTicketingData* ticketOfAccount, struct Account* accountInformation)
{

	int getoption, minimum = 0, maximum = 12, accountNumber = 0, maximumAccounts = 0, record = 1, i;
	int indexNumber;
	int tickets1Count = 0, totalRemovedMessages = 0, totalClosedMessages = 0, removedAccountCount = 0, allRemovedMessages = 0;
	int allRemovedTickets = 0, allClosedTickets = 0, totalTickets2 = 0, totalNumberOfTickets = 0, totalNumberOfAccounts = 0;
	char yesOrNo = 0, ch = 0;

	do
	{
		printf("AGENT: %s (%d)\n", accountInformation->login.nameOfCustomer, accountInformation->customerAccountNumber);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		getoption = getIntFromRange(minimum, maximum);

		switch (getoption)
		{
		case 1:
			putchar('\n');
			indexNumber = findAccountIndexByAcctNum(0, ticketOfAccount->getAccount, ticketOfAccount->maximumSizeOfAccount, DONOT_PROMPT);
			if (indexNumber < 0)
			{

				printf("ERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}

			else
			{

				for (i = 0; i < ticketOfAccount->maximumSizeOfAccount; i++)
				{
					if (ticketOfAccount->getAccount[i].customerAccountNumber > maximumAccounts)
					{

						maximumAccounts = ticketOfAccount->getAccount[i].customerAccountNumber;
					}
				}

				ticketOfAccount->getAccount[indexNumber].customerAccountNumber = maximumAccounts + 1;

				getAccount(&ticketOfAccount->getAccount[indexNumber]);
				getUserLogin(&ticketOfAccount->getAccount[indexNumber]);
				getDemographic(&ticketOfAccount->getAccount[indexNumber]);
				printf("*** New account added! ***\n\n");
				pauseExecution();
			}
			break;

		case 2:
			putchar('\n');

			do
			{
				indexNumber = findAccountIndexByAcctNum(accountNumber, ticketOfAccount->getAccount, ticketOfAccount->maximumSizeOfAccount, PROMPT);
			} while (indexNumber == -1);

			updateAccount(&ticketOfAccount->getAccount[indexNumber]);
			break;

		case 3:
			putchar('\n');
			printf("Enter the account#: ");
			accountNumber = getPositiveInteger();

			if (accountNumber == accountInformation->customerAccountNumber)
			{
				putchar('\n');
				printf("ERROR: You can't remove your own account!\n\n");
				clearStandardInputBuffer();
				pauseExecution();
			}
			else
			{
				indexNumber = findAccountIndexByAcctNum(accountNumber, ticketOfAccount->getAccount, ticketOfAccount->maximumSizeOfAccount, DONOT_PROMPT);

				displayAccountDetailHeader();
				displayAccountDetailRecord(&ticketOfAccount->getAccount[indexNumber]);
				putchar('\n');

				printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
				ch = getCharOption("YN");
				putchar('\n');

				tickets1Count = 0;
				totalRemovedMessages = 0;

				if (ch == 'Y')
				{
					tickets1Count = ticketsRemoving(ticketOfAccount, &ticketOfAccount->getAccount[indexNumber], &totalRemovedMessages);
					allRemovedTickets = allRemovedTickets + tickets1Count;
					allRemovedMessages = allRemovedMessages + totalRemovedMessages;
					removeAccountArchive(&ticketOfAccount->getAccount[indexNumber]);
					ticketOfAccount->getAccount[indexNumber].customerAccountNumber = 0;

					removedAccountCount++;
					printf("*** Account Removed! ***\n\n");
					pauseExecution();
				}
				else
				{

					printf("*** No changes made! ***\n\n");
					pauseExecution();
				}
			}
			break;

		case 4:
			putchar('\n');
			displayAllAccountSummaryRecords(ticketOfAccount->getAccount, ticketOfAccount->maximumSizeOfAccount);
			pauseExecution();
			break;

		case 5:
			putchar('\n');
			displayAllAccountDetailRecords(ticketOfAccount->getAccount, ticketOfAccount->maximumSizeOfAccount);
			pauseExecution();
			break;

		case 6:
			putchar('\n');
			displayMessageForNewTicket(ticketOfAccount);
			break;

		case 7:
			putchar('\n');
			displayMessageForActiveTicket(ticketOfAccount);
			break;

		case 8:
			putchar('\n');
			displayMessageForAgentTicket(ticketOfAccount);
			break;

		case 9:
			putchar('\n');
			modificationOfAgentTicket(ticketOfAccount, accountInformation);
			break;

		case 10:
			putchar('\n');
			printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			yesOrNo = getCharOption("YN");
			printf("\n");

			if (yesOrNo == 'Y')
			{

				totalTickets2 = 0;
				for (i = 0; i < ticketOfAccount->maximumSizeOfTicket; i++)
				{

					if (ticketOfAccount->getTicket[i].statusOfTicket == INDICATOR_CLOSED_TICKET && ticketOfAccount->getTicket[i].uniqueNumber != 0)
					{

						totalTickets2++;
						closedTicketsArchive(&ticketOfAccount->getTicket[i]);
						allClosedTickets = allClosedTickets + totalTickets2;
						totalClosedMessages = totalClosedMessages + ticketOfAccount->getTicket[i].messageCount;

						ticketOfAccount->getTicket[i].uniqueNumber = 0;
						ticketOfAccount->getTicket[i].accountNumOfCustomer = 0;

					}
				}
				printf("*** %d tickets archived ***\n\n", totalTickets2);
				pauseExecution();

			}
			break;

		case 11:
			putchar('\n');
			printf("There are %d account(s) currently archived.\n\n", removedAccountCount);
			pauseExecution();
			break;

		case 12:
			putchar('\n');
			printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n", allRemovedTickets + totalTickets2, totalClosedMessages + allRemovedMessages);
			pauseExecution();
			break;

		case 0:
			putchar('\n');
			printf("Saving session modifications...\n");
			totalNumberOfAccounts = saveCurrentUpdatedAccounts(ticketOfAccount->getAccount, ticketOfAccount->maximumSizeOfAccount);
			printf("   %d account saved.\n", totalNumberOfAccounts);
			totalNumberOfTickets = currentTicketsSaving(ticketOfAccount->getTicket, ticketOfAccount->maximumSizeOfTicket);
			printf("   %d tickets saved.\n", totalNumberOfTickets);

			printf("### LOGGED OUT ###\n\n");
			record = 0;
			break;
		}

	} while (record);

}

// function to display the summary of all the valid account records(if number is greater than 0)

void displayAllAccountSummaryRecords(struct Account dataOfAccount[], int maximumElements)
{
	int i;

	displayAccountSummaryHeader();

	for (i = 0; i < maximumElements; i++)
	{
		if (dataOfAccount[i].customerAccountNumber != 0)
		{

			displayAccountSummaryRecord(&dataOfAccount[i]);
		}
	}

	putchar('\n');

}

// function to display detailed view of all and valid account record( if number is greater than 0)
void displayAllAccountDetailRecords(struct Account dataOfAccount[], int maximumElements)
{
	int i;
	displayAccountDetailHeader();

	for (i = 0; i < maximumElements; i++)
	{
		if (dataOfAccount[i].customerAccountNumber != 0)
		{
			displayAccountDetailRecord(&dataOfAccount[i]);
		}

	}

	putchar('\n');

}

// function to check the user login name and password

int userLoginAndPasswordChecking(const struct Account* dataOfAccount, int maximumElements)
{

	int limitRemain = LIMIT_RAMAIN;
	int indexNumber = 0, accountNumber = 0, passwordChecking = 0, loginChecking = 0, info = 1;
	char enterLogin[500] = "0";
	char enterPassword[500] = "0";

	while (info)
	{
		printf("Enter the account#: ");
		accountNumber = getPositiveInteger();

		indexNumber = findAccountIndexByAcctNum(accountNumber, dataOfAccount, maximumElements, DONOT_PROMPT);

		printf("User Login    : ");
		getCString(enterLogin, 1, 500);
		loginChecking = strcmp(enterLogin, dataOfAccount[indexNumber].login.loginNameOfUser);

		printf("Password      : ");
		getCString(enterPassword, 1, 500);

		passwordChecking = strcmp(enterPassword, dataOfAccount[indexNumber].login.passwordOfUser);

		if (loginChecking == 0 && passwordChecking == 0)
		{

			printf("\n");
			info = 0;
		}
		else
		{
			limitRemain--;
			printf("INVALID user login/password combination! [attempts remaining:%d]\n\n", limitRemain);
		}

		if (limitRemain == 0)
		{

			indexNumber = -1;
			printf("ERROR:  Login failed!\n\n");
			pauseExecution();
			info = 0;
		}

	} 

	return indexNumber;
}


