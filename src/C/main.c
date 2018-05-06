#include "struct/blockchain.h"
#include "cheater/cheat.h"

#define INPUT_LENGTH 32


int main(){
	char input[INPUT_LENGTH];
	int indice;
	int difficulte;
	int nbBlocks;
	double temp_cheat;
	int ret;
	BlockChain bc = NULL;

	ret = system("clear");
	printf("Bienvenue dans l'implementation du DuckCoinCoin par la Team Belette !\n\t\tQuentin Nouvel\tFrancois Gaits\tLeo Guimas\n");
	printf("Generer une blockchain :\n\t1- Aleatoire\n\t2- Depuis un fichier Json ? \n\n\t(1/2/q) : ");
	ret = scanf("%s", input);
	if(input[0] == '1' || input[0] == '2') {
		if(input[0] == '1') {
			printf("Difficulte ? : ");
			ret = scanf("%s", input);
			difficulte = atoi(input);
			while(difficulte <= 0 && input[0] != '0') {
				printf("Saisie invalide, ressaisir : ");
				ret = scanf("%s", input);
				difficulte = atoi(input);
			}
			printf("Longueur ? : ");
			ret = scanf("%s", input);
			nbBlocks = atoi(input);
			while(nbBlocks <= 0) {
				printf("Saisie invalide, ressaisir : ");
				ret = scanf("%s", input);
				nbBlocks = atoi(input);
			}
			printf("\b\bGeneration de la blockchain...\n");
			bc = genCompleteRandomBlockChainConsole(difficulte, nbBlocks);
		} else if (input[0] == '2') {
			printf("Nom du fichier ? : ");
			ret = scanf("%s",input);
			bc = blockChainFromJson(input);
		}
		if(bc==NULL) {
			return -1;
		}
		if(!isBlockChainValid(bc)) {
			printf("Blockchain invalide !\n");
			freeBlockChain(bc);
			return -1;
		}
		printf("Blockchain generee !\nCommandes :\n\t- x pour afficher le bloc x\n\t- \"bc\" pour afficher toute la blockchain\n\t- \"s\" pour supprimer un block (Cheater)\n\t- \"js\" pour enregistrer la chaine en json\n\t- \"q\" pour quitter\n");
		ret = scanf("%s", input);

		while(input[0] != 'q' && ret != 0) {
			if(input[0] == 'b' && input[1] == 'c') {
				printf("Affichage de %d blocks\n",getNbBlock(bc));
				afficherBlockChain(bc);
			} else if (input[0] == 's') {
				printf("Numero du block a supprimer : ");
				ret = scanf("%s", input);
				indice = atoi(input);
				while (indice <= 0 || indice >= getNbBlock(bc)) {
					printf("Saisie invalide, ressaisir : ");
					ret = scanf("%s", input);
					indice = atoi(input);
				}
				temp_cheat = cheaterDeleteBlock(bc, indice);
				printf("\nBlock supprime ! temps : %lf\n", temp_cheat);
			} else if (input[0]=='j' && input[1]=='s') {
				printf("Nom du fichier ? : ");
				ret = scanf("%s",input);
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
			ret = scanf("%s", input);
		}

		freeBlockChain(bc);
	}

	return 0;
}
