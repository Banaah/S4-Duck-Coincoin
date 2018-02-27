#include <stdio.h>
#include "merkleroot.h"
#include "blockchain.h"

int main(){
  char hashRes[SHA256_BLOCK_SIZE*2 + 1];
	char *tab[] = {	"Source-Destination:65",
                       "Source-Destination:31",
                       "Source-Destination:45",
                       "Source-Destination:90",
                       "Source-Destination:44",
                       "Source-Destination:25" };

	BlockChain bc = initBlockChain(0);
    Block b = genBlock(1,6,tab,"56360bfb8218a44dd9943b4f7ea8a4ef80109e067c9d9da3dc7605be50126abb");
    addBlockToBlockChain(bc,b);
    printf("%s\n",getTimeStampFromBlock(getBlockFromBlockChain(bc,1)));
    printf("%s \ne63defa9107cbc64ba39aa4b48056ae0fe242d3aea23751ea61ec46097bbf973\n", getMerkleRootFromBlock(getBlockFromBlockChain(bc,1)));
	return 0;
}
