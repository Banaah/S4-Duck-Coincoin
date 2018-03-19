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

#include "merkleroot.h"
#include "sha256_utils.h"

typedef struct etBlockChain *BlockChain;
typedef struct etBlock *Block;

BlockChain initBlockChain(int difficulte);

void addBlockToBlockChain(BlockChain bc, char** transactions, int nbTransactions);
Block getBlockFromBlockChain(BlockChain bc, int index);

char *getBlockHashFromBlock(Block b);
char *getMerkleRootFromBlock(Block b);
char *getTimeStampFromBlock(Block b);

#endif //C_BLOCKCHAIN_H
