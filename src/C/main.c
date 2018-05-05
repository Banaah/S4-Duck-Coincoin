#include "struct/blockchain.h"
#include "cheater/cheat.h"

#define INPUT_LENGTH 32


int main(){
	char input[INPUT_LENGTH];
	int indice;
	int difficulte;
	int nbBlocks;
	double temp_cheat;

	system("clear");
	printf("Bienvenue dans l'implementation du DuckCoinCoin par la Team Belette !\n\t\tQuentin Nouvel\tFrancois Gaits\tLeo Guimas\n");
	printf("Generer une blockchain ? [o/n]\n");
	scanf("%s", input);
	if(input[0] == 'o') {
		printf("Difficulte ? : ");
		scanf("%s", input);
		difficulte = atoi(input);
		while(difficulte <= 0 && input[0] != '0') {
			printf("Saisie invalide, ressaisir : ");
			scanf("%s", input);
			difficulte = atoi(input);
		}
		printf("Longueur ? : ");
		scanf("%s", input);
		nbBlocks = atoi(input);
		while(nbBlocks <= 0) {
			printf("Saisie invalide, ressaisir : ");
			scanf("%s", input);
			nbBlocks = atoi(input);
		}
		printf("\b\bGeneration de la blockchain...\n");
		BlockChain bc = genCompleteRandomBlockChainConsole(difficulte, nbBlocks);
		printf("Blockchain generee !\nCommandes :\n\t- x pour afficher le bloc x\n\t- \"bc\" pour afficher toute la blockchain\n\t- \"s\" pour supprimer un block (Cheater)\n\t- \"js\" pour enregistrer la chaine en json\n\t- \"q\" pour quitter\n");
		scanf("%s", input);

		while(input[0] != 'q') {
			if(input[0] == 'b' && input[1] == 'c') {
				printf("Affichage de %d blocks\n",getNbBlock(bc));
				afficherBlockChain(bc);
			} else if (input[0] == 's') {
				printf("Numero du block a supprimer : ");
				scanf("%s", input);
				indice = atoi(input);
				while (indice <= 0) {
					printf("Saisie invalide, ressaisir : ");
					scanf("%s", input);
					indice = atoi(input);
				}
				temp_cheat = cheaterDeleteBlock(bc, indice);
				printf("Block supprime ! temps : %lf\n", temp_cheat);
			} else if (input[0]=='j' && input[1]=='s') {
				printf("nom du fichier : ");
				scanf("%s",input);
				blockChainToJson(bc,input);
			} else {
				indice = atoi(input);
				if (indice == 0 && input[0] != '0') {
					fprintf(stderr, "saisie invalide\n");
				} else {
					afficherBlock(getBlockFromBlockChain(bc, indice));
				}
			}
			printf("Commandes :\n\t- x pour afficher le bloc x\n\t- \"bc\" pour afficher toute la blockchain\n\t- \"s\" pour supprimer un block (Cheater)\n\t- \"js\" pour enregistrer la chaine en json\n\t- \"q\" pour quitter\n");
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
