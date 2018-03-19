#include <stdio.h>
#include "merkleroot.h"
#include "blockchain.h"

int main(){
	char *tab[] = {	"Source-Destination:1",
					   "Source-Destination:39",
					   "Source-Destination:25",
					   "Source-Destination:63",
					   "Source-Destination:7",
					   "Source-Destination:78",
					   "Source-Destination:24",
					   "Source-Destination:32",
					   "Source-Destination:72"
	};

	BlockChain bc = initBlockChain(2);
	addBlockToBlockChain(bc,tab,9);
	addBlockToBlockChain(bc,tab,9);

    printf("%s\n",getTimeStampFromBlock(getBlockFromBlockChain(bc,1)));
    printf("block hash 0: %s\n",getBlockHashFromBlock(getBlockFromBlockChain(bc,0)));
    printf("block hash 1: %s\n",getBlockHashFromBlock(getBlockFromBlockChain(bc,1)));
    printf("block hash 2: %s\n",getBlockHashFromBlock(getBlockFromBlockChain(bc,2)));
    printf("%s \n1f71d0159b9230a4da2287b18b568c242727f56fee9ee19a9ca13da3c6227240\n", getMerkleRootFromBlock(getBlockFromBlockChain(bc,1)));
	
	isBlockChainValid(bc) ? printf("OUI\n") : printf("NON\n");

	return 0;
}
