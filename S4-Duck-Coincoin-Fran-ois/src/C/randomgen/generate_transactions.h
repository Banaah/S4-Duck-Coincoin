//
// Created by Quentin Nouvel on 28/02/2018.
//

#ifndef C_GENERATE_TRANSACTIONS_H
#define C_GENERATE_TRANSACTIONS_H

#define TRANSACTION_SIZE 22
#define NB_MAX_TRANSACTION 100

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

char **generateRandomTransactionsList(int *nb);
void freeTransac(char** t, int nb);

#endif //C_GENERATE_TRANSACTIONS_H
