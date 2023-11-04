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

#include "cc-alculus/include/main.h"

INIT_CC();

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

void WASMopenBuffer(char* source) {
#ifdef __WCC_PRINTSRC__
    printf("source: %s\n", source);
#endif

#ifndef __GNUC__
    buffer = fopen("content.tmp.c", "w");
    if (buffer == NULL) perror("fopen\n");
    fputs(source, buffer);
#else
    buffer = fmemopen(source, strlen(source), "r");
#endif

    getc(buffer);
}

void init_cc() {
    // openBuffer("test.c");
    // buffer has to be opened before init

    token_sequence = (Token*)malloc(sizeof(Token) * sequence_size);
    AST            = (AST_NODE*)malloc(sizeof(AST_NODE) * AST_size);
}

void tokenize_source() {
    printf("beginning tokenization\n");
    tokenize();
}

void parse_source() {
    printf("beginning parsing\n");
    parse();
}

void clean_cc() {
    freeTokens (/* token_sequence */);
    freeAST    (AST);
    fclose     (buffer);
}
