//
// Created by Francois on 26/03/2018.
//
#ifndef C_BLOCK_H
#define C_BLOCK_H

#define HASH_SIZE 256
#define TIMESTAMP_SIZE 25
#define TRANSACTION_SIZE 22
#define NB_MAX_TRANSACTION 100

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../utils/json.h"
#include "merkleroot.h"
#include "../utils/sha256_utils.h"

/* -------------------------- STRUCTURE --------------------------- */

typedef struct etBlock *Block;

/* ---------------------------------------------------------------- */
/* -------------------------- GENERATION -------------------------- */

Block genBlock(int index, int nbTransactions, char **transactions, Block previousBlock, int difficulte);
Block genGenesisBlock();
void setBlockHash(Block b, int difficulte);

/* ---------------------------------------------------------------- */
/* --------------------------- CHEATER ---------------------------- */

void setTransactions(Block b, char **newTransactions, int nbNewTransactions);
void setIndex(Block b, int index);
void setPreviousHash(Block b, Block previous);

/* ---------------------------------------------------------------- */
/* ---------------------------- JSON ------------------------------ */

void blockToJson(FILE* fd, Block b);
Block blockFromJsonObject(json_value* value,Block previousBlock);

/* ---------------------------------------------------------------- */
/* ---------------------------- UTILS ----------------------------- */

void afficherBlock(Block b);
void freeBlock(Block b);
char **getTransactions(Block b, int *nb);
bool isBlockValid(Block b);
int getIndex(Block b);

/* ---------------------------------------------------------------- */
#endif //C_BLOCK_H
