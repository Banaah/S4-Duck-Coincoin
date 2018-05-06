package blockchain.transaction;

import blockchain.BlockChain;

public interface ITransactions {
    boolean checkValidityTransaction(BlockChain b) throws Exception;
    //Oui inutile mais j'avais prévu de faire un autre type de transactions,
    // pour les rendre lisible par le prog C.
    //Egalement imcopatible avec gson :( .
}
