#include <stdlib.h>
#include "symbolInfo.h"
#include "boolean.h"


#ifndef _LL_H
#define _LL_H

#define INIT_LENGTH 1

typedef struct listNode {
	symbolInfo symbol;
	struct listNode* next;
} node;

typedef struct {
	node* head;
	node* tail;
	int length;
} linkedList;

typedef bool (*SYMB_COMPARATOR)(symbolInfo, symbolInfo);

extern node* newNode(symbolInfo toAdd);
extern linkedList* newList(node* head);
extern void attach(linkedList* list, symbolInfo toAdd);
extern node* find(linkedList* list, symbolInfo toFind, SYMB_COMPARATOR comparator);
extern void removeNode(linkedList* list, symbolInfo toRemove);
extern void deleteNode(linkedList* list, node* toDelete);
extern void freeList(linkedList* list);
extern node* elementAt(int index, linkedList* list);


#endif