//
// Created by Quentin Nouvel on 16/02/2018.
//

#include "merkleroot.h"

int lesserPowOf2(int nb){
	int val = 1;
	while((val <<= 1 ) <= nb);
	val >>= 1;
	return val;
}

char *merkleRoot(char *transaction[TAILLE_TRANSACTION],int nb, int deb){
	char *hash1 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	char *hash2 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	char *concatenateHash = malloc((SHA256_BLOCK_SIZE*4 + 1) * sizeof(char));
	char *hashRes = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	if (nb && nb < 3){
		sha256ofString((BYTE *) transaction[0+deb], hash1);
		if (nb == 1) {
			sha256ofString((BYTE *) transaction[0+deb], hash2);
		} else{
			sha256ofString((BYTE *) transaction[1+deb], hash2);
		}
		strcpy(concatenateHash, hash1);
		strcat(concatenateHash, hash2);// Oui c'est possible de faire qu'avec 2 char*
		sha256ofString((BYTE *) concatenateHash, hashRes);
	} else{
		int t1, t2;
		t1 = lesserPowOf2(nb);
		t2 = nb-t1;
		hash1 = merkleRoot(transaction, t1, deb);// = première partie de l'arbre
		strcpy(concatenateHash, hash1);
		if (t2) {
			hash2 = merkleRoot(transaction, t2, deb + t1);// = deuxième partie de l'arbre
			strcat(concatenateHash, hash2);// Oui c'est possible de faire qu'avec 2 char*
		} else {
			strcat(concatenateHash, hash1);
		}
		sha256ofString((BYTE *) concatenateHash, hashRes);
	}
	free(hash1);
	free(hash2);
	free(concatenateHash);
	return hashRes;
}

char *getMerkleRoot(char *transaction[TAILLE_TRANSACTION], int nb){
	return merkleRoot(transaction, nb, 0);
}