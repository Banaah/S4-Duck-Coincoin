//
// Created by Francois on 26/03/2018.
//
#include "block.h"

struct etBlock {
	int index;
	int nbTransactions;
	unsigned int nonce;
	char transactions[NB_MAX_TRANSACTION][TRANSACTION_SIZE + 1];
	char timeStamp[TIMESTAMP_SIZE + 1];
	char* previousHash;
	char merkleRoot[HASH_SIZE + 1];
	char blockHash[HASH_SIZE + 1];
};

char *genTimeStamp() {
	time_t curtime;
	time(&curtime);
	return ctime(&curtime);
}

bool isMiningFinished(const char* hash, int difficulte){
	for (int i = 0; i < difficulte; ++i) {
		if (hash[i] != '0') return false;
	}
	return true;
}

void setBlockHash(Block b, int difficulte){
	int i;
	int tailleConcat = 3 + HASH_SIZE + TIMESTAMP_SIZE + 3 +  TRANSACTION_SIZE*b->nbTransactions + HASH_SIZE + 7;
	//On reserve la mémoire pour, dans l'ordre : l'index [0-999], le hash précédent, le timestamp, le nbTransaction [0-999], les transactions, la merkle root, la nonce [0-9 999 999], et le '/0'.
	char blockHash[HASH_SIZE + 1];
	char* blockConcat = (char *) malloc(sizeof(char)*(tailleConcat + 1));
	//La meme mais sans la nonce

	char strIndex[3];
	char strNbTransactions[3];
	char strNonce[7];

	if (sprintf(strIndex,"%d",b->index) < 0) {
		perror("Erreur de conversion de l'index");
		return;
	}
	if (sprintf(strNbTransactions,"%d",b->nbTransactions) < 0) {
		perror("erreur de conversion du nombre de transactions");
		return;
	}

	//printf("DEBUG : \n\tindex : %s\n\tnbTransactions : %s\n",strIndex,strNbTransactions); // DEBUG

	strcpy(blockConcat,strIndex);
	strcat(blockConcat,b->previousHash);
	strcat(blockConcat,b->timeStamp);
	strcat(blockConcat,strNbTransactions);
	for(i=0;i<b->nbTransactions;++i) {
		strcat(blockConcat,b->transactions[i]);
	}
	strcat(blockConcat,b->merkleRoot);

	int taille = (int) strlen(blockConcat);

	unsigned int nonce = 0;
	do{
		if (sprintf(strNonce,"%d",nonce) < 0) {
			perror("erreur de conversion de la nonce");
			return;
		}

		// printf("DEBUG : \n\tnonce : %s\n",strNonce); DEBUG

		blockConcat[taille] = (char) 0;
		strcat(blockConcat,strNonce);

		sha256ofString((BYTE *) blockConcat, blockHash);
		++nonce;
	} while(!isMiningFinished(blockHash, difficulte));
	strcpy(b->blockHash, blockHash);
	b->nonce = --nonce;

	//printf("DEBUG :\n\t%s\n",blockConcat);

	free(blockConcat);
}


bool isBlockValid (Block b) {
	int i;

	char* blockPreHash = (char *) malloc(sizeof(char)*(3 + HASH_SIZE + TIMESTAMP_SIZE + 3 +  TRANSACTION_SIZE*b->nbTransactions + HASH_SIZE + 7 + 1));
	char blockHash[HASH_SIZE + 1];

	char strIndex[3];
	char strNbTransactions[3];
	char strNonce[7];

	if (sprintf(strIndex,"%d",b->index) < 0) {
		perror("Erreur de conversion de l'index");
		return false;
	}
	if (sprintf(strNbTransactions,"%d",b->nbTransactions) < 0) {
		perror("erreur de conversion du nombre de transactions");
		return false;
	}
	if (sprintf(strNonce,"%d",b->nonce) < 0) {
		perror("erreur de conversion de la nonce");
		return false;
	}

	strcpy(blockPreHash,strIndex);
	strcat(blockPreHash,b->previousHash);
	strcat(blockPreHash,b->timeStamp);
	strcat(blockPreHash,strNbTransactions);
	for(i=0;i<b->nbTransactions;++i) {
		strcat(blockPreHash,b->transactions[i]);
	}
	strcat(blockPreHash,b->merkleRoot);
	strcat(blockPreHash,strNonce);

	//printf("DEBUG valid :\n\t%s\n",blockPreHash);

	sha256ofString((BYTE *)blockPreHash,blockHash);

	free(blockPreHash);

	return strcmp(b->blockHash,blockHash) == 0;
}

Block genBlock(int index, int nbTransactions, char **transactions, Block previousBlock, int difficulte) {
	int i;
	char *timeStamp = genTimeStamp();
	char *merkleRoot = getMerkleRoot(transactions, nbTransactions);

	Block b = (Block) malloc(sizeof(struct etBlock));
	b->index = index;
	b->nbTransactions = nbTransactions;
	b->previousHash =  previousBlock->blockHash;

	for (i = 0; i < nbTransactions; ++i) {
		strcpy(b->transactions[i], transactions[i]);
	}

	strcpy(b->timeStamp,timeStamp);
	// free(timeStamp);		-> fait planter, implémentation de ctime()...
	strcpy(b->merkleRoot,merkleRoot);
	free(merkleRoot);
	setBlockHash(b, difficulte);

	return b;
}

Block genGenesisBlock() {
	char *genesis[] = {"genesis block"};
	char *timeStamp = genTimeStamp();
	char *merkleRoot = getMerkleRoot(genesis, 1);

	Block b = (Block) malloc(sizeof(struct etBlock));
	b->index = 0;
	b->nbTransactions = 1;
	b->previousHash = "0";

	strcpy(b->transactions[0],"genesis block");
	strcpy(b->timeStamp,timeStamp);
	strcpy(b->merkleRoot,merkleRoot);
	free(merkleRoot);
	setBlockHash(b, 0);

	return b;
}

void afficherBlock(Block b) {
	int i = 0;

	printf("Block n%d : \n\tNombre de transactions : %d\n\tTransactions :\n",b->index,b->nbTransactions);
	for(i=0;i<b->nbTransactions;++i){
		printf("\t\t%s\n",b->transactions[i]);
	}
	printf("\tTimestamp : %s\tHash precedent : %s\n\tMerkle root : %s\n\tNonce : %d\n\tHash du block : %s\n",b->timeStamp,b->previousHash,b->merkleRoot,b->nonce,b->blockHash);
}

void freeBlock(Block b) {
	free(b);
}

/*
 * accesseur lecture de b->merkleRoot;
 */
char *getMerkleRootFromBlock(Block b) {
	return b->merkleRoot;
}
/*
 * accesseur lecture de b->timeStamp;
 */
char *getTimeStampFromBlock(Block b) {
	return b->timeStamp;
}
/*
 * accesseur lecture de b->blockHash
 */
char *getBlockHashFromBlock(Block b) {
	return b->blockHash;
};