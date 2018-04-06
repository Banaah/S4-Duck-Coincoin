//
// Created by Quentin Nouvel on 16/02/2018.
//

#ifndef C_MERKLEROOT_H
#define C_MERKLEROOT_H

#include "../utils/sha256_utils.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

#define TRANSACTION_SIZE 22

char *getMerkleRoot(char *transactions[], int nb);
char *merkleRootIt(char *transactions[], int nbTransactions);

#endif //C_MERKLEROOT_H
