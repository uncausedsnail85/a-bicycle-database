# The Bicycle Database Quick Start

## Compiling and Running

The main driver to launch the database program is found in `bikeDatabaseMenu.c`. The program also requires the following files to run:

```
bikeHashTable.c
bikeHashTable.h
bikeKeyList.c
ownerHistoryList.c
ownerHistoryList.h
yearHashTable.c
yearHashTable.h
```

To run the database would require compiling and running the compiled program. The following is one example of compiling and running on a Linux machine.

1. Ensure all files are in the same directory.
2. Open the command prompt to the directory.
3. Compile with `gcc bikeDatabaseMenu.c -o bikedatabase.c`.
4. Run with `./bikedatabase.out`.

## Using the database

The database is interacted through the console by typing commands. 

To begin, we can populate the database using the provided text file, `myBikeRecords.txt`. We can do so by selecting the right menu option (`6`) and specifying the file name.

Once that has been accomplished, the database should contain a few initial entries to interact with. We can perform various functions like accessing a record, printing the database or adding our own records. For a full list of functions, check the [User Manual.md](User%20Manual.md).

The system will create a file called `database.txt` which will be read any time the program is launched. This is where all records are stored long-term. Delete this file to reset all entries.