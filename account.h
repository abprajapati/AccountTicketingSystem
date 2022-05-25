#pragma once


#ifndef ACCOUNT_H_
#define ACCOUNT_H_


#define ACCOUNTSFILE "accounts.txt"
#define ACCOUNTSARCFILE "accounts_arc.txt"



// declaring MACROS

#define LENGTH_OF_COUNTRY_NAME 30
#define LENGTH_OF_CUSTOMER_NAME 30
#define LENGTH_OF_USER_NAME 10
#define LENGTH_OF_PASSWORD 8
#define MINIMUM_CHARACTERS 1
#define MINIMUM_AGE 18
#define MAXIMUM_AGE 110
#define SYMBOLSREPRESENT 8

// declaring structures

struct Demographic
{
	int customerBirthYear;
	double totalHouseholdIncome;
	char customerCountry[LENGTH_OF_COUNTRY_NAME + 1];
};

struct UserLogin
{
	char nameOfCustomer[LENGTH_OF_CUSTOMER_NAME + 1];
	char loginNameOfUser[LENGTH_OF_USER_NAME + 1];
	char passwordOfUser[LENGTH_OF_PASSWORD + 1];
};

struct Account
{
	int customerAccountNumber;
	char typeOfAccount;
	struct UserLogin login;
	struct Demographic demo;

};

#endif 

// declaring functions

// function to display: Account Data: New Record

void getAccount(struct Account* dataOfAccount);

// function to display: User login data input

void getUserLogin(struct Account* dataOfAccount);

// function to display: Demographic Data Input

void getDemographic(struct Account* dataOfAccount);

// function to display account's update menu options until users want to exit

void updateAccount(struct Account* dataOfAccount);

// function to display user login update menu until want to exit

void updateUserLogin(struct UserLogin* loginOfUser);

// function to display: menu with the option to modify some members of Demographic

void updateDemographic(struct Demographic* memberdemo);

// function to chnage the country name from lowercase to uppercase

void countryWithUpperCase(struct Demographic* countryDemo);

// function to check the stringth of the password

void strengthOfPassword(struct UserLogin* loginOfUser);

// function to check that is there whitespaces or not in user login name

void spacesInUserLogin(struct UserLogin* loginOfUser);

// function to load the data of accounts from accounts.txt

int loadAccounts(struct Account dataOfAccount[], int maximumElements);

// function to remove archive accounts in accounts_arc.txt

int removeAccountArchive(const struct Account* dataOfAccount);

// funtion to save in accounts.txt about current updated accounts

int saveCurrentUpdatedAccounts(const struct Account dataOfAccount[], int maximumElements);



