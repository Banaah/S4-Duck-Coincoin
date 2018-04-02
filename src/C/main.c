#define INPUT_LENGTH 20

#include "blockchain.h"

int main(){
	char input[INPUT_LENGTH];
	int indice;

	printf("Bienvenue dans l'implementation du DuckCoinCoin par la Team Belette !\n\t\tQuentin Nouvel\tFrancois Gaits\tLeo Guimas\n");

	printf("Generer une blockchain ? [o/n]\n");

	scanf("%s",input);
	if(input[0] == 'o') {
		printf("Generation de la blockchain...\n");
		BlockChain bc = genCompleteRandomBlockChainConsole(3, 10);
		printf("Ecrivez le numero d'un block ou \"bc\" pour l'afficher ou \"q\" pour quitter\n");
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



	return 0;
}
