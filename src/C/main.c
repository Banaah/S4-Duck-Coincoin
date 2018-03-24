#include "blockchain.h"

int main(){

	BlockChain bc = genCompleteRandomBlockChain(3,10);
	afficherBlockChain(bc);
	freeBlockChain(bc);

	return 0;
}
