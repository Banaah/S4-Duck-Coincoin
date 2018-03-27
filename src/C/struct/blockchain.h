//
// Created by Francois on 23/02/2018.
//

#ifndef C_BLOCKCHAIN_H
#define C_BLOCKCHAIN_H

#define HASH_SIZE 256
#define TIMESTAMP_SIZE 25
#define TRANSACTION_SIZE 22
#define NB_MAX_TRANSACTION 100

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../randomgen/generate_transactions.h"
#include "block.h"

typedef struct etBlockChain *BlockChain;

BlockChain genCompleteRandomBlockChain(int difficulte, int nbBlocks);

BlockChain initBlockChain(int difficulte);

void addBlockToBlockChain(BlockChain bc, char** transactions, int nbTransactions);

Block getBlockFromBlockChain(BlockChain bc, int index);

bool isBlockChainValid(BlockChain bc);

void afficherBlockChain(BlockChain bc);

void freeBlockChain(BlockChain bc);

int getNbBlock(BlockChain bc);

#endif //C_BLOCKCHAIN_H
