#include "struct/blockchain.h"
#include "cheater/cheat.h"

#define INPUT_LENGTH 20


int main(){
	char input[INPUT_LENGTH];
	int indice;
	int tailleInput;
	system("clear");
	printf("Bienvenue dans l'implementation du DuckCoinCoin par la Team Belette !\n\t\tQuentin Nouvel\tFrancois Gaits\tLeo Guimas\n");
	printf("Generer une blockchain ? [o/n]\n");
	scanf("%s", input);

	if(input[0] == 'o') {
		printf("\b\bGeneration de la blockchain...\n");
		BlockChain bc = genCompleteRandomBlockChainConsole(3, 20);
		printf("Blockchain generee !\nEcrivez le numero d'un block ou \"bc\" pour l'afficher ou \"q\" pour quitter\n");
		scanf("%s", input);

		while(input[0] != 'q') {
			if(input[0] == 'b' && input[1] == 'c') {
				afficherBlockChain(bc);
			} else {
				indice = atoi(input);
				if (indice == 0 && input[0] != '0') {
					fprintf(stderr, "saisie invalide\n");
				} else {
					afficherBlock(getBlockFromBlockChain(bc, indice));
				}
			}
			printf("Ecrivez le numero d'un block ou \"bc\" pour l'afficher ou \"q\" pour quitter\n");
			scanf("%s", input);
		}

		freeBlockChain(bc);
	}

	/*BlockChain bc = genCompleteRandomBlockChain(5,12);
	afficherBlockChain(bc);
	int nbTransaction;
	double temp_cheat = cheater(bc, 2, generateRandomTransactionsList(&nbTransaction), nbTransaction);
	afficherBlockChain(bc);
	printf("%lf", temp_cheat);
	freeBlockChain(bc);*/
	return 0;
}
