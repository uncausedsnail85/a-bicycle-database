/*
 * ownerHistoryList.c
 *
 * Name:    ownerHistoryList.c
 * Author:  Bryan Ang
 * E-mail:  ang.b@northeastern.edu
 * Date:    2022/08/01
 * Purpose: This file represents a linked list of owner strings. For the purposes of
 *          keeping a record of owner history. To be used as a field in the BikeRec
 *          struct.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "ownerHistoryList.h"

typedef struct owner_hst_node {
    char*     name;
    struct owner_hst_node*  next;
}owner_hst_node_t;

// Create owner node
owner_hst_node_t* createOwnerNode(char* owner) {
    owner_hst_node_t* newNode = (owner_hst_node_t*) malloc(sizeof(owner_hst_node_t));
    if (newNode == NULL) {
       return NULL;
    }
    newNode->name = (char*) malloc(sizeof(char)*20);
    strcpy(newNode->name, owner);
    newNode->next = NULL;
    return newNode;
} // make node

// returns if list of owners is empty
int ownerListEmpty(owner_hst_node_t* inHead) {
    if (inHead == NULL) {
        return 1;
    } else {
        return 0;
    }
} // function empty_list

// prints the owner node
void printOwnerNode(owner_hst_node_t* inNode) {
    printf("\t%s\n", inNode->name);
} // function print node

// returns length of the owner list
int ownerListLength(owner_hst_node_t* inHead) {
    if (inHead == NULL) {
        return 0;
    } // if

    owner_hst_node_t* itr = inHead;
    int i = 0;
    while (itr != NULL) {
        i++;
        itr = itr->next;        
    } // while
    return i;
} // function listLength

// deletes the owner node
int deleteOwnerNode(owner_hst_node_t* inNode) {
    if (inNode == NULL) {
        return -1;
    }
    free(inNode->name);
    free(inNode);
    return 1;
} // function deletenode

// creates a Owner history list
owner_hst_node_t* createOwnerList() {
    return NULL;
} // function create_list

// print the owner list
void printOwnerList(owner_hst_node_t* inHead) {
    if (inHead == NULL) {
        printf("OWNER LIST EMPTY.\n");
        return;
    }
    owner_hst_node_t* itr = inHead;
    printf("(Curr)");
    while(itr != NULL) {
        printOwnerNode(itr);
        // printf("%d ", itr->name);
        itr = itr->next;
    }
    printf("\n");
} // function print list

void writeOwnerList(FILE *fp, owner_hst_node_t* inHead) {
    if (inHead == NULL) {
        return;
    }
    owner_hst_node_t* itr = inHead;
    while(itr != NULL) {
        fprintf(fp, "%s-", itr->name);
        itr = itr->next;
    }
}

// delete the owner list
int deleteOwnerList(owner_hst_node_t* inHead) {
    if (inHead == NULL){
        return -1;
    }
    owner_hst_node_t* itr = inHead;
    owner_hst_node_t* itrNext = NULL;
    while(itr != NULL){
        itrNext = itr->next;
        deleteOwnerNode(itr);
        itr = itrNext;
    }
    return 1;
}

// insert the owner to the front of the list
int insertOwnerFront(owner_hst_node_t** inHeadPtr, char* owner) {
    if (inHeadPtr == NULL) {
        return -1;
    }

    owner_hst_node_t* newNode = createOwnerNode(owner);
    if (newNode == NULL) {
        return -1;
    }

    newNode->next = *inHeadPtr;
    *inHeadPtr = newNode;
    return 1;
} // function insertfront

// insert the owner to the rear of the list
int insertOwnerRear(owner_hst_node_t** inHeadPtr, char* owner){
    owner_hst_node_t* p = NULL;
    owner_hst_node_t* q = NULL;

    owner_hst_node_t* tempNode = createOwnerNode(owner);

    // INSERT NODE INTO EMPTY LIST
    if (ownerListEmpty(*inHeadPtr)){
        *inHeadPtr = tempNode;
        return 1;
    }
    else {
        // FIND THE LAST NODE (make p point to it)
        p = *inHeadPtr;
        q= p->next;
        while (q != NULL){
            p = q;
            q = q->next;
        }// WHILE
    }//ELSE list not empty

    //ATTACH NEW NODE TO THE LAST NODE
    p->next = tempNode;

    return 1;
}//function INSERTREAR

// insert(int pos)
// Position starts from 1 to length of list + 1.
int insertOwner(owner_hst_node_t** inHeadPtr, int position, char* owner){
    // int tempNum = 0;
    // int statusNum = -1;
    int numNodes = 0;
    int curLocation = 0;
    owner_hst_node_t* p = NULL;
    owner_hst_node_t* q = NULL;
    // owner_hst_node_t* r = NULL;
    owner_hst_node_t* tempNode;

    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL) {
        return -1;
    }//IF
    else {
        numNodes = ownerListLength(*inHeadPtr);

        //CASE 1:  emptyList or POS==1
        if (ownerListEmpty(*inHeadPtr) || position==1) {
            insertOwnerFront(inHeadPtr, owner);
            return 1;
        }
        // CASE 2:  USER SPECIFIES POSITION GREATER THAN LISTSIZE
        else if (position > numNodes)  {
            insertOwnerRear(inHeadPtr, owner);
            return 1;
        }//ELSE IF user specified POS > size
        // CASE 3:  MIDDLE OF THE LIST
        // (1) create new node (2) find spot (3) anchor q at spot (4) attach
        //      LHS of list TO new node, (4) attach the new node to RHS of list
        else {
            tempNode = createOwnerNode(owner);
            p = (*inHeadPtr);
            q = p->next;
            curLocation = 1;
            while (curLocation < position-1){
                p = q;
                q = q->next;
                curLocation++;
            }//WHILE

            // NOW p POINTS TO NODE BEFORE; q POINTS TO NODE AFTER

            //ATTACH LHS OF LIST TO NEW NODE 'tempNode'
            p->next=tempNode;

            //ATTACH NEW NODE TO RHS LIST
            tempNode->next = q;
            return 1;
        }//ELSE
        return 1;
    }//ELSE
}// function INSERT

// delete the owner at the front of the list
int deleteOwnerFront(owner_hst_node_t** inHeadPtr) {
    // inHeadPtr == NULL: no address to pointer
    // *inheadPtr == NULL: no address to node (empty list)
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }

    owner_hst_node_t* tempNode = NULL;
    if (ownerListLength(*inHeadPtr) == 1) {
        tempNode = *inHeadPtr;
        *inHeadPtr = NULL;
        // free(tempNode);
        deleteOwnerNode(tempNode);
        return 1;
    } // if one element in list
    else {
        tempNode = *inHeadPtr;
        *inHeadPtr = tempNode->next;
        // free(tempNode);
        deleteOwnerNode(tempNode);
        return 1;
    }
} // function delete front

// delete the owner at the rear of the list
int deleteOwnerRear(owner_hst_node_t** inHeadPtr) {
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }

    owner_hst_node_t* tempNode = *inHeadPtr;
    int num = ownerListLength(*inHeadPtr);
    if (num == 1) {
        tempNode = *inHeadPtr;
        *inHeadPtr = NULL;
        // free(tempNode);
        deleteOwnerNode(tempNode);
        return 1;
    } else {
        owner_hst_node_t* itr = *inHeadPtr; 
        owner_hst_node_t* itrNext = itr->next;
        owner_hst_node_t* itrNextNext = itrNext->next;
        while(itrNextNext != NULL) {
            itr = itrNext;
            itrNext = itrNextNext;
            itrNextNext = itrNextNext->next;
        } //while
        itr->next = NULL;
        // free(itrNext);
        deleteOwnerNode(itrNext);
        return 1;         
    } // else
} // function deleterear

// delete from pos
// Pos starts at 1 to length
int deleteOwneratPos(owner_hst_node_t** inHeadPtr, int position) {
    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }//IF

    if (position < 1){
        return -1;
    } // check for 0 or negative pos values

    int numLen = ownerListLength(*inHeadPtr);

    if(numLen == 1 || position == 1) {
        return deleteOwnerFront(inHeadPtr);
    } // if delete from first position
    else if(position >= numLen) {
        return deleteOwnerRear(inHeadPtr);
    } // if delete last element or greater
    else {
        owner_hst_node_t* itr = *inHeadPtr;
        int currentLocation = 1;
        while (currentLocation < position - 1) {
            itr = itr->next;
            currentLocation++;
        }
        owner_hst_node_t* tempNode = itr->next;
        itr->next = tempNode->next;
        return deleteOwnerNode(tempNode);
    }
}

// search or findItem
// returns first pos of an element, starts at 1
int findOwner(owner_hst_node_t* inHead, char* owner) {
    if (inHead == NULL) {
        return -1;
    }

    owner_hst_node_t* itr = inHead;
    int currentPos = 1;
    // itr through list
    while (itr != NULL) {
        if (itr->name == owner) {
            return currentPos;
        }
        currentPos++;
        itr = itr->next;
    } //while
    // if not found return 0.
    return 0;    
} // function findItem

//deleteItem. deletes first appeareance of an item. returns 1 if deleted, -1 if not found.
int deleteOwner(owner_hst_node_t** inHeadPtr, char* owner){
    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }//IF

    int pos = findOwner(*inHeadPtr, owner);
    if (pos < 1){
        return -1;
    } else {
        return deleteOwneratPos(inHeadPtr, pos);
    } 
}