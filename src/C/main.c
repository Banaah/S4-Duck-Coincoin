#define INPUT_LENGTH 20

#include "blockchain.h"
#include "merkleroot.h"

int main(){
	char input[INPUT_LENGTH];
	int indice;

	char *tab[] = {"Source-Destination:88",
				   "Source-Destination:55",
				   "Source-Destination:4",
				   "Source-Destination:94",
				   "Source-Destination:63",
				   "Source-Destination:68",
				   "Source-Destination:21",
				   "Source-Destination:23",
				   "Source-Destination:53",
				   "Source-Destination:15",
				   "Source-Destination:9",
				   "Source-Destination:96",
				   "Source-Destination:11",
				   "Source-Destination:78",
				   "Source-Destination:17",
				   "Source-Destination:37",
				   "Source-Destination:35",
				   "Source-Destination:22",
				   "Source-Destination:93",
				   "Source-Destination:17",
				   "Source-Destination:69"};

	char *res = merkleRootIt(tab,21);
	printf("OUI : %s\n",res);

	char *res2 = getMerkleRoot(tab,21);
	printf("OUI : %s\n",res2);

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
