//
// Created by Quentin Nouvel on 26/03/2018.
//

#include "cheat.h"

int cheatBlockFromBlockchain(BlockChain bc, int nbBlock){
	if (nbBlock < 1 || nbBlock > getNbBlock(bc)){
		fprintf(stderr, "erreur nb bloc");
		return -1;
	}
	//TODO
	int i = nbBlock;
	Block b;
	Block b2;
	do {
		b = getBlockFromBlockChain(bc, i++);
	}while(i < getNbBlock(bc));
	return 0;
}

clock_t cheater(BlockChain b, int nbBlock){
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	if (cheatBlockFromBlockchain(b, nbBlock)) return 0;
	end = clock();
	return end-start;
}