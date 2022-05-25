#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_


int currentYear(void);

void clearStandardInputBuffer(void);

// function to make sure that entered value and returned value is of type integer(int)

int getInteger(void);

// function to make sure that entered value and returned value is positive and integer type(int)

int getPositiveInteger(void);

// function to make sure that entered and returned value is of floating-double (double) type 

double getDouble(void);

//function to make sure that entered and returned value is positive and of floating-double (double) type

double getPositiveDouble(void);

// function to make sure that entered and returned value is within the range

int getIntFromRange(int intlowerBound, int intupperBound);

// function to make sure that single character is entered and returned and that is also from list of valid characters

char getCharOption(const char stringValidation[]);

// function to make sure that C string value is entered which contains number of characters within the specified range.

void getCString(char pointerChar[], int minimumCharacters, int maximumCharacters);


#endif
