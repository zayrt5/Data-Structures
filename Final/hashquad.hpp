using namespace std;

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    int *table;
    int numOfcolision =0;
public:
    HashTable(int bsize);  // Constructor

    // inserts a key into hash table
    bool insertKey(int key);

    // hash function to map values to key
    unsigned int hashFunction(int key);
    void recSearch(int* inArray, float* search, int numEntries);

    void printTable();
    int getNumOfCollision();

    int searchKey(int key);
};

