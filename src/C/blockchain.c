//
// Created by Francois on 23/02/2018.
//


#include "blockchain.h"

typedef struct etBlock {
	int index;
	int nbTransactions;
	unsigned int nonce;   //TODO On verra plus tard
	char transactions[NB_MAX_TRANSACTION][TRANSACTION_SIZE + 1];
	char timeStamp[TIMESTAMP_SIZE + 1];
	char previousHash[HASH_SIZE + 1];
	char merkleRoot[HASH_SIZE + 1];
	char blockHash[HASH_SIZE + 1];
}* Block;


typedef struct etBlockList {
	Block block;
	struct etBlockList *next;
}* BlockList;


typedef struct etBlockChain {
	int nbBlocks;
	int difficulte;
	BlockList blockList;
	BlockList lastBlockList;
}* BlockChain;

bool isBlockChainValid(BlockChain bc) {
	int i;
	BlockList bl = bc->blockList;
	for(i=0;i<bc->nbBlocks;++i) {
		if(!isBlockValid(bl->block)) {
			printf("Block n%d invalide\n",i);
			return false;
		}
		bl = bl->next;
	}
	return true;
}

/*
 * Initialise la struct interne BlockList avec le block genesis
 */
BlockList initBlockList() {
	BlockList bl = (BlockList) malloc(sizeof(struct etBlockList));
	bl->block = genGenesisBlock();
	bl->next = NULL;
	return bl;
}

/*
 * genere la struct interne BlockList avec un block donne
 */
BlockList genBlockList(Block b) {
	BlockList bl = (BlockList) malloc(sizeof(struct etBlockList));
	bl->block = b;
	bl->next = NULL;

	return bl;
}

/*
 * Init une BlockChain avec le block genesis
 */
BlockChain initBlockChain(int difficulte) {
	BlockChain bc = (BlockChain) malloc(sizeof(struct etBlockChain));
	bc->difficulte = difficulte;
	bc->blockList = initBlockList();
	bc->lastBlockList = bc->blockList;
	bc->nbBlocks = 1;

	return bc;
}

/*
 * renvoie le block correspondant à l'index dans la BlockChain
 */
Block getBlockFromBlockChain(BlockChain bc, int index) {
	int pos = 0;
	BlockList bl = bc->blockList;
	while(pos!=index && pos<bc->nbBlocks) {
		bl = bl->next;
		++pos;
	}
	return bl->block;
}

/*
 * Genere et rajoute un block à la blockchain
 */

void addBlockToBlockChain(BlockChain bc, char** transactions, int nbTransactions) {
	Block b = genBlock(bc->nbBlocks,nbTransactions,transactions,bc->lastBlockList->block,bc->difficulte);

	bc->lastBlockList->next = genBlockList(b);
	bc->lastBlockList = bc->lastBlockList->next;
	++bc->nbBlocks;
}



void afficherBlockChain(BlockChain bc) {
	int i;
	BlockList bl = bc->blockList;
	for(i=0;i<bc->nbBlocks;++i) {
		afficherBlock(bl->block);
		printf("\n");
		bl = bl->next;
	}
}

BlockChain genCompleteRandomBlockChain(int difficulte, int nbBlocks) {
	int i;
	int nbTransactions;
	char **transactions;

	BlockChain bc = initBlockChain(difficulte);
	for (i = 0; i < nbBlocks; ++i) {
		transactions = generateRandomTransactionsList(&nbTransactions);
		addBlockToBlockChain(bc, transactions, nbTransactions);
		freeTransac(transactions, nbTransactions);
	}
	return bc;
}

/*
 * avance une barre de chargment console a avancement (pourcentage)
 * pre : 0<=avancement<=1 
 */
void bougerBarreDeChargement(float avancement) {
	char barre[50];
	int j=0;
	int limite = (int)(avancement*50);
	while(j<50) {
		if(j<limite+1) {
			barre[j] = '#';
		} else {
			barre[j] = ' ';
		}
		++j;
	}
	
	printf("\r[%-50s]%d%%",barre,(int)(avancement*100));
	fflush(stdout);

}

BlockChain genCompleteRandomBlockChainConsole(int difficulte, int nbBlocks) {
	int i;

	float avancement = 0;
	float pas = (float)1/(2*nbBlocks);
	int nbTransactions;
	char **transactions;

	BlockChain bc = initBlockChain(difficulte);
	for (i = 0; i < nbBlocks; ++i) {
		bougerBarreDeChargement(avancement);
		avancement += pas;
		
		transactions = generateRandomTransactionsList(&nbTransactions);
		bougerBarreDeChargement(avancement);
		avancement += pas;
		
		addBlockToBlockChain(bc, transactions, nbTransactions);
		freeTransac(transactions, nbTransactions);
		
	}
	bougerBarreDeChargement(avancement);
	printf("\n");
	return bc;
}



void freeBlockChain(BlockChain bc) {
	BlockList bl = bc->blockList;
	BlockList freeBl;
	int i = 0;

	while(i<bc->nbBlocks){
		freeBl = bl;
		bl = bl->next;

		freeBlock(freeBl->block);
		free(freeBl);

		++i;
	}
	free(bc);
}

