/*
Assignment 3 PART B - Queue Operations
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
struct passengerQueue
{
    int seatId;
    char passengerName[30];
    float ticketPrice;
    struct passengerQueue *nextPtr;
};

// Structure renaming
typedef struct passengerQueue PassengerQueue;
typedef struct passengerQueue *PassengerQueuePtr;

/*.......Function Prototypes ....*/
// Queue Operations
void firstInLine(PassengerQueuePtr headPtr);
void lastInLine(PassengerQueuePtr tailPtr);
void enqueue(PassengerQueuePtr *headPtr, PassengerQueuePtr *tailPtr, int id, char name[30], double price);
void dequeue(PassengerQueuePtr *headPtr, PassengerQueuePtr *tailPtr);
int isQueueEmpty(PassengerQueuePtr headPtr);
void printQueue(PassengerQueuePtr headPtr);
void queueInstructions(void);
int generateQueueId();

// Functions

void firstInLine(PassengerQueuePtr headPtr)
{
    printf("\nFirst in waiting queue:\tID: %d, Name: %s, Ticket Price: $%.2lf.\n",
           headPtr->seatId, headPtr->passengerName, headPtr->ticketPrice);
}

void lastInLine(PassengerQueuePtr tailPtr)
{
    printf("\nLast in waiting queue:\tID: %d, Name: %s, Ticket Price: $%.2lf.\n",
           tailPtr->seatId, tailPtr->passengerName, tailPtr->ticketPrice);
}

void enqueue(PassengerQueuePtr *headPtr, PassengerQueuePtr *tailPtr, int id, char name[30], double price)
{
    PassengerQueuePtr newPtr;                // Define pointer for addr of newNode
    newPtr = malloc(sizeof(PassengerQueue)); // Create Space for the newNode

    if (newPtr != NULL) // (check if node was created )
    {
        // add newNode to wait queue
        newPtr->seatId = id;
        strcpy(newPtr->passengerName, name);
        newPtr->ticketPrice = price;

        newPtr->nextPtr = NULL;
        if (*headPtr == NULL)
        {
            *headPtr = newPtr; // new node at end of queue
        }
        else
        {
            (*tailPtr)->nextPtr = newPtr; // dereference before pointing
        }
        *tailPtr = newPtr; // update tailPtr as the new end
    }
    else
    {
        puts("\nMemory Failure");
    }
}

void dequeue(PassengerQueuePtr *headPtr, PassengerQueuePtr *tailPtr)
{

    // Define Pointer to be used to isolate node at the beginningofqueue - to be removed
    PassengerQueuePtr tempPtr;
    tempPtr = *headPtr;

    printf("\nPassenger Being served now: \t ID: %d, Name: %s, Ticket Price: $%.2lf.\n", tempPtr->seatId, tempPtr->passengerName, tempPtr->ticketPrice); // inform the user

    *headPtr = (*headPtr)->nextPtr; // update start of queue

    if (*headPtr == NULL)
    {
        *tailPtr == NULL; // if queue is empty, update tailPtr
    }

    free(tempPtr); // deallocate memory
}

int isQueueEmpty(PassengerQueuePtr headPtr)
{
    return (headPtr == NULL); // if this is true, that is, a value of 1, empty queue
}

void printQueue(PassengerQueuePtr headPtr)
{
    if (headPtr == NULL)
    {
        puts("\nQueue is empty... nothing to print");
    }
    else
    {
        puts("\nThe passengers in the wait queue are:");
        while (headPtr != NULL)
        {
            printf("\n   -->   ID: %d, ", headPtr->seatId);
            printf("Name: %s, ", headPtr->passengerName);
            printf("Ticket Price: $%.2lf", headPtr->ticketPrice);
            headPtr = headPtr->nextPtr;
        }
        puts("\n");
    }
}

int generateQueueId()
{
    static int id = 1;
    return id++;
}

void queueInstructions(void)
{
    printf("Enter choice:\n 1 View Passenger at the front of wait queue\n 2 View Passenger at the end of line  \n 3 Add a new Passenger to the train wait queue (enqueue)  \n 4 Seat the first Passenger in line (dequeue)  \n 5 View all passengers in wait queue  \n 6  Exit train waiting Queue \n");
}
