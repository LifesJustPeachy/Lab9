#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
};

// Combined structure for Node and HashType
struct HashNode {
    struct RecordType record;
    struct HashNode* next;
};

// Compute the hash function
int hash(int x)
{
    // Your hash function implementation here
    // For simplicity, let's use modulo division for now
    return x % 10; // Adjust 10 as needed based on the array size
}

// Insert a record into the hash table
void insertRecord(struct HashNode* hashArray[], struct RecordType record)
{
    int index = hash(record.id);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->record = record;
    newNode->next = hashArray[index];
    hashArray[index] = newNode;
}

// Display records in the hash structure
void displayRecordsInHash(struct HashNode* hashArray[], int hashSz)
{
    printf("\nRecords in Hash Structure:\n");
    for (int i = 0; i < hashSz; ++i) {
        printf("Index %d: ", i);
        struct HashNode* current = hashArray[i];
        while (current != NULL) {
            printf("(%d, %c, %d) -> ", current->record.id, current->record.name, current->record.order);
            current = current->next;
        }
        printf("NULL\n");
    }
    printf("\n");
}

// Parses input file to an array of records
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    printf("\nRecords:\n");
    for (int i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Hash table size
    const int HASH_SIZE = 10;

    // Initialize hash table
    struct HashNode* hashTable[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; ++i) {
        hashTable[i] = NULL;
    }

    // Insert records into hash table
    for (int i = 0; i < recordSz; ++i) {
        insertRecord(hashTable, pRecords[i]);
    }

    // Display records in hash structure
    displayRecordsInHash(hashTable, HASH_SIZE);

    // Free allocated memory
    free(pRecords);

    return 0;
}
