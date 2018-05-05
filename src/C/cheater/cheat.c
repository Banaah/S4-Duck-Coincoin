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

int deleteBlockFromBlockchain(BlockChain bc, int numBlock){
	if (numBlock < 1 || numBlock > getNbBlock(bc)) {
		fprintf(stderr, "erreur nb bloc");
		return -1;
	}
	float avancement;
	int i = 0;
	int j = 0;

	setNbBlock(bc,getNbBlock(bc)-1);

	Iterator it = getIterator(bc);
	for (int j = 0; j < numBlock-1; it = next(it), ++j);

	Iterator del = next(it);
	iteratorSetNext(it,(next(del)));
	iteratorSetPrevious(next(del),it);
	blockChainCheckStructure(bc,del);
 	freeBlock(getBlockFromIterator(del));
	free(del);

	if (!isFinished(it)) {
		while(next(it) != NULL)	{
			avancement = ((float)i++)/(getNbBlock(bc)-j);
			bougerBarreDeChargement(avancement);
			setIndex(getBlockFromIterator(next(it)),getIndex(getBlockFromIterator(next(it)))-1);
			setPreviousHash(getBlockFromIterator(next(it)),getBlockFromIterator(it));
			setBlockHash(getBlockFromIterator(next(it)), getBlockChainDifficulty(bc));
			it = next(it);
		}
	}
	bougerBarreDeChargement(1);
	return 0;
}

double cheaterTransaction(BlockChain bc, int nbBlock, char **transactions, int nbTransactions){
	clock_t start, end;
	start = clock();
	if (cheatBlockFromBlockchain(bc, nbBlock, transactions, nbTransactions)) return 0;
	end = clock();
	return (double) (end - start) / CLOCKS_PER_SEC;
}

double cheaterDeleteBlock(BlockChain bc, int nbBlock){
	clock_t start, end;
	start = clock();
	if (deleteBlockFromBlockchain(bc, nbBlock)) return 0;
	end = clock();
	return (double) (end - start) / CLOCKS_PER_SEC;
}
