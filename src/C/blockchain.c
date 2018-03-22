//
// Created by Francois on 23/02/2018.
//


#include "blockchain.h"

typedef struct etBlock {
	int index;
	int nbTransactions;
	unsigned int nonce;
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

char *genTimeStamp() {
	time_t curtime;
	time(&curtime);
	return ctime(&curtime);
}

/*
 * Vérifie sur un hash de block vérifie la difficulté
 */
bool isMiningFinished(const char* hash, int difficulte){
	for (int i = 0; i < difficulte; ++i) {
		if (hash[i] != '0') return false;
	}
	return true;
}

/*
 * Mine le contenu du Block jusqu'à ce qu'il valide la difficulté et set les valeurs dans le block
 */
void setBlockHash(Block b, int difficulte){
	int i;
	int tailleConcat = 3 + HASH_SIZE + TIMESTAMP_SIZE + 3 +  TRANSACTION_SIZE*b->nbTransactions + HASH_SIZE + 7;
	char blockHash[HASH_SIZE + 1];
	//char* blockPreHash = (char *) malloc(sizeof(char)*(tailleConcat + 1));
	//On reserve la mémoire pour, dans l'ordre : l'index [0-999], le hash précédent, le timestamp, le nbTransaction [0-999], les transactions, la merkle root, la nonce [0-9 999 999], et le '/0'.
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

	int taille = strlen(blockConcat);

	unsigned int nonce = 0;
	do{
		if (sprintf(strNonce,"%d",nonce) < 0) {
			perror("erreur de conversion de la nonce");
			return;
		}

		// printf("DEBUG : \n\tnonce : %s\n",strNonce); DEBUG

		//strcpy(blockPreHash,blockConcat);
		blockConcat[taille] = (char) 0;
		strcat(blockConcat,strNonce);

		sha256ofString((BYTE *) blockConcat, blockHash);
		++nonce;
	} while(!isMiningFinished(blockHash, difficulte));
	strcpy(b->blockHash, blockHash);
	b->nonce = --nonce;

	printf("DEBUG :\n\t%s\n",blockConcat);

	//free(blockPreHash);
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
 * genere un Block (avec calcul de la merkle root)
 */
Block genBlock(int index, int nbTransactions, char **transactions, char *previousHash, int difficulte){
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
	setBlockHash(b, difficulte);

	return b;
}

/*
 * Initialise la struct interne BlockList avec le block genesis
 */
BlockList initBlockList() {
	BlockList bl = (BlockList) malloc(sizeof(struct etBlockList));
	char *genesis[] = {"genesis block"};
	bl->block = genBlock(0,1,genesis,"0", 0);
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
	Block b = genBlock(bc->nbBlocks,nbTransactions,transactions,bc->lastBlockList->block->blockHash,bc->difficulte);

	bc->lastBlockList->next = genBlockList(b);
	bc->lastBlockList = bc->lastBlockList->next;
	++bc->nbBlocks;
}

void afficherBlock(Block b) {
	int i = 0;

	printf("Block n%d : \n\tNombre de transactions : %d\n\tTransactions :\n",b->index,b->nbTransactions);
	for(i=0;i<b->nbTransactions;++i){
		printf("\t\t%s\n",b->transactions[i]);
	}
	printf("\tTimestamp : %s\tHash precedent : %s\n\tMerkle root : %s\n\tNonce : %d\n\tHash du block : %s\n",b->timeStamp,b->previousHash,b->merkleRoot,b->nonce,b->blockHash);
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
	}
	return bc;
}

void freeBlock(Block b) {
	free(b);
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