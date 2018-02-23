//
// Created by Francois on 23/02/2018.
//

#ifndef C_BLOCKCHAIN_H
#define C_BLOCKCHAIN_H

#define HASH_SIZE 256
#define TIMESTAMP_SIZE 24
#define TRANSACTION_SIZE 22
#define NB_MAX_TRANSACTION 100

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mem.h>

#include "merkleroot.h"
#include "sha256_utils.h"

typedef struct etBlockChain *BlockChain;
typedef struct etBlock *Block;

Block genBlock(int index, int nbTransactions, char **transactions, char *previousHash);
char *getMerkleRootFromBlock(Block b);

#endif //C_BLOCKCHAIN_H
