/*
Assignment 3 PART C - Tree Operations
Passengers on a Train
Authors: Usma Qadri #991395853 and Krista Ryk #991406369
Date Created: March 24 2022
Date Updated: March 28 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
/************** TREENODE STRUCTURE *********************/
struct treeNode
{
    int seatId;
    char passengerName[30];
    float ticketPrice;
    struct treeNode *rightPtr;
    struct treeNode *leftPtr;
};

/**************  STRUCTURE RENAMING*********************/
typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

/************** FUNCTION PROTOTYPES *********************/
// 1) Insert into Tree
void insertNode(TreeNodePtr *treePtr, int id, char name[30], double price);
// 2) Remove from Tree
void deleteNode(TreeNodePtr *treePtr, int value);
void searchNode(TreeNodePtr *treePtr, int value, TreeNodePtr *parentPtr, TreeNodePtr *tempNodePtr, int *found);
// 3) Binary Search of the Tree for a data item
TreeNodePtr binaryTreeSearch(TreeNodePtr treePtr, int key);
// 4) Pre-order Traversal of Tree
void preOrder(TreeNodePtr treePtr);
// 5) Post-order Traversal of Tree
void postOrder(TreeNodePtr treePtr);
// 6) In-order Traversal of Tree
void inOrder(TreeNodePtr treePtr);
// Menu
void treeInstructions(void);
// ID
int generateTreeId();

void insertNode(TreeNodePtr *treePtr, int id, char name[30], double price)
{

    /* if treePtr is NULL */
    if (*treePtr == NULL)
    {

        // add code to dynamically allocate memory
        *treePtr = (TreeNodePtr)malloc(sizeof(TreeNode));

        if (*treePtr != NULL)
        {
            // add code here to insert node if memory was allocated

            (*treePtr)->seatId = id;
            strcpy((*treePtr)->passengerName, name);
            (*treePtr)->ticketPrice = price;
            (*treePtr)->leftPtr = NULL;
            (*treePtr)->rightPtr = NULL;

            printf("Passenger inserted.");
        }
        else
        {
            printf("Passenger not inserted due to Memory Failure");
        }

        return;
    }

    else
    {

        /* insert node in left subtree */
        if (id < (*treePtr)->seatId)
        {

            // add code to insert into left subtree
            insertNode(&((*treePtr)->leftPtr), id, name, price);
        }
        else if (id > (*treePtr)->seatId)
        {

            // add code to insert into right subtree
            insertNode(&((*treePtr)->rightPtr), id, name, price);
        }
        else
        { // will not all duplicate values to be inserted
            printf("Invalid entry, ID already exists.");
        }
    }

} // end of insert Node function

TreeNodePtr binaryTreeSearch(TreeNodePtr treePtr, int key)
{
    if (treePtr == NULL) // is the tree empty (NULL) or we have completed the search and have not found the specified key
    {
        return NULL;
    }
    else if (key == treePtr->seatId) // value has been found
    {
        return treePtr;
    }

    else if (key < treePtr->seatId) // did not find but there are other opportunities to find it (it might be elsewhere in the LEFT tree)
    {
        binaryTreeSearch(treePtr->leftPtr, key);
    }
    else
    {
        binaryTreeSearch(treePtr->rightPtr, key);
    }

} // end of binary search

void inOrder(TreeNodePtr treePtr)
{

    if (treePtr != NULL)
    {
        // add code: traverse left , print node, traverse right
        inOrder(treePtr->leftPtr);
        printf("\n    --> ID: %d ", treePtr->seatId);
        printf("Name: %s ", treePtr->passengerName);
        printf("Ticket Price: $%.2lf", treePtr->ticketPrice);
        inOrder(treePtr->rightPtr);
    }
    puts("\n");

} // end of inOrder function

void preOrder(TreeNodePtr treePtr)
{

    if (treePtr != NULL)
    {

        // add code: print node, traverse left sub, traverse right subtree
        printf("\n    --> ID: %d ", treePtr->seatId);
        printf("Name: %s ", treePtr->passengerName);
        printf("Ticket Price: $%.2lf", treePtr->ticketPrice);
        preOrder(treePtr->leftPtr);
        preOrder(treePtr->rightPtr);
    }

    puts("\n");
} // end of preOrder function

void postOrder(TreeNodePtr treePtr)
{

    if (treePtr != NULL)
    {

        // add code: traverse left sub, traverse right subtree, print node
        postOrder(treePtr->leftPtr);
        postOrder(treePtr->rightPtr);
        printf("\n    --> ID: %d ", treePtr->seatId);
        printf("Name: %s ", treePtr->passengerName);
        printf("Ticket Price: $%.2lf", treePtr->ticketPrice);
    }

    puts("\n");
} // end of postOrder function

/* deletes a node from the binary search tree */
void deleteNode(TreeNodePtr *treePtr, int id)
{
    int found;
    TreeNodePtr parentPtr, tempNodePtr, replacementNodePtr;

    /* if tree is empty */
    if (*treePtr == NULL)
    {
        printf("\nTree is empty, no passengers to remove");
        return;
    }

    parentPtr = NULL;
    tempNodePtr = NULL;

    /* find the node to be deleted */

    searchNode(treePtr, id, &parentPtr, &tempNodePtr, &found);

    /* if the node is not found */
    if (found == FALSE)
    {
        printf("\n Data not found");
        return;
    }

    /* if the node to be deleted has no child */
    if (tempNodePtr->leftPtr == NULL && tempNodePtr->rightPtr == NULL)
    {
        if (parentPtr->rightPtr == tempNodePtr)
            parentPtr->rightPtr = NULL;
        else
            parentPtr->leftPtr = NULL;

        free(tempNodePtr);
        return;
    }

    /* if the node to be deleted has only rightPtr */
    if (tempNodePtr->leftPtr == NULL && tempNodePtr->rightPtr != NULL)
    {
        if (parentPtr->leftPtr == tempNodePtr)
            parentPtr->leftPtr = tempNodePtr->rightPtr;
        else
            parentPtr->rightPtr = tempNodePtr->rightPtr;

        free(tempNodePtr);
        return;
    }

    /* if the node to be deleted has only left child */
    if (tempNodePtr->leftPtr != NULL && tempNodePtr->rightPtr == NULL)
    {
        if (parentPtr->leftPtr == tempNodePtr)
            parentPtr->leftPtr = tempNodePtr->leftPtr;
        else
            parentPtr->rightPtr = tempNodePtr->leftPtr;

        free(tempNodePtr);
        return;
    }

    /* if the node to be deleted has two children */
    if (tempNodePtr->leftPtr != NULL && tempNodePtr->rightPtr != NULL)
    {
        parentPtr = tempNodePtr;
        replacementNodePtr = tempNodePtr->rightPtr;

        while (replacementNodePtr->leftPtr != NULL)
        {
            parentPtr = replacementNodePtr;
            replacementNodePtr = replacementNodePtr->leftPtr;
        }

        tempNodePtr->seatId = replacementNodePtr->seatId;
        tempNodePtr = replacementNodePtr;
    }

} // end of delete node function

void searchNode(TreeNodePtr *treePtr, int id, TreeNodePtr *parentPtr, TreeNodePtr *tempNodePtr, int *found)
{
    TreeNodePtr tempPtr;
    tempPtr = *treePtr;
    *found = FALSE;
    *parentPtr = NULL;

    while (tempPtr != NULL)
    {
        if (tempPtr->seatId == id)
        {
            *found = TRUE;
            *tempNodePtr = tempPtr;
            return;
        }

        *parentPtr = tempPtr;
        if (tempPtr->seatId > id)
            tempPtr = tempPtr->leftPtr;
        else
            tempPtr = tempPtr->rightPtr;
    }
} // end of search node function

int generateTreeId()
{

    int item;
    srand(time(NULL)); // randomize ID - generates IDs from 0-99 inclusive
    item = rand() % 100;

} // end of generate id

void treeInstructions(void)
{
    printf("Enter choice:\n 1 Insert Passenger into Tree\n 2 Remove Passenger from Tree  \n 3 Binary search of tree for passenger  \n 4 Pre-Order Traversal of Tree  \n 5 Post-Order Traversal of Tree  \n 6  In-Order Traversal of Tree \n 7  Exit Tree Operations \n");
} // end of instructions
