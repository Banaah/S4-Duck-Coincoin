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

#include "merkleroot.h"
#include "sha256_utils.h"

typedef struct etBlock *Block;

bool isBlockValid(Block b);
Block genBlock(int index, int nbTransactions, char **transactions, Block previousBlock, int difficulte);
Block genGenesisBlock();
void afficherBlock(Block b);
void freeBlock(Block b);

#endif //C_BLOCK_H