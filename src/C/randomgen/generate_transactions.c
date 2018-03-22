//
// Created by Quentin Nouvel on 28/02/2018.
//

#include "generate_transactions.h"

char **generateRandomTransactionsList(int *nb){
	srand((unsigned int) time(NULL));
	char chaine[] = "Source-Destination:";
	int taille = rand()%NB_MAX_TRANSACTION; // NOLINT
	char** transactions = malloc(taille*sizeof(char));
	for (int i = 0; i < taille; ++i) {
		transactions[i] = malloc(TRANSACTION_SIZE*sizeof(char));
		for (int j = 0; j < 20; ++j) {
			transactions[i][j] = chaine[j];
		}
		transactions[i][20] = (char) (rand() % 10);// NOLINT
		transactions[i][21] = (char) (rand() % 10);// NOLINT
		transactions[i][21] = 0;
	}
	*nb = taille;
	return transactions;
}
