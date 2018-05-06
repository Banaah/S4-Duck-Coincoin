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
#include <sys/stat.h>

#include "../utils/json.h"
#include "../randomgen/generate_transactions.h"
#include "block.h"
/* -------------------------- STRUCTURE --------------------------- */

typedef struct etBlockChain *BlockChain;
typedef struct etBlockList* Iterator;

/* ---------------------------------------------------------------- */
/* -------------------------- ITERATEUR --------------------------- */

Iterator getIterator(BlockChain bc);
Iterator next(Iterator it);
bool isFinished(Iterator it);
Block getBlockFromIterator(Iterator it);

/* ---------------------------------------------------------------- */
/* -------------------------- GENERATION -------------------------- */

BlockChain genCompleteRandomBlockChain(int difficulte, int nbBlocks);
BlockChain genCompleteRandomBlockChainConsole(int difficulte, int nbBlocks);

/* ---------------------------------------------------------------- */
/* -------------------------- CHEATER ----------------------------- */

void iteratorSetNext(Iterator it, Iterator next);
void iteratorSetPrevious(Iterator it, Iterator prev);
void blockChainCheckStructure(BlockChain bc, Iterator it);

/* ---------------------------------------------------------------- */
/* -------------------------- JSON -------------------------------- */

BlockChain blockChainFromJson(char* filename);
int blockChainToJson(BlockChain bc, char* filename);

/* ---------------------------------------------------------------- */
/* -------------------------- UTILS ------------------------------- */

Block getBlockFromBlockChain(BlockChain bc, int index);
bool isBlockChainValid(BlockChain bc);
void afficherBlockChain(BlockChain bc);
void freeBlockChain(BlockChain bc);
void bougerBarreDeChargement(float avancement);
void setNbBlock(BlockChain bc, int nbBlocks);
int getNbBlock(BlockChain bc);
int getBlockChainDifficulty(BlockChain bc);

/* ---------------------------------------------------------------- */
#endif //C_BLOCKCHAIN_H
