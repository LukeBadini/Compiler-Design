#include "linkedList.h"

#ifndef _HASHTABLE_H
#define _HASHTABLE_H

typedef struct _hash_table_t_ {
	int size;       /* the size of the table */
	linkedList** table; /* the table elements, equivalent to a two-dimension array */
} hashTable;

hashTable* create_hash_table(int size);
unsigned int hash(hashTable *table, symbolInfo toAdd);
node* hasKey(hashTable* hTable, symbolInfo toFind);
void insert(hashTable* hTable, symbolInfo key);
void freeTable(hashTable* hTable);
void removeEntry(hashTable* hTable, symbolInfo entry);

#endif