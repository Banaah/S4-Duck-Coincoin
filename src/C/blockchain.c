//
// Created by Francois on 23/02/2018.
//


#include "blockchain.h"

typedef struct etBlock {
    int index;
    int nbTransactions;
    //int nonce;   //On verra plus tard
    char transactions[NB_MAX_TRANSACTION][TRANSACTION_SIZE + 1];
    char timeStamp[TIMESTAMP_SIZE +1 ];
    char previousHash[HASH_SIZE + 1];
    char merkleRoot[HASH_SIZE + 1];
    //char blockHash[HASH_SIZE + 1];    //on hash kwa ?
}* Block;

typedef struct etBlockList {
    Block *block;
    Block *nextBlock;
} BlockList;

typedef struct etBlockChain {
    int nbBlocks;
    int difficulte;
    BlockList blockList;
} BlockChainInterne;

char *genTimeStamp() {
    time_t curtime;
    time(&curtime);
    return ctime(&curtime);
}

Block genBlock(int index, int nbTransactions, char **transactions, char *previousHash){
    int i;
    char* timeStamp = genTimeStamp();
    char* merkleRoot = getMerkleRoot(transactions,nbTransactions);

    Block b = (Block) malloc(sizeof(struct etBlock));
    b->index = index;
    b->nbTransactions = nbTransactions;
    strcpy(b->previousHash,previousHash);

    for(i=0;i<nbTransactions;++i)
        strcpy(b->transactions[i],transactions[i]);

    strcpy(b->timeStamp,timeStamp);
    strcpy(b->merkleRoot,merkleRoot);

    return b;
}

char *getMerkleRootFromBlock(Block b) {
    return b->merkleRoot;
}

