//
// Created by Francois on 26/03/2018.
//
#include "block.h"

#include "../utils/json.h"

/*
 * Structure du block, previousHash pointe sur le hash du bloc précédent
 */

struct etBlock {
	int index;
	int nbTransactions;
	unsigned int nonce;
	char** transactions;
	char timeStamp[TIMESTAMP_SIZE + 1];
	char* previousHash;
	char* merkleRoot;
	char blockHash[HASH_SIZE + 1];
};

/*
 * Genere une chaine de date au format (Mois Jour, Année Heure AM/PM)
 */
char *genTimeStamp() {
	char* timestamp = malloc(sizeof(char)*TIMESTAMP_SIZE);
	struct tm date;
	time_t curtime;
	time(&curtime);
	date = *localtime(&curtime);

	strftime(timestamp, sizeof(char)*TIMESTAMP_SIZE,"%b %d, %Y %X %p",&date);

	return timestamp;
}

bool isMiningFinished(const char* hash, int difficulte){
	for (int i = 0; i < difficulte; ++i) {
		if (hash[i] != '0') return false;
	}
	return true;
}

/*
 * Hash le block, initialise les champs blockHash et nonce
 */
void setBlockHash(Block b, int difficulte){
	int i;
	int tailleConcat = 5 + HASH_SIZE + TIMESTAMP_SIZE + 4 +  (1+TRANSACTION_SIZE)*b->nbTransactions + HASH_SIZE + 10;
	//On reserve la mémoire pour, dans l'ordre : l'index [0-999], le hash précédent, le timestamp, le nbTransaction [0-999], les transactions, la merkle root, la nonce [0-9 999 999], et le '/0'.
	char blockHash[HASH_SIZE + 1];
	char* blockConcat = (char *) malloc(sizeof(char)*(tailleConcat + 1));
	//La meme mais sans la nonce
	char strIndex[5];
	char strNbTransactions[4];
	char strNonce[10];

	if (sprintf(strIndex,"%d",b->index) < 0) {
		perror("Erreur de conversion de l'index");
		return;
	}
	if (sprintf(strNbTransactions,"%d",b->nbTransactions) < 0) {
		perror("erreur de conversion du nombre de transactions");
		return;
	}
	strcpy(blockConcat,strIndex);
	strcat(blockConcat,b->previousHash);
	strcat(blockConcat,b->timeStamp);
	strcat(blockConcat,strNbTransactions);
	for(i=0;i<b->nbTransactions;++i) {
		strcat(blockConcat,b->transactions[i]);
		if(i!=b->nbTransactions-1)
			strcat(blockConcat," ");
	}
	strcat(blockConcat,b->merkleRoot);

	int taille = (int) strlen(blockConcat);

	unsigned int nonce = 0;
	do{
		if (sprintf(strNonce,"%d",nonce) < 0) {
			perror("erreur de conversion de la nonce");
			return;
		}
		blockConcat[taille] = (char) 0;
		strcat(blockConcat,strNonce);

		sha256ofString((BYTE *) blockConcat, blockHash);
		++nonce;
	} while(!isMiningFinished(blockHash, difficulte));
	strcpy(b->blockHash, blockHash);
	b->nonce = --nonce;
	free(blockConcat);
}

/*
 * re-hash les champs du block et les compare au hash contenu dans le block
 */
bool isBlockValid (Block b) {
	int i;

	char* blockPreHash = (char *) malloc(sizeof(char)*(5 + HASH_SIZE + TIMESTAMP_SIZE + 4 +  (1+TRANSACTION_SIZE)*b->nbTransactions + HASH_SIZE + 7 + 1));
	char blockHash[HASH_SIZE + 1];

	char strIndex[5];
	char strNbTransactions[4];
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
		if(i!=b->nbTransactions-1)
			strcat(blockPreHash," ");
	}
	strcat(blockPreHash,b->merkleRoot);
	strcat(blockPreHash,strNonce);
	
	sha256ofString((BYTE *)blockPreHash,blockHash);

	free(blockPreHash);

	return strcmp(b->blockHash,blockHash) == 0;
}

/*
 * Genere un block complet pour les transactions données
 */
Block genBlock(int index, int nbTransactions, char **transactions, Block previousBlock, int difficulte) {
	char *timeStamp = genTimeStamp();

	Block b = (Block) malloc(sizeof(struct etBlock));
	b->index = index;
	b->nbTransactions = nbTransactions;
	b->previousHash =  previousBlock->blockHash;
	b->transactions = transactions;

	strcpy(b->timeStamp,timeStamp);
	b->merkleRoot = getMerkleRoot(transactions, nbTransactions);
	setBlockHash(b, difficulte);

	return b;
}

/*
 * Genere le block genesis
 */
Block genGenesisBlock() {
	char tr[] = "genesis block";
	char *timeStamp = genTimeStamp();

	Block b = (Block) malloc(sizeof(struct etBlock));
	b->index = 0;
	b->nbTransactions = 1;
	b->previousHash = "0";
	b->transactions = (char**) malloc(sizeof(char*));
	b->transactions[0] = (char*) malloc(14*sizeof(char));
	strcpy(b->transactions[0], tr);
	b->merkleRoot = getMerkleRoot(b->transactions, 1);

	strcpy(b->timeStamp,timeStamp);
	setBlockHash(b, 0);

	return b;
}

/*
 * Affiche le block donne en console
 */
void afficherBlock(Block b) {
	int i = 0;

	printf("Block n%d : \n\tNombre de transactions : %d\n\tTransactions :\n",b->index,b->nbTransactions);
	for(i=0;i<b->nbTransactions;++i){
		printf("\t\t%s\n",b->transactions[i]);
	}
	printf("\tTimestamp : %s\n\tHash precedent : %s\n\tMerkle root : %s\n\tNonce : %d\n\tHash du block : %s\n",b->timeStamp,b->previousHash,b->merkleRoot,b->nonce,b->blockHash);
}

/*
 * Libere les champs du block
 * Le timeStamp ne peut pas être libéré -> fuite
 */
void freeBlock(Block b) {
	free(b->merkleRoot);
	for (int i = 0; i < b->nbTransactions; ++i) {
		free(b->transactions[i]);
	}
	free(b->transactions);
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

/*
 * Changer les transactions d'un block (Cheater)
 */
void setTransactions(Block b, char **newTransactions, int nbNewTransactions){
	for (int i = 0; i < b->nbTransactions; ++i) {
		free(b->transactions[i]);
	}
	free(b->transactions);
	b->nbTransactions = nbNewTransactions;
	b->transactions = newTransactions;
}

/*
 * Ecrit un block au format Json de l'exmple dansle fichier donné
 */
void blockToJson(FILE* fd, Block b) {
	fprintf(fd,"    {\n      \"index\": %d,\n      \"previousHash\": \"%s\",\n      \"timeStamp\": \"%s\",\n      \"nbTransactions\": %d,\n      \"transactions\": [\n",b->index,b->previousHash,b->timeStamp,b->nbTransactions);
	for(int i = 0;i < b->nbTransactions;++i) {
		fprintf(fd,"        \"%s\"",b->transactions[i]);
		if(i!=b->nbTransactions-1)
			fprintf(fd,",\n");
	}
	fprintf(fd,"\n      ],\n      \"merkleRoot\": \"%s\",\n      \"blockHash\": \"%s\",\n      \"nonce\": %d\n    }",b->merkleRoot,b->blockHash,b->nonce);
}

int getIndex(Block b) {
	return b->index;
}

void setIndex(Block b, int index) {
	b->index = index;
}

void setPreviousHash(Block b, Block previous) {
	b->previousHash = previous->blockHash;
}

char **getTransactions(Block b, int *nb){
	*nb = b->nbTransactions;
	return b->transactions;
}

/*
 * Génère un block depuis un objet json parse avant.
 * Necessite un objet au bon format
 */
Block blockFromJsonObject(json_value* value, Block previousBlock) {
	Block b = (Block) malloc(sizeof(struct etBlock));
	b->index = value->u.object.values[0].value->u.integer;
	if(previousBlock!=NULL) {
		if(strcmp(value->u.object.values[1].value->u.string.ptr,previousBlock->blockHash)!=0) {
			/*Vérifie que le champ previousHash reste cohérent*/
			printf("Json corrompu !\n");
			return NULL;
		}
		b->previousHash = previousBlock->blockHash;
	} else {
		b->previousHash = "0";
	}
	strcpy(b->timeStamp,value->u.object.values[2].value->u.string.ptr);
	b->nbTransactions = value->u.object.values[3].value->u.integer;
	b->transactions = (char**) malloc(sizeof(char*)*b->nbTransactions);
	for(int i=0;i<b->nbTransactions;++i) {
		b->transactions[i] = (char*) malloc(sizeof(char)*TRANSACTION_SIZE);
		strcpy(b->transactions[i],value->u.object.values[4].value->u.array.values[i]->u.string.ptr);
	}
	b->merkleRoot = (char*) malloc(sizeof(char)*HASH_SIZE+1);
	strcpy(b->merkleRoot,value->u.object.values[5].value->u.string.ptr);
	strcpy(b->blockHash,value->u.object.values[6].value->u.string.ptr);
	
	b->nonce = value->u.object.values[7].value->u.integer;
	return b;
}
