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
	char blockHash[HASH_SIZE + 1];	//TODO on hash kwa ?
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
 * Initialise la struct interne BlockList avec le block genesis
 */
BlockList initBlockList() {
	BlockList bl = (BlockList) malloc(sizeof(struct etBlockList));
	char *genesis[] = {"genesis block"};
	bl->block = genBlock(0,1,genesis,"0", DIFFICULTY);
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
 * Ajoute un block à la blockChain
 */
void addBlockToBlockChain(BlockChain bc, Block b) {
	bc->lastBlockList->next = genBlockList(b);
	bc->lastBlockList = bc->lastBlockList->next;
	++bc->nbBlocks;
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
 * Vérifie sur un hash de block vérifie la difficulté
 */
bool isMiningFinished(char* hash, int difficulte){
	for (int i = 0; i < difficulte; ++i) {
		if (hash[i] != '0') return false;
	}
	return true;
}

/*
 * Mine le contenue du Block jusqu'à ce qu'il valide la difficulté et set les valeurs dans le block
 */
void setBlockHash(Block b, int difficulte){
	char blockHash[HASH_SIZE + 1];
	char blockPreHash[TAILLE_BLOCK_PREHASH];
	unsigned int nonce = 0;
	do{// Minning du block
		//TODO Faire la concaténations de champs quand on connaitra le format du blockhash
		sha256ofString((BYTE *) blockPreHash, blockHash);
		++nonce;
	} while(!isMiningFinished(blockHash, difficulte));
	strcpy(b->blockHash, blockHash);
	b->nonce = --nonce;
}

/*
 * genere un Block (avec calcul de la merkle root)
 */
Block genBlock(int index, int nbTransactions, char **transactions, char *previousHash, int difficulte){ //TODO ajouter difficulté, calcul de la nonce, du hash (?)
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
	//setBlockHash(b, difficulte);// en commentaire tant qu'on sais pas comment faire un block hash

	return b;
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
