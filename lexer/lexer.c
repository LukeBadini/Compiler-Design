// The lexical analyzer for the C-- Programming Language
// TODO: you are welcome to completely wipe out the contents of this
// file and start from scratch

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"


// these are likely values that will be needed by the parser, so 
// making them global variables is okay
char lexbuf[MAXLEXSIZE];  // stores current lexeme
int  tokenval=0;          // stores current token's value
                          // (may not used for every token)
int  src_lineno=0;        // current line number in source code input

char *tokenStrings[37] = {"STARTTOKEN", "NUM", "PLUS", "MINUS", "MULT", "DIV", 
                          "NOT", "LESS", "GREATER", "LE", "GE", "AND", "OR",
                          "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LBRACK",
                          "RBRACK", "LBRACE", "RBRACE", "ASSIGN", "EQ", "NOTEQ",
                          "INT", "CHAR", "IF", "ELSE", "WHILE", "BREAK", "RETURN",
                          "READ", "WRITE", "WRITELN", "ID", "DONE", "ENDTOKEN"};

// function prototypes:
//static void print_lineno();  // static limits its scope to only in this .c file
static void newLine();
static int number(int x, FILE *fd);
static int character(FILE *fd);
static void getSpecialChara(int y);
static int determineSlash(FILE *fd);
static int lessThan(FILE *fd);
static int greaterThan(FILE *fd);
static int ampersand(FILE *fd);
static int orLine(FILE *fd);
static int assignOrEQ(FILE *fd);
static int notOrNOTEQ(FILE *fd);
static int idCheck(FILE *fd, int c);
static int keywordCheck(int x, FILE *fd, int c);
static int breakCheck(FILE *fd, int c);
static int charCheck(FILE *fd, int c);
static int elseCheck(FILE *fd, int c);
static int iCheck(FILE *fd, int c);
static int rCheck(FILE *fd, int c);
static int wCheck(FILE *fd, int c);

/***************************************************************************/
/* 
 *  Main lexer routine:  returns the next token in the input 
 *
 *  param fd: file pointer for reading input file (source C-- program)
 *            TODO: you may want to add more parameters
 *
 *  returns: the next token or 
 *           DONE if there are no more tokens 
 *           LEXERROR if there is a token parsing error 
 */
int lexan(FILE *fd) {

  // here is an example of how to use the debug macros defined in lexer.h
  //   uncomment #define DEBUG_LEXER, and recompile to see debug output 
  //   comment #define DEBUG_LEXER, and recompile to see debug output 
  //
  lexer_debug0("in lexan\n");
  lexer_debug1("in lexan, lineno = %d\n", src_lineno);
  lexer_debug1("in lexan, message = %s\n", "hello there");

/* // bogus code:
  if(src_lineno < 5) {
    src_lineno++;
    return IF;
  }
  print_lineno();
  return DONE;*/

  while (1) {
    int current = fgetc(fd);
    memset(lexbuf, 0, sizeof lexbuf);

    if (current == ' ' || current == '\t') {
      
    }
    else if (current == '\n') {
      newLine();
    }
    else if (isdigit(current)) {
      return number(current, fd);
    }
    else if (current == '\'') {
      return character(fd);
    }
    else if (current == '+') {
      return PLUS;
    }
    else if (current == '-') {
      return MINUS;
    }
    else if (current == '*') {
      return MULT;
    }
    else if (current == '/') {
      return determineSlash(fd);
    }
    else if (current == '<') {
      return lessThan(fd);
    }
    else if (current == '>') {
      return greaterThan(fd);
    }
    else if (current == '&') {
      return ampersand(fd);
    }
    else if (current == '|') {
      return orLine(fd);
    }
    else if (current == ';') {
      return SEMICOLON;
    }
    else if (current == ',') {
      return COMMA;
    }
    else if (current == '(') {
      return LPAREN;
    }
    else if (current == ')') {
      return RPAREN;
    }
    else if (current == '[') {
      return LBRACK;
    }
    else if (current == ']') {
      return RBRACK;
    }
    else if (current == '{') {
      return LBRACE;
    }
    else if (current == '}') {
      return RBRACE;
    }
    else if (current == '=') {
      return assignOrEQ(fd);
    }
    else if (current == '!') {
      return notOrNOTEQ(fd);
    }
    else if (current == '_') {
      lexbuf[0] = current;
      return idCheck(fd, 1);
    }
    else if (isalpha(current)) {
      lexbuf[0] = current;
      return keywordCheck(current, fd, 1);
    }
    else if (current == EOF) {
      return DONE;
    }
    // else {
    //   tokenval = NONE;
    //   printf("token test\n");
    //   return current;
    // }
  }
}
/***************************************************************************/
// A function for demonstrating that functions should be declared static
// if they are to be used only in the file in which they are defined.
// Static limits the scope to only this .c file
/*static void print_lineno() {
  
  printf("line no = %d\n", src_lineno);

}*/
/* Method that handles new line characters */
static void newLine() {
  src_lineno = src_lineno + 1;
}

/* Method that creates tokens for NUMs */
static int number(int x, FILE *fd) {
  ungetc(x, fd);
  fscanf(fd, "%d", &tokenval);
  return NUM;
}

/* Method that creates tokens for characters (technically NUMs) */
static int character(FILE *fd) {
  int y = fgetc(fd);
  if (isalpha(y)) {
    if (fgetc(fd) == '\'') {
      tokenval = y;
      return NUM;
    }
  }
  else if (y == '\\') {
    y = fgetc(fd);
    if (isalpha(y)) {
      if (fgetc(fd) == '\'') {
        getSpecialChara(y);
        return NUM;
      }
    }
  }
  printf("Error: invalid char declaration\n");
  return LEXERROR;
}

/* Sets tokenval equal to the ASCII value associated with an
   escape sequence */
static void getSpecialChara(int y) {
  if (y == 'a') {
    tokenval = 7;
  }
  else if (y == 'b') {
    tokenval = 8;
  }
  else if (y == 'f') {
    tokenval = 12;
  }
  else if (y == 'n') {
    tokenval = 10;
  }
  else if (y == 'r') {
    tokenval = 13;
  }
  else if (y == 't') {
    tokenval = 9;
  }
  else if (y == 'v') {
    tokenval = 11;
  }
  else if (y == '\\') {
    tokenval = 92;
  }
  else if (y == '\'') {
    tokenval = 39;
  }
  else if (y == '\"') {
    tokenval = 34;
  }
  else if (y == '\?') {
    tokenval = 63;
  }
}

/* Determines if a lexeme is divide, a line comment, 
   or a block comment */
static int determineSlash(FILE *fd) {
  int x = fgetc(fd);
  /* Scans through the block comment until it
     reaches the end character */
  if (x == '*') {
    int y = fgetc(fd);
    while (y != '*') {
      if (y == '\n') {
        newLine();
      }
      y = fgetc(fd);
      if (y == '*') {
        y = fgetc(fd);
        if (y == '/') {
          return 0;
        }
      }
    }
    return 0;
  }
  /* Scans through the single-line comment until it reaches
     the new line character */
  else if (x == '/')
  {
    int y = fgetc(fd);
    while (y != '\n') {
      y = fgetc(fd);
    }
    newLine();
    return 0;
  }
  /* The / is from a divide */
  else {
    ungetc(x, fd);
    return DIV;
  }
}

/* Gets the right lexeme for LE and LESS tokens */
static int lessThan(FILE *fd) {
  int x = fgetc(fd);
  if (x == '=') {
    return LE;
  }
  else {
    ungetc(x, fd);
    return LESS;
  }
}


/* Gets the right lexeme for the GE and GREATER tokens */
static int greaterThan(FILE *fd) {
  int x = fgetc(fd);
  if (x == '=') {
    return GE;
  }
  else {
    ungetc(x, fd);
    return GREATER;
  }
}

/* Gets the right lexeme for the && token */
static int ampersand(FILE *fd) {
  int x = fgetc(fd);
  if (x == '&') {
    return AND;
  }
  else {
    ungetc(x, fd);
    perror("Error: & is an invalid operator.");
    return LEXERROR;
  }
}

/* Gets the right lexeme for the || token */
static int orLine(FILE *fd) {
  int x = fgetc(fd);
  if (x == '|') {
    return OR;
  }
  else {
    ungetc(x, fd);
    perror("Error: | is an invalid operator.");
    return LEXERROR;
  }
}

/* Method that creates tokens for EQ and ASSIGN */
static int assignOrEQ(FILE *fd) {
  int x = fgetc(fd);
  if (x == '=') {
    return EQ;
  }
  else {
    ungetc(x, fd);
    return ASSIGN;
  }
}

/* Method that creates tokens for NOTEQ and NOT */
static int notOrNOTEQ(FILE *fd) {
  int x = fgetc(fd);
  if (x == '=') {
    return NOTEQ;
  }
  else {
    ungetc(x, fd);
    return NOT;
  }
}

/* Method that creates tokens for IDs */
static int idCheck(FILE *fd, int c) {
  int x = fgetc(fd);
  int counter = c;
  while (isalnum(x) || x == '_') {
    if (counter <= MAXLEXSIZE) {
      lexbuf[counter] = x;
      x = fgetc(fd);
      counter++;
    }
    else {
      printf("Error: ID length too long.\n");
      return LEXERROR;
    }
  }
  ungetc(x, fd);
  return ID;
}

static int keywordCheck(int x, FILE *fd, int c) {
  if (x == 'b') {
    return breakCheck(fd, c);
  }
  else if (x == 'c') {
    return charCheck(fd, c);
  }
  else if (x == 'e') {
    return elseCheck(fd, c);
  }
  else if (x == 'i') {
    return iCheck(fd, c);
  }
  else if (x == 'r') {
    return rCheck(fd, c);
  }
  else if (x == 'w') {
    return wCheck(fd, c);
  }
  return idCheck(fd, c);
}

/* Checks if a lexeme starting with a "b" corresponds to
   a BREAK token */
static int breakCheck(FILE *fd, int c) {
  int x = fgetc(fd);
  if (x == 'r') {
    lexbuf[c] = x;
    c++;
    x = fgetc(fd);
    if (x == 'e') {
      lexbuf[c] = x;
      c++;
      x = fgetc(fd);
      if (x == 'a') {
        lexbuf[c] = x;
        c++;
        x = fgetc(fd);
        if (x == 'k') {
          lexbuf[c] = x;
          c++;
          x = fgetc(fd);
          if (!isalnum(x)) {
          ungetc(x, fd);
          return BREAK;
          }
        }
      }
    }
  }
  ungetc(x, fd);
  return idCheck(fd, c);
}

/* Checks if a lexeme starting with a "c" corresponds to
   a CHAR token */
static int charCheck(FILE *fd, int c) {
  int x = fgetc(fd);
  if (x == 'h') {
    lexbuf[c] = x;
    c++;
    x = fgetc(fd);
    if (x == 'a') {
      lexbuf[c] = x;
      c++;
      x = fgetc(fd);
      if (x == 'r') {
        lexbuf[c] = x;
        c++;
        x = fgetc(fd);
        if (!isalnum(x)){
          ungetc(x, fd);
          return CHAR;
        }
      }
    }
  }
  ungetc(x, fd);
  return idCheck(fd, c);
}

/* Checks if a lexeme starting with an "e" corresponds to
   an ELSE token */
static int elseCheck(FILE *fd, int c) {
  int x = fgetc(fd);
  if (x == 'l') {
    lexbuf[c] = x;
    c++;
    x = fgetc(fd);
    if (x == 's') {
      lexbuf[c] = x;
      c++;
      x = fgetc(fd);
      if (x == 'e') {
        lexbuf[c] = x;
        c++;
        x = fgetc(fd);
        if (!isalnum(x)) {
          ungetc(x, fd);
          return ELSE;
        }
      }
    }
  }
  ungetc(x, fd);
  return idCheck(fd, c);
}

/* Checks if a lexeme starting with an "i" corresponds to an
   IF or INT token */
static int iCheck(FILE *fd, int c) {
  int x = fgetc(fd);
  if (x == 'f') {
    lexbuf[c] = x;
    c++;
    x = fgetc(fd);
    if (!isalnum(x)) {
      ungetc(x, fd);
      return IF;
    }
  }
  else if (x == 'n') {
    lexbuf[c] = x;
    c++;
    x = fgetc(fd);
    if (x == 't') {
      lexbuf[c] = x;
      c++;
      x = fgetc(fd);
      if (!isalnum(x)) {
        ungetc(x, fd);
        return INT;
      }
    }
  }
  ungetc(x, fd);
  return idCheck(fd, c);
}

/* Checks if a lexeme starting with an "r" corresponds to a
   READ or RETURN token */
static int rCheck(FILE *fd, int c) {
  int x = fgetc(fd);
  if (x == 'e') {
    lexbuf[c] = x;
    c++;
    x = fgetc(fd);
    if (x == 'a') {
      lexbuf[c] = x;
      c++;
      x = fgetc(fd);
      if (x == 'd') {
        lexbuf[c] = x;
        c++;
        x = fgetc(fd);
        if (!isalnum(x)) {
          ungetc(x, fd);
          return READ;
        }
      }
    }
    else if (x == 't') {
      lexbuf[c] = x;
      c++;
      x = fgetc(fd);
      if (x == 'u') {
        lexbuf[c] = x;
        c++;
        x = fgetc(fd);
        if (x == 'r') {
          lexbuf[c] = x;
          c++;
          x = fgetc(fd);
          if (x == 'n') {
            lexbuf[c] = x;
            c++;
            x = fgetc(fd);
            if (!isalnum(x)) {
              ungetc(x, fd);
              return RETURN;
            }
          }
        }
      }
    }
  }
  ungetc(x, fd);
  return idCheck(fd, c);
}

/* Checks if a lexeme starting with a "w" corresponds to a
   WRITE or WRITELN token */
static int wCheck(FILE *fd, int c) {
  int x = fgetc(fd);
  if (x == 'h') {
    lexbuf[c] = x;
    c++;
    x = fgetc(fd);
    if (x == 'i') {
      lexbuf[c] = x;
      c++;
      x = fgetc(fd);
      if (x == 'l') {
        lexbuf[c] = x;
        c++;
        x = fgetc(fd);
        if (x == 'e') {
          lexbuf[c] = x;
          c++;
          x = fgetc(fd);
          if (!isalnum(x)) {
            ungetc(x, fd);
            return WHILE;
          }
        }
      }
    }
  }
  else if (x == 'r') {
    lexbuf[c] = x;
    c++;
    x = fgetc(fd);
    if (x == 'i') {
      lexbuf[c] = x;
      c++;
      x = fgetc(fd);
      if (x == 't') {
        lexbuf[c] = x;
        c++;
        x = fgetc(fd);
        if (x == 'e') {
        lexbuf[c] = x;
        c++;
          x = fgetc(fd);
          if (x == 'l') {
            lexbuf[c] = x;
            c++;
            x = fgetc(fd);
            if (x == 'n') {
              lexbuf[c] = x;
              c++;
              x = fgetc(fd);
              if (!isalnum(x)) {
                ungetc(x, fd);
                return WRITELN;
              }
            }
          }
          else if (!isalnum(x)) {
            ungetc(x, fd);
            return WRITE;
          }
        }
      }
    }
  }
  ungetc(x, fd);
  return idCheck(fd, c);
}