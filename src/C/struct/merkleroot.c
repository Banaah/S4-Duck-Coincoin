//
// Created by Quentin Nouvel on 16/02/2018.
// Edited by François Gaits on 19/02/2018.
//

#include "merkleroot.h"

/*
 * params : integer nb
 * returns : power of 2 >= nb
 */
int greaterPowOf2(int nb){
	int val = 1;
	while(nb!=1&&(val <<= 1 ) < nb);
	return val;
}

/*
 * params : List of transaction, number of transaction, start of the transaction list
 * return : Hash root of the Merkle tree, NULL in case of errors
 * Internal function
 */
char *merkleRoot(char *transactions[], int nb, int deb){
	if (nb==0) {
		fprintf(stderr,"invalid number of transactions (0) in merkleRoot()\n");
		return NULL;
	}

	char *hash1 = NULL;
	char *hash2 = NULL;
	char *concatenateHash = malloc((SHA256_BLOCK_SIZE*4 + 1) * sizeof(char));
	char *hashRes = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));

	if (concatenateHash == NULL || hashRes == NULL) {
		fprintf(stderr,"Issue while allocating hashes in merkleRoot()\n");
		if(concatenateHash != NULL) free(concatenateHash);
		if(hashRes != NULL) free(hashRes);
		return NULL;
	}

	if (nb == 1){
		sha256ofString((BYTE *) transactions[0], hashRes);
		free(concatenateHash);
		return hashRes;
	}

	if (nb == 2){
		hash1 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
		hash2 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
		sha256ofString((BYTE *) transactions[0+deb], hash1);
		sha256ofString((BYTE *) transactions[1+deb], hash2);
		strcpy(concatenateHash, hash1);
		strcat(concatenateHash, hash2);
	} else if (nb > 3) {
		int t = nb >> 1;
		hash1 = merkleRoot(transactions, t, deb);// = première partie de l'arbre
		strcpy(concatenateHash, hash1);
		hash2 = merkleRoot(transactions, t, deb + t);// = deuxième partie de l'arbre
		strcat(concatenateHash, hash2);
	} else {
		fprintf(stderr,"Transaction number should be a power of 2\n");
		free(concatenateHash);
		free(hashRes);
		return NULL;
	}
	sha256ofString((BYTE *) concatenateHash, hashRes);

	free(hash1);
	free(hash2);
	free(concatenateHash);
	return hashRes;
}

/*
 * params : List of transaction, number of transaction
 * return : Hash root of the Merkle tree, NULL in case of errors
 */
char *getMerkleRoot(char *transactions[TRANSACTION_SIZE], int nb){
	int taille = greaterPowOf2(nb);
	if (taille != nb){
		char *tab[taille];
		for (int i = 0; i < nb; ++i) {
			tab[i] = transactions[i];
		}
		if (nb%2 == 0){
			for (int i = nb; i < taille; i+=2) {
				tab[i] = transactions[nb-2];
				tab[i+1] = transactions[nb-1];
			}
		} else {
			for (int i = nb; i < taille; ++i) {
				tab[i] = transactions[nb-1];
			}
		}
		return merkleRoot(tab, taille, 0);
	}
	return merkleRoot(transactions, taille, 0);
}

char *merkleRootIt(char *transactions[], int nbTransactions) {
	int i = 0;
	int nb = nbTransactions;
	char *hashRes = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));

	if(nb == 1) {
		sha256ofString((BYTE*)transactions[0],hashRes);
		return hashRes;
	}

	char concatenateHash[SHA256_BLOCK_SIZE*4 + 1];
	char **hashTab = (char**) malloc(sizeof(char*)*(nb+1)/2);
	for(i = 0;i<(nb+1)/2;++i) {
		hashTab[i] = (char *) malloc(sizeof(char)*(SHA256_BLOCK_SIZE*2 + 1));
	}

	for(i = 0;i<nb;i=i+2) {
		strcpy(concatenateHash,transactions[i]);
		strcat(concatenateHash,i+1 >= nb ? transactions[i] : transactions[i+1]);
		sha256ofString((BYTE*)concatenateHash,hashTab[i/2]);
	}

	nb = (nb+1)/2;

	while(nb != 1) {
		printf("a : %d\n",nb);
		for (i = 0; i < nb; i = i + 2) {
			strcpy(concatenateHash, hashTab[i]);
			strcat(concatenateHash, i + 1 >= nb ? hashTab[i] : hashTab[i + 1]);
			sha256ofString((BYTE*)concatenateHash,hashTab[i/2]);
		}
		nb = (nb + 1) / 2;
	}
	strcpy(hashRes,hashTab[0]);

	for(i=0;i<(nbTransactions+1)/2;++i){
		free(hashTab[i]);
	}
	free(hashTab);

	return hashRes;
}
