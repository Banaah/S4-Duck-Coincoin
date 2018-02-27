//
// Created by Quentin Nouvel on 16/02/2018.
// Edited by François Gaits on 19/02/2018.
//

#include <printf.h>
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

	char *hash1 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	char *hash2 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	char *concatenateHash = malloc((SHA256_BLOCK_SIZE*4 + 1) * sizeof(char));
	char *hashRes = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));

	if (hash1 == NULL || hash2 == NULL || concatenateHash == NULL || hashRes == NULL) {
		fprintf(stderr,"Issue while allocating hashes in merkleRoot()\n");
		if(hash1 != NULL) free(hash1);
		if(hash2 != NULL) free(hash2);
		if(concatenateHash != NULL) free(concatenateHash);
		if(hashRes != NULL) free(hashRes);
		return NULL;
	}
	
	if (nb == 1){
		sha256ofString((BYTE *) transactions[0], hashRes);
		return hashRes;
	}
	
	if (nb == 2){
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
		free(hash1);
		free(hash2);
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
char *getMerkleRoot(char *transactions[TAILLE_TRANSACTION], int nb){	
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

char *getMerkleRoot2(char *transactions[TAILLE_TRANSACTION], int nb){
	int taille = greaterPowOf2(nb);
	if (taille != nb){
		char *tab[taille];
		int diff = taille-nb;
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
		/*for (int i = nb; i < diff; ++i) {
			tab[i] = transactions[i-diff];
		}*/
		for (int i = 0; i < taille; ++i) {
			printf("%s ", tab[i]);
			printf("\n");
		}
		return merkleRoot2(tab, taille, 0);
	}
	return merkleRoot2(transactions, nb, 0);
}