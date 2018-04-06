//
// Created by Quentin Nouvel on 26/03/2018.
//

#include "cheat.h"

int cheatBlockFromBlockchain(BlockChain bc, int numBlock, char **transactions, int nbTransactions){
	if (numBlock < 1 || numBlock > getNbBlock(bc)) {
		fprintf(stderr, "erreur nb bloc");
		return -1;
	}
	Iterator it = getIterator(bc);
	for (int i = 0; i < numBlock; it = next(it), ++i);
	setTransactions(getBlockFromIterator(it), transactions, nbTransactions);
	setBlockHash(getBlockFromIterator(it), getBlockChainDifficulty(bc));
	if (!isFinished(it)) {
		for (it = next(it); !isFinished(it); it = next(it)) {
			setBlockHash(getBlockFromIterator(it), getBlockChainDifficulty(bc));
		}
	}
	return 0;
}

double cheater(BlockChain bc, int nbBlock, char **transactions, int nbTransactions){
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	if (cheatBlockFromBlockchain(bc, nbBlock, transactions, nbTransactions)) return 0;
	end = clock();
	return (double) (end - start) / CLOCKS_PER_SEC;
}