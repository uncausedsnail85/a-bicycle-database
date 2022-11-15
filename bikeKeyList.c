/*
 * bikeKeyList.c
 *
 * Name:    bikeKeyList.c
 * Author:  Bryan Ang
 * E-mail:  ang.b@northeastern.edu
 * Date:    2022/08/01
 * Purpose: This file represents a collection of bike serial numbers using a
 *          linked list. To be used as the Value in a KV-Pair where the year
 *          is the value.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct bike_serialNum_node {
    int     serialNum;
    struct bike_serialNum_node*  next;
}bike_serialNum_node_t;

// Create a serialNum node
bike_serialNum_node_t* createSerialNumNode(int serialNum) {
    bike_serialNum_node_t* newNode = (bike_serialNum_node_t*) malloc(sizeof(bike_serialNum_node_t));
    if (newNode == NULL) {
       return NULL;
    }
    newNode->serialNum = serialNum;
    newNode->next = NULL;
    return newNode;
} // make node

// returns if list is empty
int serialNumListEmpty(bike_serialNum_node_t* inHead) {
    if (inHead == NULL) {
        return 1;
    } else {
        return 0;
    }
} // function empty_list

// prints one node
void printSerialNumNode(bike_serialNum_node_t* inNode) {
    printBikeRec(findBikeRecord(inNode->serialNum));
    // printf("\n");
    // printf("\t%d\n", inNode->serialNum);
} // function print node

// returns length of list
int serialNumListLength(bike_serialNum_node_t* inHead) {
    if (inHead == NULL) {
        return 0;
    } // if

    bike_serialNum_node_t* itr = inHead;
    int i = 0;
    while (itr != NULL) {
        i++;
        itr = itr->next;        
    } // while
    return i;
} // function listLength

// deletes and frees one node
int deleteSerialNumNode(bike_serialNum_node_t* inNode) {
    if (inNode == NULL) {
        return -1;
    }
    free(inNode);
    return 1;
} // function deletenode

// creates a serialNum list. For initialization
bike_serialNum_node_t* createSerialNumList() {
    return NULL;
} // function create_list

// prints the list
void printSerialNumList(bike_serialNum_node_t* inHead) {
    if (inHead == NULL) {
        printf("List of serial numbers empty.\n");
        return;
    }
    bike_serialNum_node_t* itr = inHead;
    while(itr != NULL) {
        printSerialNumNode(itr);
        itr = itr->next;
    }
    printf("\n");
} // function print list

// deletes and frees the list
int deleteSerialNumList(bike_serialNum_node_t* inHead) {
    if (inHead == NULL){
        return -1;
    }
    bike_serialNum_node_t* itr = inHead;
    bike_serialNum_node_t* itrNext = NULL;
    while(itr != NULL){
        itrNext = itr->next;
        deleteSerialNumNode(itr);
        itr = itrNext;
    }
    return 1;
}

int insertSerialNumFront(bike_serialNum_node_t** inHeadPtr, int serialNum) {
    if (inHeadPtr == NULL) {
        return -1;
    }

    bike_serialNum_node_t* newNode = createSerialNumNode(serialNum);
    if (newNode == NULL) {
        return -1;
    }

    newNode->next = *inHeadPtr;
    *inHeadPtr = newNode;
    return 1;
} // function insertfront

int insertSerialNumRear(bike_serialNum_node_t** inHeadPtr, int serialNum){
    bike_serialNum_node_t* p = NULL;
    bike_serialNum_node_t* q = NULL;

    bike_serialNum_node_t* tempNode = createSerialNumNode(serialNum);

    // INSERT NODE INTO EMPTY LIST
    if (serialNumListEmpty(*inHeadPtr)){
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
int insertSerialNum(bike_serialNum_node_t** inHeadPtr, int position, int serialNum){
    // int tempNum = 0;
    // int statusNum = -1;
    int numNodes = 0;
    int curLocation = 0;
    bike_serialNum_node_t* p = NULL;
    bike_serialNum_node_t* q = NULL;
    // bike_serialNum_node_t* r = NULL;
    bike_serialNum_node_t* tempNode;

    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL) {
        return -1;
    }//IF
    else {
        numNodes = serialNumListLength(*inHeadPtr);

        //CASE 1:  emptyList or POS==1
        if (serialNumListEmpty(*inHeadPtr) || position==1) {
            insertSerialNumFront(inHeadPtr, serialNum);
            return 1;
        }
        // CASE 2:  USER SPECIFIES POSITION GREATER THAN LISTSIZE
        else if (position > numNodes)  {
            insertSerialNumRear(inHeadPtr, serialNum);
            return 1;
        }//ELSE IF user specified POS > size
        // CASE 3:  MIDDLE OF THE LIST
        // (1) create new node (2) find spot (3) anchor q at spot (4) attach
        //      LHS of list TO new node, (4) attach the new node to RHS of list
        else {
            tempNode = createSerialNumNode(serialNum);
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

int deleteSerialNumFront(bike_serialNum_node_t** inHeadPtr) {
    // inHeadPtr == NULL: no address to pointer
    // *inheadPtr == NULL: no address to node (empty list)
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }

    bike_serialNum_node_t* tempNode = NULL;
    if (serialNumListLength(*inHeadPtr) == 1) {
        tempNode = *inHeadPtr;
        *inHeadPtr = NULL;
        // free(tempNode);
        deleteSerialNumNode(tempNode);
        return 1;
    } // if one element in list
    else {
        tempNode = *inHeadPtr;
        *inHeadPtr = tempNode->next;
        // free(tempNode);
        deleteSerialNumNode(tempNode);
        return 1;
    }
} // function delete front

int deleteSerialNumRear(bike_serialNum_node_t** inHeadPtr) {
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }

    bike_serialNum_node_t* tempNode = *inHeadPtr;
    int num = serialNumListLength(*inHeadPtr);
    if (num == 1) {
        tempNode = *inHeadPtr;
        *inHeadPtr = NULL;
        // free(tempNode);
        deleteSerialNumNode(tempNode);
        return 1;
    } else {
        bike_serialNum_node_t* itr = *inHeadPtr; 
        bike_serialNum_node_t* itrNext = itr->next;
        bike_serialNum_node_t* itrNextNext = itrNext->next;
        while(itrNextNext != NULL) {
            itr = itrNext;
            itrNext = itrNextNext;
            itrNextNext = itrNextNext->next;
        } //while
        itr->next = NULL;
        // free(itrNext);
        deleteSerialNumNode(itrNext);
        return 1;         
    } // else
} // function deleterear

// delete from pos
// Pos starts at 1 to length
int deleteSerialNumatPos(bike_serialNum_node_t** inHeadPtr, int position) {
    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }//IF

    if (position < 1){
        return -1;
    } // check for 0 or negative pos values

    int numLen = serialNumListLength(*inHeadPtr);

    if(numLen == 1 || position == 1) {
        return deleteSerialNumFront(inHeadPtr);
    } // if delete from first position
    else if(position >= numLen) {
        return deleteSerialNumRear(inHeadPtr);
    } // if delete last element or greater
    else {
        bike_serialNum_node_t* itr = *inHeadPtr;
        int currentLocation = 1;
        while (currentLocation < position - 1) {
            itr = itr->next;
            currentLocation++;
        }
        bike_serialNum_node_t* tempNode = itr->next;
        itr->next = tempNode->next;
        return deleteSerialNumNode(tempNode);
    }
}

// search or findItem
// returns first pos of an element, starts at 1
int findSerialNum(bike_serialNum_node_t* inHead, int serialNum) {
    if (inHead == NULL) {
        return -1;
    }

    bike_serialNum_node_t* itr = inHead;
    int currentPos = 1;
    // itr through list
    while (itr != NULL) {
        if (itr->serialNum == serialNum) {
            return currentPos;
        }
        currentPos++;
        itr = itr->next;
    } //while
    // if not found return 0.
    return 0;    
} // function findItem

//deleteItem. deletes first appeareance of an item. returns 1 if deleted, -1 if not found.
int deleteSerialNum(bike_serialNum_node_t** inHeadPtr, int serialNum){
    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }//IF

    int pos = findSerialNum(*inHeadPtr, serialNum);
    if (pos < 1){
        return -1;
    } else {
        return deleteSerialNumatPos(inHeadPtr, pos);
    } 
}

// int main() {
    
//     bike_serialNum_node_t* mySerialNumList = createSerialNumList();
//     insertSerialNumFront(&mySerialNumList, 1001);
//     insertSerialNumRear(&mySerialNumList, 1002);
//     insertSerialNum(&mySerialNumList, 2, 1003);

//     printSerialNumList(mySerialNumList);

//     printf("Deleting\n");
//     deleteSerialNumFront(&mySerialNumList);
//     deleteSerialNumFront(&mySerialNumList);
//     deleteSerialNumFront(&mySerialNumList);
//     printSerialNumList(mySerialNumList);

//     return 0;
// }
