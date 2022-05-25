
#define _CRT_SECURE_NO_WARNINGS

//  System Libraries

#include<stdio.h>
#include <time.h>

// User Library

#include "commonHelpers.h"


int currentYear(void)
{
	time_t currentTime = time(NULL);

	return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // body of while is empty because we want to do nothing 
	}

}

// function to make sure that entered value and returned value is of type integer(int)

int getInteger(void)
{

	int intNumber = 0;
	char getNewLine = 0;

	do
	{

		scanf("%d%c", &intNumber, &getNewLine);

		if (getNewLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (getNewLine != '\n');

	return intNumber;
}

// function to make sure that entered value and returned value is positive and integer type (int)

int getPositiveInteger(void)
{
	int info = 1, posInteger = 0;


	while (info)
	{

		posInteger = getInteger();

		if (posInteger <= 0)
		{
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
		else
		{
			info = 0;
		}

	}
	return posInteger;
}

// function to make sure that entered and returned value is of floating-double (double) type

double getDouble(void)
{

	double doubleNumber = 0.0;
	char getNewLine = 0;

	do
	{
		scanf("%lf%c", &doubleNumber, &getNewLine);

		if (getNewLine != '\n')
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}

	} while (getNewLine != '\n');

	return doubleNumber;
}

//function to make sure that entered and returned value is positive and of floating-double (double) type  

double getPositiveDouble(void)
{
	double doublePositiveNum = 0.0;
	int info = 1;

	do
	{
		doublePositiveNum = getDouble();

		if (doublePositiveNum <= 0)
		{

			printf("ERROR: Value must be a positive double floating-point number: ");
		}
		else
		{

			info = 0;
		}

	} while (info);

	return doublePositiveNum;
}

// function to make sure that entered and returned value is within the range

int getIntFromRange(int intlowerBound, int intupperBound)
{
	int  info = 1, integerRange = 0;

	do
	{
		integerRange = getInteger();

		if (integerRange >= intlowerBound && integerRange <= intupperBound)
		{

			info = 0;
		}
		else
		{

			printf("ERROR: Value must be between %d and %d inclusive: ", intlowerBound, intupperBound);

		}

	} while (info);

	return integerRange;
}

// function to make sure that single character is entered and returned and that is also from list of valid characters

char getCharOption(const char stringValidation[])
{
	char getCharacter = 0;
	int i = 0, record = 0, info = 1;
	char getCharacterOne = 0;

	for (i = 0; stringValidation[i] != '\0'; i++)
	{

		record++;
	}

	while (info)
	{
		scanf("%c%c", &getCharacter, &getCharacterOne);


		if (getCharacterOne == '\n')
		{

			for (i = 0; i < record && info; i++)
			{

				if (getCharacter == stringValidation[i])
				{

					info = 0;
				}


			}

			if (info)
			{
				printf("ERROR: Character must be one of [%s]: ", stringValidation);
			}
		}
		else
		{
			printf("ERROR: Character must be one of [%s]: ", stringValidation);
			clearStandardInputBuffer();
		}

	}


	return getCharacter;
}

// function to make sure that C string value is entered which contains number of characters within the specified range.

void getCString(char pointerChar[], int minimumCharacters, int maximumCharacters)
{
	int i = 0, j = 0;
	int info = 1, record = 0;
	char getCString[500];

	do
	{

		scanf("%500[^\n]", getCString);
		clearStandardInputBuffer();
		record = 0;

		for (i = 0; getCString[i] != '\0'; i++)
		{
			record++;
		}

		if (record < minimumCharacters && (minimumCharacters != maximumCharacters))
		{

			printf("ERROR: String length must be between %d and %d chars: ", minimumCharacters, maximumCharacters);
		}
		else if (record > maximumCharacters && (minimumCharacters != maximumCharacters))
		{
			printf("ERROR: String length must be no more than %d chars: ", maximumCharacters);
		}
		else if ((record <minimumCharacters || record>maximumCharacters) && minimumCharacters == maximumCharacters)
		{

			printf("ERROR: String length must be exactly %d chars: ", minimumCharacters);

		}

		else
		{
			for (j = 0; j < record + 1; j++)
			{
				pointerChar[j] = getCString[j];
			}
			info = 0;
		}

	} while (info);


}