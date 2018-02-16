//
// Created by Quentin Nouvel on 16/02/2018.
//

#ifndef C_MERKLEROOT_H
#define C_MERKLEROOT_H

#include "sha256_utils.h"
#include <stdlib.h>
#include <memory.h>

#define TAILLE_TRANSACTION 10

char *getMerkleRoot(char *transaction[TAILLE_TRANSACTION], int nb);// transaction au pluriel ?

#endif //C_MERKLEROOT_H
