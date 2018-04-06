#include "struct/blockchain.h"
#include "cheater/cheat.h"
#include <openssl/sha.h>

int main(){
	BlockChain bc = genCompleteRandomBlockChain(5,12);
	afficherBlockChain(bc);
	int nbTransaction;
	double temp_cheat = cheater(bc, 2, generateRandomTransactionsList(&nbTransaction), nbTransaction);
	afficherBlockChain(bc);
	printf("%lf", temp_cheat);
	freeBlockChain(bc);
	return 0;
}
