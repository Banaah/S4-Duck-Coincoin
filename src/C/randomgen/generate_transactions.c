//
// Created by Quentin Nouvel on 28/02/2018.
//

#include "generate_transactions.h"

char **generateRandomTransactionsList(int *nb){
	char a;

	srand((unsigned int) time(NULL));
	char chaine[] = "Source-Destination:";
	int taille = rand()%NB_MAX_TRANSACTION; // NOLINT
	char** transactions = malloc(taille*sizeof(char));
	for (int i = 0; i < taille; ++i) {
		transactions[i] = malloc(TRANSACTION_SIZE*sizeof(char));
		for (int j = 0; j < 20; ++j) {
			transactions[i][j] = chaine[j];
		}
		/* complètement contre intuitif, Quentin devrait aimer : d'abord on choisit un nombre entre 1 et 9 et ensuite entre 1 et 10
		 * si ce nombre vaut 10, alors on rajoute rien.
		 * en gros si on génère 3 et 10 ça donne :   Source-Destination:3
		 * et 2 et 5 donnent :						 Source-Destination:25
		 */
		transactions[i][19] = (char) ((char) (rand() % 9) + '1');// NOLINT
		transactions[i][20] = (char) ((a =(char) (rand() % 11)) == 10 ? 0 : a + '0');// NOLINT
		transactions[i][21] = 0;
	}
	*nb = taille;
	return transactions;
}
