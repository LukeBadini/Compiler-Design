#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "boolean.h"


#ifndef _SYMINFO_H
#define _SYMINFO_H

typedef enum {
	CHAR_TYPE,
	INT_TYPE
} type;

typedef enum {
	FUNC_PARAM,
	GLOBAL,
	BLOCK_LOCAL,
	FOR_LOOP,
	WHILE_LOOP
} scope;

typedef struct {
	tokenT token;
	char* varName;
	type varType;
	scope curScope;
} symbolInfo;

bool equals(symbolInfo original, symbolInfo toCompare);
symbolInfo newSymbol(tokenT varToken, char* varName, scope varScope, type varType);
void destroySymbol(symbolInfo* toDestroy);

#endif