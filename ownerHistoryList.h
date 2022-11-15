/*
 * ownerHistoryList.h
 *
 * Name:    ownerHistoryList.h
 * Author:  Bryan Ang
 * E-mail:  ang.b@northeastern.edu
 * Date:    2022/08/01
 * Purpose: This file represents a linked list of owner strings. For the purposes of
 *          keeping a record of owner history. To be used as a field in the BikeRec
 *          struct.
 */

#include <stdio.h>
#include <stdlib.h> 

typedef struct owner_hst_node owner_hst_node_t;

void printOwnerNode(owner_hst_node_t* inNode); //
owner_hst_node_t* createOwnerNode(char* owner); //
owner_hst_node_t* createOwnerList(); //
int ownerListEmpty(owner_hst_node_t* inHead); //
void printOwnerList(owner_hst_node_t* inHead); //
int ownerListLength(owner_hst_node_t* inHead); //

int insertOwnerFront(owner_hst_node_t** inHeadPtr, char* owner); //
int insertOwnerRear(owner_hst_node_t** inHeadPtr, char* owner); //
int insertOwner(owner_hst_node_t** inHeadPtr, int position, char* owner); //

int deleteOwnerNode(owner_hst_node_t* inNode); //
int deleteOwnerFront(owner_hst_node_t** inHeadPtr); //
int deleteOwnerRear(owner_hst_node_t** inHeadPtr); //
int deleteOwnerList(owner_hst_node_t* inHead); //
int deleteOwneratPos(owner_hst_node_t** inHeadPtr, int position); //

int findOwner(owner_hst_node_t* inHead, char* owner); //
int deleteOwner (owner_hst_node_t** inHeadPtr, char* owner);

void writeOwnerList(FILE *fp, owner_hst_node_t* inHead);