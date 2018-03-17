#include <stdio.h>
#include "merkleroot.h"
#include "blockchain.h"

int main(){
    char hashRes[SHA256_BLOCK_SIZE*2 + 1];
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

	BlockChain bc = initBlockChain(0);
    Block b = genBlock(1,9,tab,"56360bfb8218a44dd9943b4f7ea8a4ef80109e067c9d9da3dc7605be50126abb", 4);
    addBlockToBlockChain(bc,b);
    printf("%s\n",getTimeStampFromBlock(getBlockFromBlockChain(bc,1)));
    printf("%s \n1f71d0159b9230a4da2287b18b568c242727f56fee9ee19a9ca13da3c6227240\n", getMerkleRootFromBlock(getBlockFromBlockChain(bc,1)));

	/*char tab[] = "Jan 19, 2018 10:49:16 AM01genesis block56360bfb8218a44dd9943b4f7ea8a4ef80109e067c9d9da3dc7605be50126abb0";
	char res[HASH_SIZE+1];
	sha256ofString((BYTE *) tab, res);
	printf("%s\n996e3af3152933e59a4a71257eb03499cd1940f157b235332a0271e42b908097\n", res);
	*/
	return 0;
}
