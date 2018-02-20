#include <stdio.h>
#include "sha256.h"
#include "sha256_utils.h"
#include "merkleroot.h"

int main(){
	char *tab[] = {	"genesis block" };
	printf("%s \n56360bfb8218a44dd9943b4f7ea8a4ef80109e067c9d9da3dc7605be50126abb\n", getMerkleRoot(tab, 1));
	return 0;
}
