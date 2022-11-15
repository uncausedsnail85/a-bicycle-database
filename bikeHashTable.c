
/*
 * bikeHashTable.c
 *
 * Name:    bikeHashTable.c
 * Author:  Bryan Ang
 * E-mail:  ang.b@northeastern.edu
 * Date:    2022/08/01
 * Purpose: This file contains all the components necessary for a hash table, including
 *          the array, the linked list of kv-pairs, the kv-pair and the bike struct.
 *          The hash table provides a data strucure to store and retrieve bike records.
 */

#include "bikeHashTable.h"
#include "ownerHistoryList.c"
#include "yearHashTable.c"


#define NUMBBIKEBUCKETS 7
#define DATABASEFILENAME "database.txt"

bike_node_t* bikeHashMapArray[NUMBBIKEBUCKETS];

/* ***************************************************** */
/*                 LinkedList Functions                  */
/* ***************************************************** */

// Create node for a bike KV pair
bike_node_t* createNode(bike_kvpair_t* inPair) {
    bike_node_t* newNode = (bike_node_t*) malloc(sizeof(bike_node_t));
    if (newNode == NULL) {
       return NULL;
    }
    newNode->data = inPair;
    newNode->next = NULL;
    return newNode;
} // make node

// prints bike-kv node
void printNode(bike_node_t* inNode) {
    printf("---- NODE ----\n");
    printf("DATA:\n");
    printKVpair(inNode->data);
} // function print node

// Returns legnth of bike-kv node
int listLength(bike_node_t* inHead) {
    if (inHead == NULL) {
        return 0;
    } // if

    bike_node_t* itr = inHead;
    int i = 0;
    while (itr != NULL) {
        i++;
        itr = itr->next;        
    } // while
    return i;
} // function listLength

// Deletes a bike-kv node
int deleteNode(bike_node_t* inNode) {
    if (inNode == NULL) {
        return -1;
    }
    deleteBikeRec(inNode->data->value);
    deleteKVpair(inNode->data);
    free(inNode);
    return 1;
} // function deletenode

// creates a list for bike-kv node
bike_node_t* createList() {
    return NULL;
} // function create_list

//prints the list of bike kv-nodes
void printList(bike_node_t* inHead) {
    if (inHead == NULL) {
        printf("EMPTY.\n");
        return;
    }
    bike_node_t* itr = inHead;
    while(itr != NULL) {
        printNode(itr);
        // printf("%d ", itr->data);
        itr = itr->next;
    }
    printf("\n");
} // function print list

// deletes the list of bike kv-nodes
int deleteList(bike_node_t* inHead) {
    if (inHead == NULL){
        return -1;
    }
    bike_node_t* itr = inHead;
    bike_node_t* itrNext = NULL;
    while(itr != NULL){
        itrNext = itr->next;
        deleteNode(itr);
        itr = itrNext;
    }
    return 1;
}

// insert front
int insertFront(bike_node_t** inHeadPtr, bike_kvpair_t* inKVpair) {
    if (inHeadPtr == NULL) {
        return -1;
    }

    bike_node_t* newNode = createNode(inKVpair);
    if (newNode == NULL) {
        return -1;
    }

    newNode->next = *inHeadPtr;
    *inHeadPtr = newNode;
    return 1;
} // function insertfront



// insert at the back
int insertRear(bike_node_t** inHeadPtr, bike_kvpair_t* inKVpair){
    bike_node_t* p = NULL;
    bike_node_t* q = NULL;

    bike_node_t* tempNode = createNode(inKVpair);

    // INSERT NODE INTO EMPTY LIST
    if (listEmpty(*inHeadPtr)){
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

// 6. insert(int pos)
// Position starts from 1 to length of list + 1.
int insert(bike_node_t** inHeadPtr, int position, bike_kvpair_t* inKVpair){
    // int tempNum = 0;
    // int statusNum = -1;
    int numNodes = 0;
    int curLocation = 0;
    bike_node_t* p = NULL;
    bike_node_t* q = NULL;
    // bike_node_t* r = NULL;
    bike_node_t* tempNode;

    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL) {
        return -1;
    }//IF
    else {
        numNodes = listLength(*inHeadPtr);

        //CASE 1:  emptyList or POS==1
        if (listEmpty(*inHeadPtr) || position==1) {
            insertFront(inHeadPtr, inKVpair);
            return 1;
        }
        // CASE 2:  USER SPECIFIES POSITION GREATER THAN LISTSIZE
        else if (position > numNodes)  {
            insertRear(inHeadPtr, inKVpair);
            return 1;
        }//ELSE IF user specified POS > size
        // CASE 3:  MIDDLE OF THE LIST
        // (1) create new node (2) find spot (3) anchor q at spot (4) attach
        //      LHS of list TO new node, (4) attach the new node to RHS of list
        else {
            tempNode = createNode(inKVpair);
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

// delete front
int deleteFront(bike_node_t** inHeadPtr) {
    // inHeadPtr == NULL: no address to pointer
    // *inheadPtr == NULL: no address to node (empty list)
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }

    bike_node_t* tempNode = NULL;
    if (listLength(*inHeadPtr) == 1) {
        tempNode = *inHeadPtr;
        *inHeadPtr = NULL;
        // free(tempNode);
        deleteNode(tempNode);
        return 1;
    } // if one element in list
    else {
        tempNode = *inHeadPtr;
        *inHeadPtr = tempNode->next;
        // free(tempNode);
        deleteNode(tempNode);
        return 1;
    }
} // function delete front

// delete rear
int deleteRear(bike_node_t** inHeadPtr) {
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }

    bike_node_t* tempNode = *inHeadPtr;
    int num = listLength(*inHeadPtr);
    if (num == 1) {
        tempNode = *inHeadPtr;
        *inHeadPtr = NULL;
        // free(tempNode);
        deleteNode(tempNode);
        return 1;
    } else {
        bike_node_t* itr = *inHeadPtr; 
        bike_node_t* itrNext = itr->next;
        bike_node_t* itrNextNext = itrNext->next;
        while(itrNextNext != NULL) {
            itr = itrNext;
            itrNext = itrNextNext;
            itrNextNext = itrNextNext->next;
        } //while
        itr->next = NULL;
        // free(itrNext);
        deleteNode(itrNext);
        return 1;         
    } // else
} // function deleterear

// delete from pos
// Pos starts at 1 to length
int delete(bike_node_t** inHeadPtr, int position) {
    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }//IF

    if (position < 1){
        return -1;
    } // check for 0 or negative pos values

    int numLen = listLength(*inHeadPtr);

    if(numLen == 1 || position == 1) {
        return deleteFront(inHeadPtr);
    } // if delete from first position
    else if(position >= numLen) {
        return deleteRear(inHeadPtr);
    } // if delete last element or greater
    else {
        bike_node_t* itr = *inHeadPtr;
        int currentLocation = 1;
        while (currentLocation < position - 1) {
            itr = itr->next;
            currentLocation++;
        }
        bike_node_t* tempNode = itr->next;
        itr->next = tempNode->next;
        return deleteNode(tempNode);
    }
}

int listEmpty(bike_node_t* inHead) {
    if (inHead == NULL) {
        return 1;
    } else {
        return 0;
    }
} // function empty_list

// returns first pos of an element, starts at 1
int findItem(bike_node_t* inHead, int item) {
    if (inHead == NULL) {
        return -1;
    }

    bike_node_t* itr = inHead;
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
} // function findItem

// deleteItem. deletes first appeareance of an item. returns 1 if deleted, -1 if not found.
int deleteItem(bike_node_t** inHeadPtr, int item){
    // VERIFY inHeadPtr IS NOT NULL
    if (inHeadPtr == NULL || *inHeadPtr == NULL) {
        return -1;
    }//IF

    int pos = findItem(*inHeadPtr, item);
    if (pos < 1){
        return -1;
    } else {
        return delete(inHeadPtr, pos);
    } 
}

// returns the value (bike_t) based on a given key. NULL if doesnt exist
bike_t* getValue(bike_node_t* inHead, int key) {
    if (inHead == NULL) {
        return NULL;
    }
    bike_node_t* itr = inHead;
    // itr through list
    while (itr != NULL) {
        if (itr->data->key == key) {
            return itr->data->value;
        }
        itr = itr->next;
    } //while
    // if not found return 0.
    return NULL;   
} // function getValue

/* ************** Populate List Functions ****************** */

char* getFileName() {
      char* str = (char*)malloc((sizeof(char)*50));
      printf("Enter file name: ");
      scanf("%s", str);
      return str;
} // function getFileName

bike_t* parseLine(char inLine[300]) {
        int   temp_serialNum = 0;
        char  temp_manufacturer[12]="            ";
        char  temp_model[12]="            ";
        int   temp_manufacturedYear = 0;
        int   temp_possessionStatus = 0;
        char  temp_owner[12] = "           ";

        // CREATE A NEW bike_t
        bike_t* cR = (bike_t*)malloc(sizeof(bike_t));

        // EXTRACT THE DATA FROM THE FORMAL PARAMETER inLine
        sscanf(inLine, " %d %s %s %d %d %s ", &temp_serialNum, temp_manufacturer, temp_model, &temp_manufacturedYear, &temp_possessionStatus, temp_owner);
        
        // INSTANTIATE THE NEW STRUCT WITH EXTRACTED DATA
        cR->serialNum = temp_serialNum;
        cR->manufacturedYear = temp_manufacturedYear;
        cR->possessionStatus = temp_possessionStatus;
        
        cR->manufacturer = (char*)malloc(sizeof(char)*20);
        cR->model = (char*)malloc(sizeof(char)*20);
        strcpy(cR->manufacturer, temp_manufacturer);
        strcpy(cR->model, temp_model);

        cR->owner = createOwnerList();
        // Splitting owner string into tokens, deliminatted by '-'
        char * token = strtok(temp_owner, "-");
        // loop through the string to extract all other tokens
        while( token != NULL ) {
            insertOwnerRear(&(cR->owner), token); //adding each token
            token = strtok(NULL, "-");
        }
        yearTableInsertKey(cR->manufacturedYear, cR->serialNum);

       // RETURN A POINTER TO THE NEWLY CREATED AND 
       //        INSTANTIATED bike_t struct 
        return cR;

}// function PARSELINE

int populateList(bike_node_t** inHeadPtr){

    bike_t*   tempCR = NULL;
    bike_kvpair_t*      tempKV = NULL;

    FILE *fp;
    char* fileName = getFileName();
    char inLine[300];

    // OPEN PHYSICAL FILE FOR INPUT
    fp = fopen(fileName, "r");  

    // INITIALIZE POSITION OF LOGICAL FILE HANDLE
    rewind(fp);
    // READ FILE INTO BUFFER AND PARSE BUFFER
    if (fp) {
        while (!feof(fp)) {
            fgets(inLine, 300, fp); //inLine = a line
            inLine[strlen(inLine)] = '\0';

            if (strlen(inLine) > 50) {
                tempCR = parseLine(inLine); // Create a bike record
                if (tempCR != NULL) {
                    tempKV = getKVpair(tempCR); // add CR to kv pair
                    insertRear(inHeadPtr, tempKV); // add CR to list
                } //if
            } // if length
            else{
                    break;
            } // else
        } //while
    }  // if not open
    fclose(fp);
    return 1;
}// FUNCTION READFILE

// Writes the list of bikeRecs into a file
void writeBikeList(FILE *fp, bike_node_t* inHead) {
    if (inHead == NULL) {
        return;
    }
    bike_node_t* itr = inHead;
    while(itr != NULL) {
        writeBikeRec(fp, itr->data->value);
        itr = itr->next;
    }
}

/* ***************************************************** */

/* ***************************************************** */
/*                   KV-Pair Functions                   */
/* ***************************************************** */

// creates a key-value pair from a bike_t using serial num
bike_kvpair_t* getKVpair(bike_t* inCust) {
    bike_kvpair_t* newKVpair = (bike_kvpair_t*) malloc(sizeof(bike_kvpair_t));

    newKVpair->key = inCust->serialNum;
    newKVpair->value = inCust;
    return newKVpair;
} // get kv pair

// prints the given kv-pair
void printKVpair(bike_kvpair_t* inPair) {
    printf("---- Key-Value Pair ----\n");
    printf("KEY:    %d\n", inPair->key);
    printf("VALUE: \n");
    printBikeRec(inPair->value);
} // print kv pair

// function that frees KVPair
int deleteKVpair(bike_kvpair_t* inKVpair) {
    if (inKVpair == NULL) {
        return -1;
    }
    free(inKVpair);
    return 1;    
} // function delete kv

/* ***************************************************** */
/*                   BikeRec Functions                   */
/* ***************************************************** */

// Function to get an inputted string from the user
char* getString(int length) {
    char* tempString = (char*)malloc(sizeof(char)*length);
    printf("Enter string (max %d characters): ", length);
    scanf("%s", tempString);
    return tempString;
} //getString()

// Function to get an inputted bike_t from the user
bike_t* getBike() {
    bike_t* newCustRec = (bike_t*)malloc(sizeof(bike_t));

    printf("Serial Number -- ");
    scanf("%d", &(newCustRec->serialNum));

    printf("Manufacturer -- ");
    newCustRec->manufacturer = getString(20);

    printf("Model -- ");
    newCustRec->model = getString(13);

    printf("Manufactured Year -- Enter: ");
    scanf("%d", &(newCustRec->manufacturedYear));

    int tempStatus = 4;
    while (tempStatus > 3 || tempStatus < 0) {
        printf("Possession Status -- Enter number : (1) With Onwer, (2) Missing, (3) Stolen\n ");
        scanf("%d", &tempStatus);
        if (tempStatus > 3 || tempStatus < 0) {
            printf("Invalid option.\n");
        }
    }
    newCustRec->possessionStatus = tempStatus-1;

    printf("Owner -- ");
    char* tempOwner = getString(20);
    newCustRec->owner = createOwnerList();
    insertOwnerFront(&(newCustRec->owner), tempOwner);

    // update db index table
    yearTableInsertKey(newCustRec->manufacturedYear, newCustRec->serialNum);
    return newCustRec;    
} //getBike()

// Prompts user to select a field from BikeRec to update. Then updates that field.
// Updating serial num not supported
int updateBike(bike_t** inBike, int choice) {
    int tempStatus = 4;
    int tempYear = 0;
    switch (choice)
    {
    case (1):
        printf("Manufacturer -- ");
        (*inBike)->manufacturer = getString(20);
        break;
    case (2):
        printf("Model -- ");
        (*inBike)->model = getString(20);
        break; 
    case (3):
        printf("Manufacturered Year -- ");
        scanf("%d", &tempYear);
        // update db index table
        updateYearfromYearHashTable((*inBike)->manufacturedYear, (*inBike)->serialNum, tempYear);
        (*inBike)->manufacturedYear = tempYear;
        break;
    case (4):
        while (tempStatus > 3 || tempStatus < 0) {
            printf("Possession Status -- Enter number : (1) With Onwer, (2) Missing, (3) Stolen\n ");
            scanf("%d", &tempStatus);
            if (tempStatus > 3 || tempStatus < 0) {
                printf("Invalid option.\n");
            }
        }
        (*inBike)->possessionStatus = tempStatus -1;
        break;
    case (5):
        printf("Owner -- ");
        char* tempString = getString(20);
        insertOwnerFront(&((*inBike)->owner), tempString);
        break;
    default:
        return 0;
    }
    return 1;
}

// Function that prints a bike record
void printBikeRec(bike_t* inBike)  {
    printf("---- Bike Record ----\n");
    printf("Serial Num:               %d\n", inBike->serialNum);
    printf("Manufacturer:     %s\n", inBike->manufacturer);
    printf("Model:     %s\n", inBike->model);
    printf("Manufactured Year:             %d\n", inBike->manufacturedYear);
    switch (inBike->possessionStatus) {
        case (WITHOWNER):
            printf("Possession Status:     With Owner\n");
            break;    
        case (MISSING):
            printf("Possession Status:     Missing\n");
            break;   
        case (STOLEN):
            printf("Possession Status:     Stolen\n");
            break;    
        default:
        break;
    }
    printf("Owner(s):\n");
    printOwnerList(inBike->owner);
    printf("\n");
} //printBikeRec();

// Writes the Bike Rec into a file
void writeBikeRec(FILE *fp, bike_t* inBike) {
    if (inBike == NULL) {
        return;
    }
    fprintf(fp, "%d ", inBike->serialNum);
    fprintf(fp, "%s ", inBike->manufacturer);
    fprintf(fp, "%s ", inBike->model);
    fprintf(fp, "%d ", inBike->manufacturedYear);
    fprintf(fp, "%d ", inBike->possessionStatus);
    writeOwnerList(fp, inBike->owner);
    fprintf(fp, "\n");
}
// function that frees CR
int deleteBikeRec(bike_t* inRec) {
    if (inRec == NULL) {
        return -1;
    }
    // update db index table
    deleteSerialNumFromYearHashTable(inRec->manufacturedYear, inRec->serialNum);
    free(inRec->manufacturer);
    free(inRec->model);
    deleteOwnerList(inRec->owner);
    free(inRec);
    return 1;    
} // function dlete cr

/* ***************************************************** */
/*                   Hash Map Functions                  */
/* ***************************************************** */

// Computes the array index for a given integer
int computeHashIndex(int key, int numBuckets){
    return ((key % 10) * 10000) % numBuckets;
}//FUNCTION COMPUTEHASHINDEX

// Checks if the hash map has a given key (serial num)
int hasKey(int key) {
    int hashIndex = computeHashIndex(key, NUMBBIKEBUCKETS);
    int findStatus = findItem(bikeHashMapArray[hashIndex], key);
    return findStatus;
}// FUNCTION HASKEY

// inserts a given bikeRec given it's serialNum(key)
int insertKey(int key, bike_t* bikeRec){
    // int hashIndex = hasKey(key);
    // If key not found at hash index
    if (hasKey(key) < 1) {
        int hashIndex = computeHashIndex(key, NUMBBIKEBUCKETS);
        // add to linked-list at hash index
        bike_kvpair_t* tempKV = getKVpair(bikeRec);
        insertRear(&bikeHashMapArray[hashIndex], tempKV);
        return 1;
    } else {
        // key already in list at index
        return 0;
    }
}//FUNCTION INSERTKEY

// Removes a bikeRec from the hash map given it's serial number(key)
int deleteKey(int key){
    int hashIndex = computeHashIndex(key, NUMBBIKEBUCKETS);
    return deleteItem(&bikeHashMapArray[hashIndex], key);
}//FUNCTION DELETEKEY

// Prints the entire contents of one cell of the array
void printBucket(int bucketNumber){
    printList(bikeHashMapArray[bucketNumber]);
}//function PRINTBUCKET

// Prints the entire hash map
void printHashMap(){
    int i;
    for (i = 0; i < NUMBBIKEBUCKETS; i++) {
        printf("******************\n");
        printf("Bucket %d is now:\n", i);
        printBucket(i);
        printf("\n\n");
    }
}//function PRINTHASHMAP

int populateHash() {
    bike_t*   tempCR = NULL;
    bike_kvpair_t*      tempKV = NULL;

    FILE *fp;
    char* fileName = getFileName();
    char inLine[300];

    // OPEN PHYSICAL FILE FOR INPUT
    fp = fopen(fileName, "r");  

    // INITIALIZE POSITION OF LOGICAL FILE HANDLE
    rewind(fp);
    // READ FILE INTO BUFFER AND PARSE BUFFER
    if (fp) {
        while (!feof(fp)) {
            fgets(inLine, 300, fp); //inLine = a line
            inLine[strlen(inLine)] = '\0';

            // if (strlen(inLine) > 50) {
                tempCR = parseLine(inLine); // Create a bike record
                if (tempCR != NULL) {
                    insertKey(tempCR->serialNum, tempCR);
                } //if
            // } // if length
            // else{
                    // break;
            // } // else
        } //while
    }  // if not open
    fclose(fp);
    return 1;
}//function POPULATEHASH

// Writes the hash map into a file
void writeHashMap(char* filename) {
    int i;
    FILE* fp;
    fp = fopen(filename, "w"); // relative
    for (i = 0; i < NUMBBIKEBUCKETS; i++) {
        writeBikeList(fp, bikeHashMapArray[i]);
    }
}

// loads the hash, meant for when loading the program
// works similiarly to populateHash()
int loadHashAtStartup() {
    bike_t*   tempCR = NULL;
    bike_kvpair_t*      tempKV = NULL;

    FILE *fp;
    char inLine[300];

    // OPEN PHYSICAL FILE FOR INPUT
    fp = fopen(DATABASEFILENAME, "r");  

    // check if files doesnt exist
    if (fp == NULL) {
        // create file
        fp = fopen(DATABASEFILENAME, "a"); // open for append
        return 0;
    }

    // check if file is empty
    fseek (fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        return 0;
    }

    // INITIALIZE POSITION OF LOGICAL FILE HANDLE
    rewind(fp);
    // READ FILE INTO BUFFER AND PARSE BUFFER
    if (fp) {
        while (!feof(fp)) {
            fgets(inLine, 300, fp); //inLine = a line
            inLine[strlen(inLine)] = '\0';

            // if (strlen(inLine) > 50) {
                tempCR = parseLine(inLine); // Create a bike record
                if (tempCR != NULL) {
                    insertKey(tempCR->serialNum, tempCR);
                } //if
            // } // if length
            // else{
                    // break;
            // } // else
        } //while
    }  // if not open
    fclose(fp);
    return 1;
}

// can also be called accessKey(key)
bike_t* findBikeRecord(int key) {
    if (hasKey(key) < 1) {
        return NULL;
    } else {
        int hashIndex = computeHashIndex(key, NUMBBIKEBUCKETS);
        return getValue(bikeHashMapArray[hashIndex], key);
    }
} // function findCustomerRec

// Given a serial number (key), adds a new owner to the owner field of that entry
int insertOwnertoHashTable(int serialNum, char* owner) {
    int hashIndex = computeHashIndex(serialNum, NUMBBIKEBUCKETS);
    int findStatus = findItem(bikeHashMapArray[hashIndex], serialNum);

    if (findStatus > 0) {
        bike_t* tempBike = findBikeRecord(serialNum);
        insertOwnerFront(&(tempBike->owner), owner);
        return 1;
    } else {
        printf("Bike not found while inserting owner.\n");
        return 0;
    }
}

// Remove and add if found. if not found return 0;
int updateBikeKey(int oldKey, bike_t* newBikeRec) {
    if (hasKey(oldKey) < 1) {
        printf("Key not found while updating Serial Number.\n");
        return 0;
    }
    deleteKey(oldKey);
    insertKey(newBikeRec->serialNum, newBikeRec);
}

/****************************************************************/
int sizeOfHashMap(){

   int sizeSoFar = 0;

   // COMPUTE AND ADD SIZE OF ALL BUCKETS
   int i;
   for (i = 0; i < NUMBBIKEBUCKETS; i++){
         sizeSoFar = sizeSoFar + listLength(bikeHashMapArray[i]);
   }//FOR
   return sizeSoFar;

}// function SIZEOFHASHMAP

