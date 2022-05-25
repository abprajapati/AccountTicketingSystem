
#define _CRT_SECURE_NO_WARNINGS

  // System Library
#include<stdio.h>

  //User Library
#include "accountTicketingUI.h"

// function for searching the array got in argument 2 about a match on a desired ticket number

int ticketIndexByTickNumberFinding(int ticketNumber, const struct Ticket dataOfTicket[], int maximumElements, int promptTicketNumber)
{

	int foundIndex = -1, i = 0;
	if (promptTicketNumber)
	{

		printf("Enter ticket number: ");
		ticketNumber = getPositiveInteger();
		putchar('\n');
	}

	for (i = 0, foundIndex = -1; foundIndex < 0 && i < maximumElements; i++)
	{
		if (ticketNumber == dataOfTicket[i].uniqueNumber)
		{

			foundIndex = i;
		}
	}

	return foundIndex;
}

// function to romove tickets and the account associated with that ticket

int ticketsRemoving(const struct AccountTicketingData* ticketOfAccount, struct Account* accountInformation, int* allRemovedTickets)
{
	int info = 0, i = 0;

	for (i = 0; i < ticketOfAccount->maximumSizeOfTicket; i++)
	{
		if (ticketOfAccount->getTicket[i].accountNumOfCustomer == accountInformation->customerAccountNumber)
		{

			if (ticketOfAccount->getTicket[i].statusOfTicket == INDICATOR_ACTIVE_TICKET)
			{
				ticketOfAccount->getTicket[i].uniqueNumber = 0;
				ticketOfAccount->getTicket[i].accountNumOfCustomer = 0;
				
			}

			else
			{
				*allRemovedTickets = ticketOfAccount->getTicket[i].messageCount;
				info = removedClosedTicketsArchive(&ticketOfAccount->getTicket[i]);
				ticketOfAccount->getTicket[i].uniqueNumber = 0;
				ticketOfAccount->getTicket[i].accountNumOfCustomer = 0;
				
			}

		}

	}
	return info;

}

// function to generate or create new tickets for customer

void forNewTicketCreation(struct Ticket* ticketForNewCustomer, const struct Account* accountInformation, int maximumElements)
{

	int  i = 0, minimum = 1, ticketIndex = 0, maximumTicketNumber = 0;

	ticketIndex = ticketIndexByTickNumberFinding(0, ticketForNewCustomer, maximumElements, DONOT_PROMPT);

	if (ticketIndex < 0)
	{

		printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
		pauseExecution();
	}

	else
	{

		for (i = 0; i < ticketIndex; i++)
		{

			if (ticketForNewCustomer[i].uniqueNumber > maximumTicketNumber)
			{

				maximumTicketNumber = ticketForNewCustomer[i].uniqueNumber;
			}
		}

		ticketForNewCustomer[ticketIndex].uniqueNumber = maximumTicketNumber + 1;
		ticketForNewCustomer[ticketIndex].accountNumOfCustomer = accountInformation->customerAccountNumber;
		ticketForNewCustomer[ticketIndex].messageCount = NUMBER_OF_NEW_MASSAGE;
		ticketForNewCustomer[ticketIndex].statusOfTicket = INDICATOR_ACTIVE_TICKET;
		ticketForNewCustomer[ticketIndex].detailsOfMassage->authorAccountType = accountInformation->typeOfAccount;


		printf("New Ticket (Ticket#:%06d)\n", ticketForNewCustomer[ticketIndex].uniqueNumber);
		printf("----------------------------------------\n");
		printf("Enter the ticket SUBJECT (%d chars. maximum): ", SIZE_OF_SUBJECT);

		getCString(ticketForNewCustomer[ticketIndex].lineOfSubject, minimum, SIZE_OF_SUBJECT);
		putchar('\n');
		printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", SIZE_OF_MASSAGE);
		getCString(ticketForNewCustomer[ticketIndex].detailsOfMassage[ticketForNewCustomer[ticketIndex].messageCount - 1].detailOfMassage, minimum, SIZE_OF_MASSAGE);

		for (i = 0; i < LENGTH_OF_DISPLAY_NAME; i++)
		{

			ticketForNewCustomer[ticketIndex].detailsOfMassage[ticketForNewCustomer[ticketIndex].messageCount - 1].nameDisplay[i] = accountInformation->login.nameOfCustomer[i];
		}

		putchar('\n');
		printf("*** New ticket created! ***\n\n");
		pauseExecution();

	}
}

// function to check the ticket number and cater the index

void customerTicketModification(struct Ticket* ticketForNewCustomer, struct Account* accountInformation, int maximumElements)
{

	int ticketIndex = 0, ticketNumber = 0;

	do
	{
		ticketIndex = ticketIndexByTickNumberFinding(ticketNumber, ticketForNewCustomer, maximumElements, PROMPT);

	} while (ticketIndex == -1);

	if (ticketForNewCustomer[ticketIndex].accountNumOfCustomer != accountInformation->customerAccountNumber)
	{
		printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
		pauseExecution();
		
	}

	else
	{
		if (ticketForNewCustomer[ticketIndex].statusOfTicket == 1)
		{

			modifyCustomerTicketMenu(&ticketForNewCustomer[ticketIndex], accountInformation);
		}
		else
		{
			printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
			pauseExecution();
		}
	}
}

// function to cater menu for modifying customer ticket

void modifyCustomerTicketMenu(struct Ticket* dataOfTicket, struct Account* accountInformation)
{

	int record = 1, optionModification = 0;
	int minimum = 0, maximum = 3;
	char ticketClose = 0, messageLeave = 0;
	int i = 0;

	while (record)
	{

		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", dataOfTicket->uniqueNumber);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", dataOfTicket->statusOfTicket == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", dataOfTicket->lineOfSubject);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");

		optionModification = getIntFromRange(minimum, maximum);
		putchar('\n');

		switch (optionModification)
		{

		case 1:
			printf("Enter the revised ticket SUBJECT (%d chars. maximum): ", SIZE_OF_SUBJECT);
			getCString(dataOfTicket->lineOfSubject, minimum, SIZE_OF_SUBJECT);
			putchar('\n');
			break;

		case 2:
			if (dataOfTicket->messageCount >= MESSAGES_COUNT)
			{

				printf("ERROR: Message limit has been reached, call ITS Support!\n");
			}
			else
			{

				printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", SIZE_OF_MASSAGE);
				dataOfTicket->messageCount = dataOfTicket->messageCount + 1;
				getCString(dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].detailOfMassage, minimum, SIZE_OF_MASSAGE);
				for (i = 0; i < LENGTH_OF_DISPLAY_NAME; i++)
				{

					dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].nameDisplay[i] = accountInformation->login.nameOfCustomer[i];
				}

			}

			putchar('\n');

			break;

		case 3:

			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			ticketClose = getCharOption("YN");

			if (ticketClose == 'Y')
			{
				dataOfTicket->statusOfTicket = 0;
				
			}
			else
			{
				dataOfTicket->statusOfTicket = 1;
			}

			putchar('\n');

			if (dataOfTicket->messageCount < MESSAGES_COUNT)
			{

				printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
				messageLeave = getCharOption("YN");
				putchar('\n');

				if (messageLeave == 'Y')
				{
					printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", SIZE_OF_MASSAGE);
					dataOfTicket->messageCount = dataOfTicket->messageCount + 1;
					getCString(dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].detailOfMassage, minimum, SIZE_OF_MASSAGE);

					for (i = 0; i < LENGTH_OF_DISPLAY_NAME; i++)
					{

						dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].nameDisplay[i] = accountInformation->login.nameOfCustomer[i];
					}
					putchar('\n');
				}
			}

			if (ticketClose == 'Y')
			{

				printf("*** Ticket closed! ***\n\n");
				pauseExecution();
				record = 0;

			}
			break;

		case 0:
			pauseExecution();
			record = 0;
			break;

		}

	} 
}

// function to display closed agent massages

void displayMessageForAgentTicket(const struct AccountTicketingData* ticketNewAgent)
{

	int i = 0, j = 0, record = 1, info = 1, count = 0, ticketNumber;

	do
	{

		info = 1;
		displayHeaderOfTicket();

		for (i = 0; i < ticketNewAgent->maximumSizeOfTicket; i++)
		{

			if (ticketNewAgent->getTicket[i].statusOfTicket == INDICATOR_CLOSED_TICKET && ticketNewAgent->getTicket[i].uniqueNumber != 0)
			{
				printf("%06d %5d %-15s %-6s %-30s %5d\n", ticketNewAgent->getTicket[i].uniqueNumber, ticketNewAgent->getTicket[i].accountNumOfCustomer, ticketNewAgent->getTicket[i].detailsOfMassage->nameDisplay, ticketNewAgent->getTicket[i].statusOfTicket == 1 ? "ACTIVE" : "CLOSED", ticketNewAgent->getTicket[i].lineOfSubject, ticketNewAgent->getTicket[i].messageCount);
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
			for (i = 0; i < ticketNewAgent->maximumSizeOfTicket && info; i++)
			{

				if (ticketNewAgent->getTicket[i].uniqueNumber == ticketNumber && ticketNewAgent->getTicket[i].uniqueNumber != 0)
				{

					printf("================================================================================\n");
					printf("%06d (%s) Re: %s\n", ticketNewAgent->getTicket[i].uniqueNumber, ticketNewAgent->getTicket[i].statusOfTicket == 1 ? "ACTIVE" : "CLOSED", ticketNewAgent->getTicket[i].lineOfSubject);
					printf("================================================================================\n");

					for (j = 0; j < ticketNewAgent->getTicket[i].messageCount; j++)
					{
						printf("%s (%s):\n", ticketNewAgent->getTicket[i].detailsOfMassage[j].authorAccountType == 'A' ? "AGENT" : "CUSTOMER", ticketNewAgent->getTicket[i].detailsOfMassage[j].nameDisplay);
						printf("   %s\n\n", ticketNewAgent->getTicket[i].detailsOfMassage[j].detailOfMassage);

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
	} while (record);
}

// function to check agent ticket number and cater index for that ticket number

void modificationOfAgentTicket(const struct AccountTicketingData* ticketNewAgent, struct Account* accountInformation)
{

	int ticketNum = 0, ticketIndex = 0;

	do
	{
		ticketIndex = ticketIndexByTickNumberFinding(ticketNum, ticketNewAgent->getTicket, ticketNewAgent->maximumSizeOfTicket, PROMPT);

	} while (ticketIndex == -1);

	modifyAgentTicketMenu(&ticketNewAgent->getTicket[ticketIndex], accountInformation);
}

// function to check agent ticket number and cater index for that ticket number

void modifyAgentTicketMenu(struct Ticket* dataOfTicket, struct Account* accountInformation)
{
	int modifyOption = 0, min = 0, max = 3, repeatLoop = 1;
	char leaveMessage = 0, closeTicket = 0, reopenTicket = 0;
	int i = 0;

	while (repeatLoop)
	{
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", dataOfTicket->uniqueNumber);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", dataOfTicket->statusOfTicket == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", dataOfTicket->lineOfSubject);
		printf("Acct#   : %d\n", dataOfTicket->accountNumOfCustomer);
		printf("%s: %s\n", dataOfTicket->detailsOfMassage->authorAccountType == 'A' ? "Agent" : "Customer", dataOfTicket->detailsOfMassage->nameDisplay);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");

		modifyOption = getIntFromRange(min, max);
		putchar('\n');

		switch (modifyOption)

		{

		case 1:
			if (dataOfTicket->statusOfTicket == 0)
			{
				printf("ERROR: Ticket is closed - new messages are not permitted.\n");
				
			}
			else
			{
				if (dataOfTicket->messageCount >= MESSAGES_COUNT)
				{
					printf("ERROR: Message limit has been reached, call ITS Support!\n");
				}
				else
				{
					printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", SIZE_OF_MASSAGE);
					dataOfTicket->messageCount = dataOfTicket->messageCount + 1;
					getCString(dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].detailOfMassage, min, SIZE_OF_MASSAGE);
					for (i = 0; i < LENGTH_OF_DISPLAY_NAME; i++)
					{

						dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].nameDisplay[i] = accountInformation->login.nameOfCustomer[i];
					}
					dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].authorAccountType = accountInformation->typeOfAccount;

				}
				
			}
			putchar('\n');
			break;

		case 2:

			if (dataOfTicket->statusOfTicket == 0)
			{
				printf("ERROR: Ticket is already closed!\n\n");
			}

			else
			{

				printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				closeTicket = getCharOption("YN");

				if (closeTicket == 'Y')
				{
					dataOfTicket->statusOfTicket = 0;
				}

				else
				{
					dataOfTicket->statusOfTicket = 1;
				}
				putchar('\n');

				if (dataOfTicket->messageCount < MESSAGES_COUNT)
				{

					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					leaveMessage = getCharOption("YN");
					putchar('\n');
					if (leaveMessage == 'Y')
					{


						printf("Enter the ticket message details (%d chars. maximum). Press the ENTER key to submit:\n", SIZE_OF_MASSAGE);
						dataOfTicket->messageCount = dataOfTicket->messageCount + 1;
						getCString(dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].detailOfMassage, min, SIZE_OF_MASSAGE);
						for (i = 0; i < LENGTH_OF_DISPLAY_NAME; i++)
						{
							dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].nameDisplay[i] = accountInformation->login.nameOfCustomer[i];
						}

						dataOfTicket->detailsOfMassage[dataOfTicket->messageCount - 1].authorAccountType = accountInformation->typeOfAccount;
						putchar('\n');
					}
				}

				if (closeTicket == 'Y')
				{

					printf("*** Ticket closed! ***\n\n");
				}
			}
			break;

		case 3:
			if (dataOfTicket->statusOfTicket == 0)
			{
				printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				reopenTicket = getCharOption("YN");

				if (reopenTicket == 'Y')
				{

					dataOfTicket->statusOfTicket = 1;
					printf("\n*** Ticket re-opened! ***");
					printf("\n\n");
				}
				else
				{

					dataOfTicket->statusOfTicket = 0;
					printf("\n");
				}
				
			}
			else
			{
				printf("ERROR: Ticket is already active!\n\n");
			}

			break;

		case 0:
			repeatLoop = 0;
			break;
		}

	} 
}

// function to load data of the tickets from tickets.txt

int loadTickets(struct Ticket dataOfTicket[], int maximumElements)
{
	int countField, totalTickets = 0;
	int i = 0;

	FILE* fp = fopen(TICKETSFILE, "r");

	if (fp != NULL)
	{

		do
		{
			countField = fscanf(fp, "%d|%d|%d|%30[^|]|%d|",
				&dataOfTicket[totalTickets].uniqueNumber,
				&dataOfTicket[totalTickets].accountNumOfCustomer,
				&dataOfTicket[totalTickets].statusOfTicket,
				dataOfTicket[totalTickets].lineOfSubject,
				&dataOfTicket[totalTickets].messageCount);

			if (countField == 5)
			{

				if (dataOfTicket[totalTickets].uniqueNumber > 0)
				{

					for (i = 0, countField = 3; countField == 3 && i < dataOfTicket[totalTickets].messageCount; i++)
					{
						countField = fscanf(fp, "%c|%30[^|]|%150[^|]|", &dataOfTicket[totalTickets].detailsOfMassage[i].authorAccountType,
							dataOfTicket[totalTickets].detailsOfMassage[i].nameDisplay,
							dataOfTicket[totalTickets].detailsOfMassage[i].detailOfMassage);
					}
				}

				totalTickets++;
			}
		} while (!feof(fp) && totalTickets < maximumElements);

		fflush(fp);
		fclose(fp);
		fp = NULL;
	}

	else
	{
		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}
	return totalTickets;
}

// function to save the details of the current updated tickets in tickets.txt file

int currentTicketsSaving(const struct Ticket dataOfTicket[], int maximumElements)
{
	int i = 0, j = 0, totalTickets = 0;
	FILE* fp = fopen(TICKETSFILE, "w");

	if (fp != NULL)
	{
		for (i = 0; i < maximumElements; i++)
		{

			if (dataOfTicket[i].uniqueNumber > 0)
			{

				fprintf(fp, "%d|%d|%d|%s|%d|", dataOfTicket[i].uniqueNumber, dataOfTicket[i].accountNumOfCustomer, dataOfTicket[i].statusOfTicket, dataOfTicket[i].lineOfSubject, dataOfTicket[i].messageCount);

				if (dataOfTicket[i].uniqueNumber > 0)
				{

					for (j = 0; j < dataOfTicket[i].messageCount; j++)
					{

						fprintf(fp, "%c|%s|%s|", dataOfTicket[i].detailsOfMassage[j].authorAccountType,
							dataOfTicket[i].detailsOfMassage[j].nameDisplay,
							dataOfTicket[i].detailsOfMassage[j].detailOfMassage);

						if (j == dataOfTicket[i].messageCount - 1)
						{

							fprintf(fp, "\n");
						}

					}
				}

				totalTickets++;
			}
		}

		fflush(fp);
		fclose(fp);
		fp = NULL;
	}

	else
	{

		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}

	return totalTickets;
}

// function to closed removed ticket archive in tickets_arc.txt

int removedClosedTicketsArchive(const struct Ticket* dataOfTicket)
{
	int i = 0, info = 0;
	FILE* fp = fopen(TICKETSARCFILE, "a");

	if (fp != NULL)
	{
		fprintf(fp, "%d|%d|%d|%s|%d|", dataOfTicket->uniqueNumber, dataOfTicket->accountNumOfCustomer, dataOfTicket->statusOfTicket, dataOfTicket->lineOfSubject, dataOfTicket->messageCount);

		if (dataOfTicket->uniqueNumber > 0)
		{
			for (i = 0; i < dataOfTicket->messageCount; i++)
			{

				info = fprintf(fp, "%c|%s|%s|", dataOfTicket->detailsOfMassage[i].authorAccountType,
					dataOfTicket->detailsOfMassage[i].nameDisplay,
					dataOfTicket->detailsOfMassage[i].detailOfMassage);

				if (i == dataOfTicket->messageCount - 1)
				{

					fprintf(fp, "\n");
				}
			}

		}

		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	else
	{

		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}
	return info > 0 ? 1 : 0;
}

// function to get closed tickets archive in tickets_arc.txt

void closedTicketsArchive(const struct Ticket* dataOfTicket)
{
	int i = 0;
	FILE* fp = fopen(TICKETSARCFILE, "a");

	if (fp != NULL)
	{

		fprintf(fp, "%d|%d|%d|%s|%d|", dataOfTicket->uniqueNumber, dataOfTicket->accountNumOfCustomer, dataOfTicket->statusOfTicket, dataOfTicket->lineOfSubject, dataOfTicket->messageCount);

		if (dataOfTicket->uniqueNumber > 0)
		{

			for (i = 0; i < dataOfTicket->messageCount; i++)
			{

				fprintf(fp, "%c|%s|%s|", dataOfTicket->detailsOfMassage[i].authorAccountType,
					dataOfTicket->detailsOfMassage[i].nameDisplay,
					dataOfTicket->detailsOfMassage[i].detailOfMassage);

				if (i == dataOfTicket->messageCount - 1)
				{

					fprintf(fp, "\n");
				}
			}
		}

		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
	else
	{

		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}


}