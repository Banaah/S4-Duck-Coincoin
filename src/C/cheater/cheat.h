//
// Created by Quentin Nouvel on 26/03/2018.
//

#ifndef C_CHEAT_H
#define C_CHEAT_H

#include <time.h>

#include "../struct/blockchain.h"
#include "../struct/block.h"

/* --------------------------- CHEATER ---------------------------- */

double cheaterTransaction(BlockChain bc, int nbBlock, char **transactions, int nbTransactions);
double cheaterDeleteBlock(BlockChain bc, int nbBlock);

/* ---------------------------------------------------------------- */
#endif //C_CHEAT_H
