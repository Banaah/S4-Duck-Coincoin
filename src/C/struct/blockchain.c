//
// Created by Francois on 23/02/2018.
//


#include "blockchain.h"
/*
 * Structure interne du chainage dele blockChain
 */
typedef struct etBlockList {
	Block block;
	struct etBlockList *next;
	struct etBlockList *prev;
}* BlockList;

/*
 * Synonyme pour l'utilisation d'un iterateur
 */
typedef BlockList Iterator;

/*
 * BlockChain sous la forme d'une sentinelle
 */
typedef struct etBlockChain {
	int nbBlocks;
	int difficulte;
	BlockList blockList;
	BlockList lastBlockList;
}* BlockChain;

/*
 * Generation d'un iterateur (depuis le debut)
 */
Iterator getIterator(BlockChain bc){
	return (Iterator) bc->blockList;
}

/*
 * Generation d'un iterateur (depuis la fin)
 */
Iterator getIteratorFromLast(BlockChain bc){
	return (Iterator) bc->lastBlockList;
}

Iterator next(Iterator it){
	return it->next;
}

Iterator prev(Iterator it){
	return it->prev;
}
bool isAtStart(Iterator it){
	return it==NULL;
}

bool isFinished(Iterator it){
	return it->next==NULL;
}

Block getBlockFromIterator(Iterator it){
	return it->block;
}

/*
 * Modificateurs du chainage de la bc (cheater)
 */
void iteratorSetNext(Iterator it, Iterator next){
	if(it==NULL) return;
	it->next = next;
}

/*
 * Modificateurs du chainage de la bc (cheater)
 */
void iteratorSetPrevious(Iterator it, Iterator prev){
	if(it==NULL) return;
	it->prev = prev;
}

/*
 * Verifie la validité de l'ensemble de la blockChain
 */
bool isBlockChainValid(BlockChain bc) {
	Iterator it = getIterator(bc);
	for(;!isFinished(it);it=next(it)) {
		if(!isBlockValid(getBlockFromIterator(it))) {
			printf("Block invalide\n");
			return false;
		}
	}
	if(!isBlockValid(getBlockFromIterator(it))) {
		printf("Block invalide\n");
		return false;
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
	bl->prev = NULL;
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
	while(pos!=index && pos<bc->nbBlocks-1) {
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
	bc->lastBlockList->next->prev = bc->lastBlockList;
	bc->lastBlockList = bc->lastBlockList->next;
	++bc->nbBlocks;
}

/*
 * Affiche la bc en console
 */
void afficherBlockChain(BlockChain bc) {
	int i;
	BlockList bl = bc->blockList;
	for(i=0;i<bc->nbBlocks;++i) {
		afficherBlock(bl->block);
		printf("\n");
		bl = bl->next;
	}
}

/*
 * Genere une bc complète et valide
 */
BlockChain genCompleteRandomBlockChain(int difficulte, int nbBlocks) {
	int i;
	int nbTransactions;

	BlockChain bc = initBlockChain(difficulte);
	for (i = 0; i < nbBlocks; ++i) {
		addBlockToBlockChain(bc, generateRandomTransactionsList(&nbTransactions), nbTransactions);
	}
	return bc;
}

/*
 * Convertit une blockchain en Json et l'écrit dans le fichier passé en parametre
 */
int blockChainToJson(BlockChain bc, char* filename) {
	FILE* fd = NULL;
	fd = fopen(filename,"w");
	if(fd==NULL) {
		fprintf(stderr,"Impossible d'ouvrir %s\n",filename);
		return -1;
	}

	fprintf(fd,"{\n  \"difficulty\": %d,\n  \"nbBlocks\": %d,\n  \"BC\": [\n",bc->difficulte,bc->nbBlocks);

	for(Iterator it = getIteratorFromLast(bc);!isAtStart(it);it=prev(it)) {
		blockToJson(fd,getBlockFromIterator(it));
		if(getIndex(getBlockFromIterator(it))!=0)
			fprintf(fd,",\n");
	}
	fprintf(fd,"\n  ]\n}");
	printf("Fichier enregistre !\n");
	fclose(fd);
	return 0;
}

/*
 * Positionne une barre de chargement à avancement*100%
 */
void bougerBarreDeChargement(float avancement) {
	if(avancement>1 || avancement<0) return;
	char barre[51];
	int j=0;
	int limite = (int)(avancement*50);
	while(j<51) {
		if(j<=limite) {
			barre[j] = '#';
		} else {
			barre[j] = ' ';
		}
		++j;
	}
	barre[50] = (char)0;

	printf("\r[%-50s]%d%%",barre,(int)(avancement*100));
	fflush(stdout);

}

/*
 * Generation d'une bc avec gestion de l'affichage console
 */
BlockChain genCompleteRandomBlockChainConsole(int difficulte, int nbBlocks) {
	if(nbBlocks<0) {
		fprintf(stderr,"Nombre de Blocks invalides\n");
		return NULL;
	}

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
	}
	bougerBarreDeChargement((float)1);
	printf("\n");
	return bc;
}

/*
 * Free la bc
 */
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
 * setteur pour le cheater
 */
void setNbBlock(BlockChain bc,int nbBlocks){
	bc->nbBlocks = nbBlocks;
}

int getNbBlock(BlockChain bc){
	return bc->nbBlocks;
}

int getBlockChainDifficulty(BlockChain bc){
	return bc->difficulte;
}

/*
 * garantie de l'intégrité de la structure interne de la bc pour cheater
 */
void blockChainCheckStructure(BlockChain bc, Iterator it) {
	if(bc->lastBlockList == it) {
		bc->lastBlockList = bc->lastBlockList->prev;
	} else if (bc->blockList == it) {
		bc->blockList = bc->blockList->next;
	}
}

/*
 * Cree une bc a partir d'un fichier json au format de l'exemple
 */
BlockChain blockChainFromJson(char* filename){
	FILE* fd;
	struct stat fstat;
	char* file;
	json_char* json;
	json_value* value = NULL;
	
	if(stat(filename,&fstat)!=0) {
		fprintf(stderr,"Fichier %s introuvable\n",filename);
		return NULL;
	}
	
	file = (char*)malloc(fstat.st_size);
	
	fd = fopen(filename,"r");
	
	if(fread(file,fstat.st_size,1,fd)==0) {
		fprintf(stderr,"Erreur de lecture du fichier json\n");
		return NULL;
	}
	fclose(fd);
	
	json = (json_char*)file;
	
	value = json_parse(json,fstat.st_size);
	if(value == NULL) {
		fprintf(stderr,"Erreur de parse du fichier\n");
		return NULL;
	}
	BlockChain bc = (BlockChain) malloc(sizeof(struct etBlockChain));
	bc->nbBlocks = 1;
	bc->difficulte = value->u.object.values[0].value->u.integer;
	int len = value->u.object.values[2].value->u.array.length;
	
	Block b = blockFromJsonObject(value->u.object.values[2].value->u.array.values[len-1],NULL);
	bc->lastBlockList=genBlockList(b);
	bc->blockList=bc->lastBlockList;
	
	for(int i = len-2;i>=0;--i) {
		b = blockFromJsonObject(value->u.object.values[2].value->u.array.values[i],bc->lastBlockList->block);
		if(b == NULL) {
			return NULL;
		}
		bc->lastBlockList->next=genBlockList(b);
		bc->lastBlockList->next->prev=bc->lastBlockList;
		bc->lastBlockList = bc->lastBlockList->next;
		bc->nbBlocks++;
	}
	
	json_value_free(value);
	free(file);
	
	return bc;
}
	
	
	
	
	
	
	
	
	
	
	
	
	

