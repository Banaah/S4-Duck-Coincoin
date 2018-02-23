#include <stdio.h>
#include "merkleroot.h"
#include "blockchain.h"

int main(){
	char *tab[] = {	"Source-Destination:65",
                       "Source-Destination:31",
                       "Source-Destination:45",
                       "Source-Destination:90",
                       "Source-Destination:44",
                       "Source-Destination:25" };
	Block b = genBlock(0,6,tab,"");
    printf("%s \ne63defa9107cbc64ba39aa4b48056ae0fe242d3aea23751ea61ec46097bbf973\n", getMerkleRootFromBlock(b));
	return 0;
}
