/*
Assignment 3 PART D - Complete Integration
Passengers on a Train
Authors: Usma Qadri #991395853 and Krista Ryk #991406369
Date Created: March 28 2022
Date Updated: March 28 2022
*/

#include "stack.h"
#include "queue.h"
#include "tree.h"

void operationInstructions(void);

// function main begins program execution
int main(void)
{
	//* Main Variables*//
	int id;
	char name[30];
	double price;
	char priceInput[10];
	char *priceInputPtr;
	char nameInput[30];
	char *nameInputPtr;
	unsigned int operationChoice; // user's menu choice

	//*Stack Variables*//
	PassengerPtr stackPtr = NULL; // creating pointer to top-of-stack
	int stackChoice;

	/*Queue Variables*/
	PassengerQueuePtr headPtr = NULL; // creating pointer to start of queue
	PassengerQueuePtr tailPtr = NULL; // creating pointer to end of queue
	int queueChoice;

	/*Tree Variables*/
	TreeNodePtr rootPtr = NULL;
	TreeNodePtr searchPtr = NULL; // declare pointer to search - node
	int treeChoice;
	int searchKey;

	/*Main Menu*/
	operationInstructions(); // display the menu
	printf("%s", "? ");
	scanf("%u", &operationChoice);

	// while user does not enter 4
	while (operationChoice != 4)
	{

		switch (operationChoice)
		{
		case 1:
			/*Stack Menu*/
			stackInstructions();
			printf("? ");
			scanf("%d", &stackChoice);

			while (stackChoice != 5)
			{
				switch (stackChoice)
				{
				case 1:

					printf("%s", "\nInsert a Passenger via Stack: \n");

					printf("%s", "Enter Passenger Name: \n");
					scanf("%s", nameInput);
					strcpy(name, nameInput);

					while (strtod(name, &nameInputPtr) != 0.0)
					{
						printf("%s", "That is not a valid Name! Try again! \n");
						printf("%s", "Enter Passenger Name: \n");
						scanf("%s", nameInput);
						strcpy(name, nameInput);
					}

					printf("%s", "Enter the Price of the Ticket: \n");
					scanf("%s", priceInput);
					price = strtod(priceInput, &priceInputPtr);
					while (price <= 0)

					{
						printf("%s", "That is not a valid price! Try again! \n");
						scanf("%s", priceInput);
						price = strtod(priceInput, &priceInputPtr);
					}

					stackPtr = push(stackPtr, generateStackId(), name, price);
					printStack(stackPtr);
					printf("%s", "\n");
					break;

				case 2:
					if (!isEmpty(stackPtr))
					{
						stackPtr = pop(stackPtr);
					}
					printStack(stackPtr);
					break;

				case 3:
					if (!isEmpty(stackPtr))
					{
						topOfStack(stackPtr);
					}
					printStack(stackPtr);
					break;
				case 4:
					if (!isEmpty(stackPtr))
					{
						bottomOfStack(stackPtr);
					}
					printStack(stackPtr);
					break;
				default:
					printf("Invalid choice.\n\n");
					break;
				}
				stackInstructions();
				printf("? ");
				scanf("%d", &stackChoice);
			}

			break;

		case 2:
			/*Queue Menu*/
			queueInstructions();
			printf("? ");
			scanf("%d", &queueChoice);

			while (queueChoice != 6)
			{
				switch (queueChoice)
				{
				case 1: // first in queue head

					if (!isQueueEmpty(headPtr))
					{
						firstInLine(headPtr);
					}
					printQueue(headPtr);
					break;
				case 2: // last in queue tail

					if (!isQueueEmpty(tailPtr))
					{
						lastInLine(tailPtr);
					}
					printQueue(headPtr);
					break;

				case 3: // Add or queue

					printf("%s", "\nInsert a Passenger: \n");

					printf("%s", "Enter Passenger Name: \n");
					scanf("%s", nameInput);
					strcpy(name, nameInput);

					while (strtod(name, &nameInputPtr) != 0.0)
					{
						printf("%s", "That is not a valid Name! Try again! \n");
						printf("%s", "Enter Passenger Name: \n");
						scanf("%s", nameInput);
						strcpy(name, nameInput);
					}

					printf("%s", "Enter the Price of the Ticket: \n");
					scanf("%s", priceInput);
					price = strtod(priceInput, &priceInputPtr);
					while (price <= 0)

					{
						printf("%s", "That is not a valid price! Try again! \n");
						scanf("%s", priceInput);
						price = strtod(priceInput, &priceInputPtr);
					}

					// queue
					enqueue(&headPtr, &tailPtr, generateQueueId(), name, price);
					printf("%s", "\n");
					break;

				case 4: // dequeue
					if (!isQueueEmpty(headPtr))
					{
						dequeue(&headPtr, &tailPtr);
					}
					printQueue(headPtr);
					break;

				case 5:

					printQueue(headPtr);

					break;

				default:
					printf("Invalid choice.\n\n");
					break;
				}
				queueInstructions();
				printf("? ");
				scanf("%d", &queueChoice);
			}

			break;

		case 3:
			/*Tree Menu*/
			treeInstructions();
			printf("? ");
			scanf("%d", &treeChoice);

			while (treeChoice != 7)
			{
				switch (treeChoice)
				{
				case 1: // Insert Passenger into Tree

					// Get data from user
					printf("%s", "\nInsert a Passenger via Tree: \n");
					printf("%s", "Enter Passenger Name: \n");
					scanf("%s", nameInput);
					strcpy(name, nameInput);

					while (strtod(name, &nameInputPtr) != 0.0)
					{
						printf("%s", "That is not a valid Name! Try again! \n");
						printf("%s", "Enter Passenger Name: \n");
						scanf("%s", nameInput);
						strcpy(name, nameInput);
					} // end of while

					printf("%s", "Enter the Price of the Ticket: \n");
					scanf("%s", priceInput);
					price = strtod(priceInput, &priceInputPtr);
					while (price <= 0)

					{
						printf("%s", "That is not a valid price! Try again! \n");
						scanf("%s", priceInput);
						price = strtod(priceInput, &priceInputPtr);
					} // end of while

					// Insert into tree
					insertNode(&rootPtr, generateTreeId(), name, price);
					printf("%s", "\n");
					break;

				case 2: // Remove Passenger from Tree
					printf("\nEnter Customer ID to be deleted: ");
					scanf("%d", &id);
					deleteNode(&rootPtr, id);
					break;

				case 3: // Binary Search of Tree for Passenger
					printf("\nEnter a search key: ");
					scanf("%d", &searchKey);
					searchPtr = binaryTreeSearch(rootPtr, searchKey); // returns with address of where node is found, if it is found -- needs to store the address
					/*determine if the node was found */
					if (searchPtr != NULL)
					{
						printf("\nThe customer with ID %d was found\n", searchPtr->seatId);
						printf("Customers Name: %s ", searchPtr->passengerName);
						printf("\nTicket Price: $%.2lf\n", searchPtr->ticketPrice);
					}
					else
					{
						printf("There is no customer with ID %d on the train\n", searchKey);
					}
					break;

				case 4: // Pre-Order Traversal of Tree
					printf("%s", "\n PreOrder Traversal \n");
					preOrder(rootPtr);

					break;

				case 5: // Post- Order Traversal of Tree
					printf("%s", "\n PostOrder Traversal \n");
					postOrder(rootPtr);

					break;

				case 6: // In-Order Traversal of Tree
					printf("%s", "\n Inorder Traversal \n");
					inOrder(rootPtr);

					break;

				default:
					printf("%s", "Invalid choice\n\n");
					break;
				} // end of INNER MENU

				treeInstructions();
				printf("%s", "? ");
				scanf("%d", &treeChoice);
			} // end of inner while

			break;

		default:
			puts("Invalid choice.\n");
			operationInstructions();
			break;
		} // end switch

		operationInstructions();
		printf("%s", "? ");
		scanf("%u", &operationChoice);
	} // end  outer while

	puts("End of run.");
} // end main

void operationInstructions(void)
{
	printf("Enter choice:\n 1 Stack Operations\n 2 Queue Operations  \n 3 Tree Operations\n 4  Exit  \n");
}
