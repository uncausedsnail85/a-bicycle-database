/*
 * yearHashTable.c
 *
 * Name:    yearHashTable.c
 * Author:  Bryan Ang
 * E-mail:  ang.b@northeastern.edu
 * Date:    2022/08/01
 * Purpose: This a database index implemented using a hash table. The table
 *          is linked to the bikeRec struct, where any bikeRec will have its
 *          manufactured year indexed here with its serial num for quick
 *          access.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bikeKeyList.c"
#include "yearHashTable.h"

#define NUMBYEARBUCKETS 7

 // ---------------------------------------------------------

// The kv-pair fore the has table.
// Key: manuYear
// Value: A list of serial numbers
typedef struct year_kvpair {
    int      key; //year
    bike_serialNum_node_t*    value;  
}year_kvpair_t;

// ---------------------------------------------------------

typedef struct year_node {
    year_kvpair_t*     data;
    struct year_node*  next;
}year_node_t;

year_node_t* yearHashMapArray[NUMBYEARBUCKETS];

 
/* ***************************************************** */
/*                 LinkedList Functions                  */
/* ***************************************************** */

year_node_t* createYearKvNode(year_kvpair_t* inPair) {
    year_node_t* newNode = (year_node_t*) malloc(sizeof(year_node_t));
    if (newNode == NULL) {
       return NULL;
    }
    newNode->data = inPair;
    newNode->next = NULL;
    return newNode;
} // make node

void printYearKvNode(year_node_t* inNode) {
    printf("---- NODE ----\n");
    printf("DATA:\n");
    printYearKVpair(inNode->data);
} // function print node

int yearKvListLength(year_node_t* inHead) {
    if (inHead == NULL) {
        return 0;
    } // if

    year_node_t* itr = inHead;
    int i = 0;
    while (itr != NULL) {
        i++;
        itr = itr->next;        
    } // while
    return i;
} // function yearKvListLength

int deleteYearKvNode(year_node_t* inNode) {
    if (inNode == NULL) {
        return -1;
    }
    deleteYearKVpair(inNode->data);
    free(inNode);
    return 1;
} // function deletenode

year_node_t* createYearKvList() {
    return NULL;
} // function create_list

// 2.
void printYearKvList(year_node_t* inHead) {
    if (inHead == NULL) {
        printf("EMPTY.\n");
        return;
    }
    year_node_t* itr = inHead;
    while(itr != NULL) {
        printYearKvNode(itr);
        // printf("%d ", itr->data);
        itr = itr->next;
    }
    printf("\n");
} // function print list

// 3. deleteYearKList
int deleteYearKvList(year_node_t* inHead) {
    if (inHead == NULL){
        return -1;
    }
    year_node_t* itr = inHead;
    year_node_t* itrNext = NULL;
    while(itr != NULL){
        itrNext = itr->next;
        deleteYearKvNode(itr);
        itr = itrNext;
    }
    return 1;
}

// 4.
int insertYearKvFront(year_node_t** inHeadPtr, year_kvpair_t* inKVpair) {
    if (inHeadPtr == NULL) {
        return -1;
    }

    year_node_t* newNode = createYearKvNode(inKVpair);
    if (newNode == NULL) {
        return -1;
    }

    newNode->next = *inHeadPtr;
    *inHeadPtr = newNode;
    return 1;
} // function insertfront



// 5.
int insertYearKvRear(year_node_t** inHeadPtr, year_kvpair_t* inKVpair){
    year_node_t* p = NULL;
    year_node_t* q = NULL;

    year_node_t* tempNode = createYearKvNode(inKVpair);

    // INSERT NODE INTO EMPTY LIST
    if (yearKvListEmpty(*inHeadPtr)){
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

// 6. insertYearKvatPos(int pos)
// Position starts from 1 to length of list + 1.
int insertYearKvatPos(year_node_t** inHeadPtr, int position, year_kvpair_t* inKVpair){
    // int tempNum = 0;
    // int statusNum = -1;
    int numNodes = 0;
    int curLocation = 0;
    year_node_t* p = NULL;
    year_node_t* q = NULL;
    // year_node_t* r = NULL;
    year_node_t* tempNode;

    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL) {
        return -1;
    }//IF
    else {
        numNodes = yearKvListLength(*inHeadPtr);

        //CASE 1:  emptyList or POS==1
        if (yearKvListEmpty(*inHeadPtr) || position==1) {
            insertYearKvFront(inHeadPtr, inKVpair);
            return 1;
        }
        // CASE 2:  USER SPECIFIES POSITION GREATER THAN LISTSIZE
        else if (position > numNodes)  {
            insertYearKvRear(inHeadPtr, inKVpair);
            return 1;
        }//ELSE IF user specified POS > size
        // CASE 3:  MIDDLE OF THE LIST
        // (1) create new node (2) find spot (3) anchor q at spot (4) attach
        //      LHS of list TO new node, (4) attach the new node to RHS of list
        else {
            tempNode = createYearKvNode(inKVpair);
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

// 7.
int deleteYearKvFront(year_node_t** inHeadPtr) {
    // inHeadPtr == NULL: no address to pointer
    // *inheadPtr == NULL: no address to node (empty list)
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }

    year_node_t* tempNode = NULL;
    if (yearKvListLength(*inHeadPtr) == 1) {
        tempNode = *inHeadPtr;
        *inHeadPtr = NULL;
        // free(tempNode);
        deleteYearKvNode(tempNode);
        return 1;
    } // if one element in list
    else {
        tempNode = *inHeadPtr;
        *inHeadPtr = tempNode->next;
        // free(tempNode);
        deleteYearKvNode(tempNode);
        return 1;
    }
} // function delete front

// 8.
int deleteYearKvRear(year_node_t** inHeadPtr) {
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }

    year_node_t* tempNode = *inHeadPtr;
    int num = yearKvListLength(*inHeadPtr);
    if (num == 1) {
        tempNode = *inHeadPtr;
        *inHeadPtr = NULL;
        // free(tempNode);
        deleteYearKvNode(tempNode);
        return 1;
    } else {
        year_node_t* itr = *inHeadPtr; 
        year_node_t* itrNext = itr->next;
        year_node_t* itrNextNext = itrNext->next;
        while(itrNextNext != NULL) {
            itr = itrNext;
            itrNext = itrNextNext;
            itrNextNext = itrNextNext->next;
        } //while
        itr->next = NULL;
        // free(itrNext);
        deleteYearKvNode(itrNext);
        return 1;         
    } // else
} // function deleterear

// 9. delete from pos
// Pos starts at 1 to length
int deleteYearKvatPos(year_node_t** inHeadPtr, int position) {
    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }//IF

    if (position < 1){
        return -1;
    } // check for 0 or negative pos values

    int numLen = yearKvListLength(*inHeadPtr);

    if(numLen == 1 || position == 1) {
        return deleteYearKvFront(inHeadPtr);
    } // if delete from first position
    else if(position >= numLen) {
        return deleteYearKvRear(inHeadPtr);
    } // if delete last element or greater
    else {
        year_node_t* itr = *inHeadPtr;
        int currentLocation = 1;
        while (currentLocation < position - 1) {
            itr = itr->next;
            currentLocation++;
        }
        year_node_t* tempNode = itr->next;
        itr->next = tempNode->next;
        return deleteYearKvNode(tempNode);
    }
}

int yearKvListEmpty(year_node_t* inHead) {
    if (inHead == NULL) {
        return 1;
    } else {
        return 0;
    }
} // function empty_list

// returns first pos of an element, starts at 1
int findYearKv(year_node_t* inHead, int item) {
    if (inHead == NULL) {
        return -1;
    }

    year_node_t* itr = inHead;
    int currentPos = 1;
    // itr through list
    while (itr != NULL) {
        if (itr->data->key == item) {
            return currentPos;
        }
        currentPos++;
        itr = itr->next;
    } //while
    // if not found return 0.
    return 0;    
} // function findYearKv

// deleteYearKv. deletes first appeareance of an item. returns 1 if deleted, -1 if not found.
int deleteYearKv(year_node_t** inHeadPtr, int item){
    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }//IF

    int pos = findYearKv(*inHeadPtr, item);
    if (pos < 1){
        return -1;
    } else {
        return deleteYearKvatPos(inHeadPtr, pos);
    } 
}

// returns the value (bike_serialNum_node_t) based on a given key. NULL if doesnt exist
bike_serialNum_node_t* getBikeKvValue(year_node_t* inHead, int key) {
    if (inHead == NULL) {
        return NULL;
    }
    year_node_t* itr = inHead;
    // itr through list
    while (itr != NULL) {
        if (itr->data->key == key) {
            return itr->data->value;
        }
        itr = itr->next;
    } //while
    // if not found return 0.
    return NULL;   
} // function getBikeKvValue


/* ***************************************************** */
/*                   KV-Pair Functions                   */
/* ***************************************************** */

// creates a key-value pair from a bike_serialNum_node_t using 
year_kvpair_t* getYearKVpair(int manuYear, int serialNum) {
    year_kvpair_t* newKVpair = (year_kvpair_t*) malloc(sizeof(year_kvpair_t));

    newKVpair->key = manuYear;
    bike_serialNum_node_t* tempKeyNode = createSerialNumNode(serialNum);
    newKVpair->value = tempKeyNode;
    return newKVpair;
} // get kv pair

// prints the given kv-pair
void printYearKVpair(year_kvpair_t* inPair) {
    printf("---- Key-Value Pair ----\n");
    printf("KEY:    %d\n", inPair->key);
    printf("VALUE: \n");
    printSerialNumList(inPair->value);
} // print kv pair

// function that frees KVPair
int deleteYearKVpair(year_kvpair_t* inKVpair) {
    if (inKVpair == NULL) {
        return -1;
    }
    free(inKVpair);
    return 1;    
} // function delete kv


/* ***************************************************** */
/*                   Hash Map Functions                  */
/* ***************************************************** */

// Computes the array index for a given integer
int computeYearHashIndex(int key, int numBuckets){
    return ((key % 10) * 10000) % numBuckets;
}//FUNCTION computeYearHashIndex

// Checks if the hash map has a given key (year)
int yearTableHasKey(int key) {
    int hashIndex = computeYearHashIndex(key, NUMBYEARBUCKETS);
    int findStatus = findYearKv(yearHashMapArray[hashIndex], key);
    return findStatus;
}// FUNCTION HASKEY

// inserts an serialNum given it's year(key)
int yearTableInsertKey(int key, int serialNum){

    // If key not found at hash index, create new linked list and add to kv
    if (yearTableHasKey(key) < 1) {
        int hashIndex = computeYearHashIndex(key, NUMBYEARBUCKETS);
        // add to linked-list at hash index
        year_kvpair_t* tempKV = getYearKVpair(key, serialNum);
        insertYearKvRear(&yearHashMapArray[hashIndex], tempKV);
        return 1;
    } else {
        // key already in list at index
        // add to rear of the linked list at index
        int hashIndex = computeYearHashIndex(key, NUMBYEARBUCKETS);
        bike_serialNum_node_t* tempKeyNode = getBikeKvValue(yearHashMapArray[hashIndex], key);
        insertSerialNumRear(&tempKeyNode, serialNum);
        return 1;
    }
}//FUNCTION INSERTKEY

// Deletes entire KV pair of that year(key), i.e. will remove all associated serialNums
int yearTableDeleteKey(int key){
    int hashIndex = computeYearHashIndex(key, NUMBYEARBUCKETS);
    return deleteYearKv(&yearHashMapArray[hashIndex], key);
}//FUNCTION DELETEKEY

// Prints the entire contents of one cell of the array
void yearTablePrintBucket(int bucketNumber){
    printYearKvList(yearHashMapArray[bucketNumber]);
}//function PRINTBUCKET

// Prints the entire hash map
void printYearHashMap(){
    int i;
    for (i = 0; i < NUMBYEARBUCKETS; i++) {
        printf("******************\n");
        printf("Bucket %d is now:\n", i);
        yearTablePrintBucket(i);
        printf("\n\n");
    }
}//function PRINTHASHMAP

// can also be called accessKey(key)
bike_serialNum_node_t* yearTableFindSerialNumNode(int key) {
    if (yearTableHasKey(key) < 1) {
        return NULL;
    } else {
        int hashIndex = computeYearHashIndex(key, NUMBYEARBUCKETS);
        return getBikeKvValue(yearHashMapArray[hashIndex], key);
    }
} // function findCustomerRec

// Removes a serial number from the hash map, given it's manuYear(the key)
int deleteSerialNumFromYearHashTable(int manuYear, int serialNum) {

    // 1. Check if table hasKey, i.e. if the year is found
    // 2. Delete the serialNum from serialNum list of that year
    // 3. if serilNum list is empty, delete year kv pair

    bike_serialNum_node_t* tempNode = yearTableFindSerialNumNode(manuYear);
    if (tempNode == NULL) {
        return 0;
    }

    deleteSerialNum(&tempNode, serialNum);

    if (serialNumListEmpty(tempNode)) {
        int hashIndex = computeYearHashIndex(manuYear, NUMBYEARBUCKETS);
        deleteYearKv(&yearHashMapArray[hashIndex], manuYear);
    }
    return 1;
}

// Updates a serial num (value) to a new Year(key) in the year hash table
int updateYearfromYearHashTable(int oldYear, int serialNum, int newYear) {
    if (yearTableHasKey(oldYear) < 1) {
        printf("Key not found while updating year in index table.\n");
        return 0;
    }
    deleteSerialNumFromYearHashTable(oldYear, serialNum);
    yearTableInsertKey(newYear, serialNum);
}

/****************************************************************/

