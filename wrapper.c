#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cc-alculus/include/tokens.h"
#include "cc-alculus/include/tokenizer.h"
#include "cc-alculus/include/keywords.h"
#include "cc-alculus/include/parser.h"
#include "cc-alculus/include/stdout.h"

/* identical to main.c */

Token*    token_sequence = NULL;
size_t    sequence_size  = 10;
size_t    sequence_pos   = 0;

AST_NODE* AST            = NULL;
size_t    AST_size       = 10;
size_t    AST_position   = 0;

FILE*     buffer         = NULL;
char      active         = 0;
uint8_t   row = 1, col   = 0;

KVP keywords[] =
{
    { "int"    , TOK_INT    },
    { "void"   , TOK_VOID   },
    { "char"   , TOK_CHAR   },
    { "if"     , TOK_IF     },
    { "else"   , TOK_ELSE   },
    { "return" , TOK_RETURN },
};

uint8_t keywords_size = sizeof(keywords) / sizeof(keywords[0]);

void freeTokens() {
    for (int i = 0; i < sequence_pos; i++)
        free(token_sequence[i].value);

    free(token_sequence);
}

void freeAST(AST_NODE* node) {
    if (node == NULL) return;

    for (int i = 0; i < node->children_count; i++)
        freeAST(&node->children[i]);

    free(node->children);
    free(node);
}


/* usage
 * init_cc();
 * WASMopenBuffer("some_c_code");
 * tokenize_source();
 * parse_source();
 */

void WASMopenBuffer(char* source) {
    buffer = fopen("content.tmp.c", "w");
    fputs(source, buffer);
}

void init_cc() {
    // openBuffer("test.c");
    // buffer has to be opened before init

    token_sequence = (Token*)malloc(sizeof(Token) * sequence_size);
    AST            = (AST_NODE*)malloc(sizeof(AST_NODE) * AST_size);
}

void tokenize_source() { tokenize(); }
void parse_source()    { parse();    }

void clean_cc() {
    freeTokens (/* token_sequence */);
    freeAST    (AST);
    fclose     (buffer);
}
