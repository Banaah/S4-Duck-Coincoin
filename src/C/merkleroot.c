//
// Created by Quentin Nouvel on 16/02/2018.
//

#include <printf.h>
#include "merkleroot.h"

int lesserPowOf2(int nb){
	int val = 1;
	while((val <<= 1 ) < nb);
	val >>= 1;
	return val;
}

int greaterPowOf2(int nb){
	int val = 1;
	while((val <<= 1 ) <= nb);
	return val;
}

char *merkleRoot(char *transactions[TAILLE_TRANSACTION],int nb, int deb){
	char *hash1 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	char *hash2 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	char *concatenateHash = malloc((SHA256_BLOCK_SIZE*4 + 1) * sizeof(char));
	char *hashRes = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	if (nb && nb < 3){
		sha256ofString((BYTE *) transactions[0+deb], hash1);
		if (nb == 1) {
			sha256ofString((BYTE *) transactions[0+deb], hash2);
		} else{
			sha256ofString((BYTE *) transactions[1+deb], hash2);
		}
		strcpy(concatenateHash, hash1);
		strcat(concatenateHash, hash2);// Oui c'est possible de faire qu'avec 2 char*
		sha256ofString((BYTE *) concatenateHash, hashRes);
	} else{
		int t1, t2;
		t1 = lesserPowOf2(nb);
		t2 = nb-t1;
		hash1 = merkleRoot(transactions, t1, deb);// = première partie de l'arbre
		strcpy(concatenateHash, hash1);
		if (t2) {
			hash2 = merkleRoot(transactions, t2, deb + t1);// = deuxième partie de l'arbre
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

char *merkleRoot2(char *transactions[TAILLE_TRANSACTION],int nb, int deb){
	char *hash1 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	char *hash2 = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	char *concatenateHash = malloc((SHA256_BLOCK_SIZE*4 + 1) * sizeof(char));
	char *hashRes = malloc((SHA256_BLOCK_SIZE*2 + 1) * sizeof(char));
	if (nb && nb < 3){
		sha256ofString((BYTE *) transactions[0+deb], hash1);
		if (nb == 1) {
			sha256ofString((BYTE *) transactions[0+deb], hash2);
		} else{
			sha256ofString((BYTE *) transactions[1+deb], hash2);
		}
		strcpy(concatenateHash, hash1);
		if (t2) {
			hash2 = merkleRoot(transaction, t2, deb + t1);// = deuxième partie de l'arbre
			strcat(concatenateHash, hash2);// Oui c'est possible de faire qu'avec 2 char*
		} else {
			strcat(concatenateHash, hash1);
		}
		sha256ofString((BYTE *) concatenateHash, hashRes);
	} else{
		int t = nb >> 1;
		hash1 = merkleRoot(transactions, t, deb);// = première partie de l'arbre
		strcpy(concatenateHash, hash1);
		hash2 = merkleRoot(transactions, t, deb + t);// = deuxième partie de l'arbre
		strcat(concatenateHash, hash2);// Oui c'est possible de faire qu'avec 2 char*
		sha256ofString((BYTE *) concatenateHash, hashRes);
	}
	free(hash1);
	free(hash2);
	free(concatenateHash);
	return hashRes;
}

char *getMerkleRoot(char *transactions[TAILLE_TRANSACTION], int nb){
	return merkleRoot(transactions, nb, 0);
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