
#define _CRT_SECURE_NO_WARNINGS

// System Library
#include<stdio.h>
#include<ctype.h>

// User Defined Library
#include "commonHelpers.h"
#include "account.h"


// function to display: Account Data: New Record

void getAccount(struct Account* dataOfAccount)
{
	printf("New Account Data (Account#:%d)\n", dataOfAccount->customerAccountNumber);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	dataOfAccount->typeOfAccount = getCharOption("AC");
	putchar('\n');
}

// function to display: User login data input

void getUserLogin(struct Account* dataOfAccount)
{

	printf("User Login Data Input\n");

	printf("----------------------------------------\n");

	spacesInUserLogin(&dataOfAccount->login);
	printf("Enter the display name (%d chars max): ", LENGTH_OF_CUSTOMER_NAME);
	getCString(dataOfAccount->login.nameOfCustomer, MINIMUM_CHARACTERS, LENGTH_OF_CUSTOMER_NAME);

	strengthOfPassword(&dataOfAccount->login);
	putchar('\n');

}

// function to display: Demographic Data Input

void getDemographic(struct Account* dataOfAccount)
{

	int  minimumYear, maximumYear, getRunningYear;
	
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	getRunningYear = currentYear();
	minimumYear = getRunningYear - 110;
	maximumYear = getRunningYear - 18;

	printf("Enter birth year (current age must be between %d and %d): ", MINIMUM_AGE, MAXIMUM_AGE);
	dataOfAccount->demo.customerBirthYear = getIntFromRange(minimumYear, maximumYear);
	printf("Enter the household Income: $");
	dataOfAccount->demo.totalHouseholdIncome = getPositiveDouble();
	printf("Enter the country (%d chars max.): ", LENGTH_OF_COUNTRY_NAME);
	getCString(dataOfAccount->demo.customerCountry, MINIMUM_CHARACTERS, LENGTH_OF_COUNTRY_NAME);

	countryWithUpperCase(&dataOfAccount->demo);
	putchar('\n');
}

// function to display account's update menu options until users want to exit

void updateAccount(struct Account* dataOfAccount)
{

	int optionUpdation, minimum = 0, maximum = 3, record = 1; 

	do
	{
		printf("Account: %d - Update Options\n", dataOfAccount->customerAccountNumber);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", dataOfAccount->typeOfAccount);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		optionUpdation = getIntFromRange(minimum, maximum);
		putchar('\n');

		switch (optionUpdation)
		{

		case 1:
			printf("Enter the account type (A=Agent | C=Customer): ");
			dataOfAccount->typeOfAccount = getCharOption("AC");
			break;

		case 2:
			updateUserLogin(&dataOfAccount->login);
			break;

		case 3:
			updateDemographic(&dataOfAccount->demo);
			break;

		case 0:
			record = 0;
			break;
		}

	} while (record);
}

// function to display user login update menu until want to exit

void updateUserLogin(struct UserLogin* loginOfUser)
{

	int optionUpdation, record = 1, minimum = 0, maximum = 2;

	while (record)
	{
		printf("User Login: %s - Update Options\n", loginOfUser->loginNameOfUser);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", loginOfUser->nameOfCustomer);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");

		optionUpdation = getIntFromRange(minimum, maximum);
		putchar('\n');

		switch (optionUpdation)
		{

		case 1:
			printf("Enter the display name (%d chars max): ", LENGTH_OF_CUSTOMER_NAME);
			getCString(loginOfUser->nameOfCustomer, MINIMUM_CHARACTERS, LENGTH_OF_CUSTOMER_NAME);
			putchar('\n');
			break;

		case 2:
			strengthOfPassword(loginOfUser);
			printf("\n");
			break;

		case 0:
			record = 0;
			break;
		}

	} 

}

// function to display: menu with the option to modify some members of Demographic

void updateDemographic(struct Demographic* memberdemo)
{

	int optionUpdation, record = 1, minimum = 0, maximum = 2;

	do
	{
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", memberdemo->totalHouseholdIncome);
		printf("2) Country (current value: %s)\n", memberdemo->customerCountry);
		printf("0) Done\n");
		printf("Selection: ");

		optionUpdation = getIntFromRange(minimum, maximum);
		putchar('\n');

		switch (optionUpdation)
		{
		case 1:
			printf("Enter the household Income: $");
			memberdemo->totalHouseholdIncome = getPositiveDouble();
			putchar('\n');
			break;

		case 2:
			printf("Enter the country (%d chars max.): ", LENGTH_OF_COUNTRY_NAME);
			getCString(memberdemo->customerCountry, MINIMUM_CHARACTERS, LENGTH_OF_COUNTRY_NAME);
			countryWithUpperCase(memberdemo);
			putchar('\n');
			break;

		case 0:
        	record = 0;
			break;
		}

	} while (record);

}

// function to chnage the country name from lowercase to uppercase

void countryWithUpperCase(struct Demographic* countryDemo)
{

	int j = 0;

	while (countryDemo->customerCountry[j] != '\0')
	{

		if (islower(countryDemo->customerCountry[j]))
		{
			countryDemo->customerCountry[j] = toupper(countryDemo->customerCountry[j]);
		}
		j++;
	}

}

// function to check the stringth of the password

void strengthOfPassword(struct UserLogin* loginOfUser)
{
	int digitCount, upperCount, lowerCount, countOfSymbol;
	int i = 0, j = 0, record = 1;
	char getSymbols[SYMBOLSREPRESENT + 1] = "!@#$%^&*";

	while (record)
	{

		upperCount = 0;
		lowerCount = 0;
		digitCount = 0;
		countOfSymbol = 0;

		printf("Enter the password (must be %d chars in length): ", LENGTH_OF_PASSWORD);
		getCString(loginOfUser->passwordOfUser, LENGTH_OF_PASSWORD, LENGTH_OF_PASSWORD);

		i = 0;
		do
		{
			if (isdigit(loginOfUser->passwordOfUser[i]))
			{
				digitCount++;
			}

			if (isupper(loginOfUser->passwordOfUser[i]))
			{
				upperCount++;
			}

			if (islower(loginOfUser->passwordOfUser[i]))
			{
				lowerCount++;
			}

			if (!islower(loginOfUser->passwordOfUser[i]) && !isupper(loginOfUser->passwordOfUser[i]) && !isdigit(loginOfUser->passwordOfUser[i]))
			{

				for (j = 0; j < SYMBOLSREPRESENT; j++)
				{
					if (loginOfUser->passwordOfUser[i] == getSymbols[j])
					{

						countOfSymbol++;
					}

				}
			}

			i++;
		} while (loginOfUser->passwordOfUser[i] != '\0');

		if (digitCount == 2 && lowerCount == 2 && upperCount == 2 && countOfSymbol == 2)
		{
			record = 0;
		}

		else
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
		}

	} 
}

// function to check that is there whitespaces or not in user login name

void spacesInUserLogin(struct UserLogin* loginOfUser)
{
	int info = 0, record = 1, i = 0;

	do
	{

		info = 0;
		printf("Enter user login (%d chars max): ", LENGTH_OF_USER_NAME);
		getCString(loginOfUser->loginNameOfUser, MINIMUM_CHARACTERS, LENGTH_OF_USER_NAME);
		do
		{

			if (isspace(loginOfUser->loginNameOfUser[i]))
			{
				info++;
			}

			i++;
		} while (loginOfUser->loginNameOfUser[i] != '\0');

		if (info > 0)
		{

			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
		}
		else
		{

			record = 0;
		}

	} while (record);
}

// function to load the data of accounts from accounts.txt

int loadAccounts(struct Account dataOfAccount[], int maximumElements)
{

	int totalAccounts = 0;
	char character;

	FILE* fp = fopen(ACCOUNTSFILE, "r");

	if (fp != NULL)
	{
		while (totalAccounts < maximumElements && fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]%c",
			&dataOfAccount[totalAccounts].customerAccountNumber,
			&dataOfAccount[totalAccounts].typeOfAccount,
			dataOfAccount[totalAccounts].login.nameOfCustomer,
			dataOfAccount[totalAccounts].login.loginNameOfUser,
			dataOfAccount[totalAccounts].login.passwordOfUser,
			&dataOfAccount[totalAccounts].demo.customerBirthYear,
			&dataOfAccount[totalAccounts].demo.totalHouseholdIncome,
			dataOfAccount[totalAccounts].demo.customerCountry, &character) == 9)
		{

			if (character != '\n')
			{

				while (fgetc(fp) != '\n');
			}

			totalAccounts++;
		}
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}

	else
	{

		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}

	return totalAccounts;
}

// function to remove archive accounts in accounts_arc.txt

int removeAccountArchive(const struct Account* dataOfAccount)
{
	int score = 0;
	FILE* fp = fopen(ACCOUNTSARCFILE, "a");

	if (fp != NULL)
	{

		score = fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", dataOfAccount->customerAccountNumber,
			dataOfAccount->typeOfAccount,
			dataOfAccount->login.nameOfCustomer,
			dataOfAccount->login.loginNameOfUser,
			dataOfAccount->login.passwordOfUser,
			dataOfAccount->demo.customerBirthYear,
			dataOfAccount->demo.totalHouseholdIncome,
			dataOfAccount->demo.customerCountry);

		fflush(fp);
		fclose(fp);
		fp = NULL;
	}

	else
	{

		puts("ERROR: UNABLE TO ACCESS FILE!!!\n");
	}
	return score > 0 ? 1 : 0;
}

// funtion to save in accounts.txt about current updated accounts

int saveCurrentUpdatedAccounts(const struct Account dataOfAccount[], int maximumElements)
{

	int i = 0, totalAccounts = 0;
	FILE* fp = fopen(ACCOUNTSFILE, "w");

	if (fp != NULL)
	{

		for (i = 0; i < maximumElements; i++)
		{

			if (dataOfAccount[i].customerAccountNumber > 0)
			{

				fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", dataOfAccount[i].customerAccountNumber,
					dataOfAccount[i].typeOfAccount,
					dataOfAccount[i].login.nameOfCustomer,
					dataOfAccount[i].login.loginNameOfUser,
					dataOfAccount[i].login.passwordOfUser,
					dataOfAccount[i].demo.customerBirthYear,
					dataOfAccount[i].demo.totalHouseholdIncome,
					dataOfAccount[i].demo.customerCountry);

				totalAccounts++;
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

	return totalAccounts;
}
