#include <stdio.h>
#include "sha256.h"
#include "sha256_utils.h"
#include "merkleroot.h"

int main(){
	char *tab[] = {"Source-Destination:1","Source-Destination:39","Source-Destination:25","Source-Destination:63","Source-Destination:7","Source-Destination:78","Source-Destination:24","Source-Destination:32","Source-Destination:72"};
	printf("%s %s\n", getMerkleRoot(tab, 9), getMerkleRoot2(tab, 9));
	return 0;
}