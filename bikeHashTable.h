/*
 * bikeHashTable.h
 *
 * Name:    bikeHashTable.h
 * Author:  Bryan Ang
 * E-mail:  ang.b@northeastern.edu
 * Date:    2022/08/01
 * Purpose: This file contains all the components necessary for a hash table, including
 *          the array, the linked list of kv-pairs, the kv-pair and the bike struct.
 *          The hash table provides a data strucure to store and retrieve bike records.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ownerHistoryList.h"

// ------------- typedef ---------------

typedef enum possessionStatus {WITHOWNER, MISSING, STOLEN} STATUS;

typedef struct bikeRec {
    int     serialNum;
    char*   manufacturer;
    char*   model;
    int     manufacturedYear;
    STATUS possessionStatus;
    owner_hst_node_t*   owner;
}bike_t;


 // ---------------------------------------------------------

 typedef struct bike_kvpair {
      int            key;
      bike_t*   value;
 }bike_kvpair_t;

 // ---------------------------------------------------------

 typedef struct bike_node {
     bike_kvpair_t*     data;
     struct bike_node*  next;
 }bike_node_t;

/*
* List functions
*/
bike_node_t* createNode(bike_kvpair_t* inPair);
void printNode(bike_node_t* inNode);
int listLength(bike_node_t* inHead);
int deleteNode(bike_node_t* inNode);
bike_node_t* createList();
void printList(bike_node_t* inHead);
int deleteList(bike_node_t* inHead);
int insertFront(bike_node_t** inHeadPtr, bike_kvpair_t* inKVpair);
int insertRear(bike_node_t** inHeadPtr, bike_kvpair_t* inKVpair);
int insert(bike_node_t** inHeadPtr, int position, bike_kvpair_t* inKVpair);
int deleteFront(bike_node_t** inHeadPtr);
int deleteRear(bike_node_t** inHeadPtr);
int delete(bike_node_t** inHeadPtr, int position);
int findItem(bike_node_t* inHead, int item);
int deleteItem(bike_node_t** inHeadPtr, int item);
bike_t* getValue(bike_node_t* inHead, int key);
int populateList(bike_node_t** inHeadPtr);
void writeBikeList(FILE *fp, bike_node_t* inHead);

/*
* KV-Pair functions (Serialnum-bikeRec pair)
*/
bike_kvpair_t* getKVpair(bike_t* inCust);
void printKVpair(bike_kvpair_t* inPair);
int deleteKVpair(bike_kvpair_t* inKVpair);

/*
* BikeRec functions
*/
bike_t* getBike();
int updateBike(bike_t** inBike, int choice);
void printBikeRec(bike_t* inCust);
int deleteBikeRec(bike_t* inRec);
void writeBikeRec(FILE *fp, bike_t* inBike);

/*
* Hash Map functions
*/
int computeHashIndex(int key, int numBuckets);
int hasKey(int key);
int insertKey(int key, bike_t* bikeRec);
int deleteKey(int key);
void printBucket(int bucketNumber);
void printHashMap();
int populateHash();
bike_t* findBikeRecord(int key);
int insertOwnertoHashTable(int serialNum, char* owner);
void writeHashMap();
int loadHashAtStartup();

