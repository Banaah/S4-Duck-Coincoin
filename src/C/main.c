#include "blockchain.h"

int main(){
	BlockChain bc = genCompleteRandomBlockChainConsole(3,10);
	freeBlockChain(bc);
	return 0;
}
