/*
 * Bicycle Database 
 *
 * Name:    bikeDatabaseMenu.c
 * Author:  Bryan Ang
 * E-mail:  ang.b@northeastern.edu
 * Date:    2022/07/13
 * Purpose: This file is the main driver for The Bike Records,
 *          containing the menu code for interacting and using
 *          the database system.
 */


#include <stdio.h>
#include <stdlib.h>
#include "bikeHashTable.c"

// Prints the main menu choices
void printMenu() {
    // system("clear");
    printf("\n-- Main Functions -------------------- \n");
    printf("     1 -- Find by Serial Number \n");
    printf("     2 -- Search by Year \n");
    printf("     3 -- Add Bike \n");
    printf("     4 -- Edit Bike \n");
    printf("     5 -- Remove Bike  \n");
    printf("     6 -- Add Bike(s) from a File\n");
    printf("     7 -- Export Bike to a File\n");
    printf("     8 -- Save and Quit \n");
    printf("-------------------------------------- \n");
    printf("*Diagnostic Functions:*\n");
    printf("    9 -- Print All Entries (Print Hash Map)\n");
    printf("    10 -- Print Database Index (Year)\n");
    printf("    11 -- Compute Hashkey\n");
    printf("    12 -- Export Entire Database to a File\n");
    printf("    13 -- Save Database\n");
}// function PRINTMENU

// Gets user choice from their input
int getUserChoice() {
    int tempChoice = 0;

    printMenu();
    printf("Enter choice: ");
    fflush(stdin);
    scanf("%d", &tempChoice);
    printf("\n");
    return tempChoice;

} // function GETUSERCHOICE

// Prints a sub menu where a user is given a choice of fields to update
void printUpdateRecordSubMenu() {
    printf("----------------------------------- \n");
    printf("     1 -- Manufacturer \n");
    printf("     2 -- Model \n");
    printf("     3 -- Manufactured Year\n");
    printf("     4 -- Possession Status\n");
    printf("     5 -- Add Owner\n");
    printf("----------------------------------- \n");
}

// gets user choice for a sub menu
int getUserChoiceUpdateRecordSubMenu() {
    int tempChoice = 0;

    printUpdateRecordSubMenu();
    printf("Enter choice: ");
    fflush(stdin);
    scanf("%d", &tempChoice);
    printf("\n");
    // system("clear");
    return tempChoice;
} // function GETUSERCHOICE

// Runs the main menu loop. Displays, recieves input and executes functions.
int executeMenu() {
    int tempChoice = 0;
    int myNum = 0;
    int tempNum = 0;
    int tempKey = 0;
    char myChar = '0';
    char* tempString = (char*) malloc(sizeof(char)*20);
    bike_t*  myBike;
    bike_kvpair_t*     myKV;

    tempChoice = getUserChoice();
    int statusNum = 0;
    int userPosition = 0;
    int tempHash = -1;
    
    switch (tempChoice) {

        // -------------------------------------------------------------------------
        // CASE 1:  Search by SN
       case (1): {
            printf("Enter Serial Number of BIKE TO PRINT:");
            scanf("%d",&tempKey);
            //CALL FIND AND GET
            myBike = findBikeRecord(tempKey);
            if (myBike == NULL){
                printf("Cannot ACCESS Bike %d NOT in Hash map \n", tempKey);
            }//IF
            else{
                printBikeRec(myBike);
            }//
            break;
        }//CASE 1

        // -------------------------------------------------------------------------

        // CASE 2:  Search by Manufactured Year
        case (2): {
            printf("Enter manufactured year to search: ");
            scanf("%d", &tempNum);
            bike_serialNum_node_t* listOfSerialNum = yearTableFindSerialNumNode(tempNum);
            printSerialNumList(listOfSerialNum);
            break;
        }//CASE 2  

        // -------------------------------------------------------------------------
        
        // CASE 3:  Add Bike
        case (3): {
            myBike = getBike();
            tempKey=myBike->serialNum;
            insertKey(tempKey, myBike);
            break;
        }//CASE 3  

        // -------------------------------------------------------------------------

        //CASE 4  Edit Bike 
        case (4): {
             printf("Enter Serial Number of RECORD TO update to:");
            scanf("%d",&tempKey);
            myBike = findBikeRecord(tempKey);
            if (myBike == NULL){
                printf("Record with KEY %d DOES NOT EXIST in Hash Map.\n", tempKey);
            }// RECORD EXISTS
            else{
                printf("Record found\n");
                printBikeRec(myBike);
                int subChoice = getUserChoiceUpdateRecordSubMenu();
                updateBike(&myBike, subChoice);
                printf("Updated succesfully... \n");
                printBikeRec(myBike);
            }//RECORD NOT IN HASHMAP
            break;
         }//CASE 4
        // -------------------------------------------------------------------------

         //CASE 5 DELETE Bike
         case (5): {
            printf("Enter Serial Number of the Bike to Delete:"); 
            scanf("%d",&tempKey);
            statusNum = deleteKey(tempKey);
            if (statusNum < 1) {
                printf("Error deleteing, serial number not found.\n ");
            } else {
                printf("Bike %d deleted\n", tempKey);
            }
            break;
         }//CASE 5 

        // -------------------------------------------------------------------------
        
        // CASE 6:  Add from file
        case (6): {
            populateHash();
            break;
        }//CASE 6

        // -------------------------------------------------------------------------

        // case 7: Export a bike to a file
        case (7): {
            printf("Enter Serial Number of BIKE to export:");
            scanf("%d",&tempKey);
            //CALL FIND AND GET
            myBike = findBikeRecord(tempKey);
            if (myBike == NULL){
                printf("Cannot ACCESS Bike %d NOT in Hash map \n", tempKey);
            }//IF
            else{
                printf("Bike Found. Enter filename to save as: ");
                scanf("%s", tempString);
                FILE* fptr;
                fptr = fopen(tempString, "w"); // relative
                writeBikeRec(fptr, myBike);
                printf("Write successful\n");
            }
            break;
        }//CASE 7

        // case 8: quit
        case (8): {
            printf("Saving database...\n");
            writeHashMap(DATABASEFILENAME);
            printf("Quitting now.  Bye.  \n");
            break;
        }//CASE 8
        
        // case 9: print hashmap
        case (9): {
            printHashMap();
            break;
        }//CASE 9
        
        // case 10: print year hash map
        case (10): {
            printYearHashMap();
            break;
        }//CASE 10

        // case 11: compute hashkey
        case (11): {
            printf("Enter a Serial Number:");
            scanf("%d", &tempNum);
            tempHash = computeHashIndex(tempNum, NUMBBIKEBUCKETS);
            printf("The computed Hash Bucket (Index) is: %d\n",tempHash);
            break;
        }//CASE 11

        // case 12: export db to a file
        case (12): {
            printf("Enter filename to save as: ");
            scanf("%s", tempString);
            FILE* fptr;
            fptr = fopen(tempString, "w"); // relative
            writeHashMap(tempString);
            printf("Write successful\n");
            break;
        } // CASE 12

        // case 13: save db to default file
        case (13): {
            printf("Saving...\n");
            writeHashMap(DATABASEFILENAME);
            printf("Save successful\n");
            break;
        } // CASE 13

        default: {
            printf("invalid choice ... choose again \n");
        }//DEFAULT
    } //SWITCH
    fflush(stdin);
    fflush(stdout);
    return tempChoice;

} // function EXECUTE MENU

/* ********************************************************** */

void showListADT(){

    int userChoice = -1;

    do {
        userChoice = executeMenu(); 
    } while (userChoice != 8);

} // function SHOWLISTADT

/****************************************************************/

int main() {

    //CREATE AND INSTANTIATE AN ARRAY OF LINKED LISTS
    int i;
    for (i = 0; i < NUMBBIKEBUCKETS; i++){
        bikeHashMapArray[i] = createList();
    }//FOR
    for (i = 0; i < NUMBYEARBUCKETS; i++){
        yearHashMapArray[i] = createYearKvList();
    }//FOR
    loadHashAtStartup(); // reads the db txt file
    showListADT();

    return 0;
} //MAIN