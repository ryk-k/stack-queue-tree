/*
Assignment 3 PART A - Stacks
Passengers on a Train
Authors: Usma Qadri #991395853 and Krista Ryk #991406369
Date Created: March 12 2022
Date Updated: March 28 2022

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure Definition with integer data and a self-referential pointer
struct passenger
{
	int seatId;
	char passengerName[30];
	float ticketPrice;
	struct passenger *nextPtr;
};

// Structure renaming
typedef struct passenger Passenger;
typedef struct passenger *PassengerPtr;

/*.......Function Prototypes ....*/
// Operations on the stack
PassengerPtr push(PassengerPtr topPtr, int id, char name[30], double price);
PassengerPtr pop(PassengerPtr topPtr);
int isEmpty(PassengerPtr topPtr);
void topOfStack(PassengerPtr topPtr);
void printStack(PassengerPtr topPtr);
void bottomOfStack(PassengerPtr topPtr);
void stackInstructions(void);
int generateStackId();

PassengerPtr push(PassengerPtr topPtr, int id, char name[30], double price)
{
	PassengerPtr newPtr;				// Define pointer for newNode
	newPtr = malloc(sizeof(Passenger)); // Create Space for the newNode

	if (newPtr != NULL) // (check if node was created )
	{
		// Push newNode onto Stack
		newPtr->seatId = id;
		strcpy(newPtr->passengerName, name);
		newPtr->ticketPrice = price;
		newPtr->nextPtr = topPtr;
		topPtr = newPtr;
	}
	else
	{
		puts("Memory Failure");
	}
	return topPtr; // return with the topPtr
}

PassengerPtr pop(PassengerPtr topPtr)
{
	// Define Pointer to be used to isolate node at the topOfStack
	PassengerPtr tempPtr;
	tempPtr = topPtr;																																 // isolate the top Node
	printf("\nPassenger Being Popped: \t ID: %d, Name: %s, Ticket Price: $%.2lf.\n", tempPtr->seatId, tempPtr->passengerName, tempPtr->ticketPrice); // inform the user
	topPtr = topPtr->nextPtr;																														 // update topPtr
	free(tempPtr);																																	 // deallocate memory
	return topPtr;																																	 // return with the topPtr
}

int isEmpty(PassengerPtr topPtr)
{
	return (topPtr == NULL); // if this is true, that is, a value of 1, empty stack
}

void topOfStack(PassengerPtr topPtr)
{

	printf("\nTop of Stack: \t ID: %d, Name: %s, Ticket Price: $%.2lf.\n", topPtr->seatId, topPtr->passengerName, topPtr->ticketPrice); // 	inform the user
}

void bottomOfStack(PassengerPtr topPtr)

{
	PassengerPtr previousPtr = NULL, currentPtr = topPtr;
	if (currentPtr == NULL)
	{
		printf("Empty\n");
	}
	else
	{
		while (currentPtr != NULL)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		printf("\nBottom of Stack: \t ID: %d, Name: %s, Ticket Price: $%.2lf.\n", previousPtr->seatId, previousPtr->passengerName, previousPtr->ticketPrice); // 	inform the user
	}
}

void printStack(PassengerPtr topPtr)
{
	PassengerPtr currentPtr = topPtr;
	if (currentPtr == NULL)
	{
		puts("Stack is empty... nothing to print");
	}
	else
	{
		puts("The Values in the stack are:");
		while (currentPtr != NULL)
		{
			printf("   -->   ID: %d, ", currentPtr->seatId);
			printf("Name: %s, ", currentPtr->passengerName);
			printf("Ticket Price: $%.2lf", currentPtr->ticketPrice);
			currentPtr = currentPtr->nextPtr;
		}
		puts("\n");
	}
}

int generateStackId()
{
	static int id = 1;
	return id++;
}

void stackInstructions(void)
{
	printf("Enter choice:\n1 Push a Passenger on to the Stack\n2 Pop a Passenger off the Stack\n3 Top of Stack\n4 Bottom of stack\n5 End of Program\n");
}
