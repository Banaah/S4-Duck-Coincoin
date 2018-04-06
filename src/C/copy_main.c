//
// Created by Quentin Nouvel on 24/03/2018.
//

#include "struct/blockchain.h"

int main(){
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	BlockChain bc = genCompleteRandomBlockChain(4,15);
	afficherBlockChain(bc);
	freeBlockChain(bc);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%f", cpu_time_used);


	return 0;
}
