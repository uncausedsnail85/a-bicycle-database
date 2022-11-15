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


 // ---------------------------------------------------------

// The kv-pair fore the has table.
// Key: manuYear
// Value: A list of serial numbers
typedef struct year_kvpair year_kvpair_t;

 // ---------------------------------------------------------

// The linked list node for use in the hash map buckets
typedef struct year_node year_node_t;

/*
* List functions
*/
year_node_t* createYearKvNode(year_kvpair_t* inPair);
void printYearKvNode(year_node_t* inNode);
int yearKvListLength(year_node_t* inHead);
int deleteYearKvNode(year_node_t* inNode);
year_node_t* createYearKvList();
void printYearKvList(year_node_t* inHead);
int deleteYearKvList(year_node_t* inHead);
int insertYearKvFront(year_node_t** inHeadPtr, year_kvpair_t* inKVpair);
int insertYearKvRear(year_node_t** inHeadPtr, year_kvpair_t* inKVpair);
int insertYearKvatPos(year_node_t** inHeadPtr, int position, year_kvpair_t* inKVpair);
int deleteYearKvFront(year_node_t** inHeadPtr);
int deleteYearKvRear(year_node_t** inHeadPtr);
int deleteYearKvatPos(year_node_t** inHeadPtr, int position);
int yearKvListEmpty(year_node_t* inHead);
int findYearKv(year_node_t* inHead, int item);
int deleteYearKv(year_node_t** inHeadPtr, int item);
bike_serialNum_node_t* getBikeKvValue(year_node_t* inHead, int key);

/*
* KV-Pair functions (Year-listOfSerialNum pair)
*/
year_kvpair_t* getYearKVpair(int manuYear, int serialNum);
void printYearKVpair(year_kvpair_t* inPair);
int deleteYearKVpair(year_kvpair_t* inKVpair);

/*
* Hash Map functions
*/
int computeYearHashIndex(int key, int numBuckets);
int yearTableHasKey(int key);
int yearTableInsertKey(int key, int serialNum);
int yearTableDeleteKey(int key);
void yearTablePrintBucket(int bucketNumber);
void printYearHashMap();
bike_serialNum_node_t* yearTableFindSerialNumNode(int key);
int deleteSerialNumFromYearHashTable(int manuYear, int serialNum);
int updateYearfromYearHashTable(int oldYear, int serialNum, int newYear);

