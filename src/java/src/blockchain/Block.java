package blockchain;

import blockchain.transaction.ITransactions;

import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.stream.Collectors;

import static projectutils.HashUtil.applySha256;

public class Block {

    private Integer index;
    private String previousHash;
    private String timeStamp;
    private Integer nbTransactions;
    private ITransactions transactions[];
    private String merkleRoot;
    private String blockHash;
    private Integer nonce;

    /**
     * Create block with mining of block hash.
     *
     * @param index          number of block in BC.
     * @param previousHash   Hash of the previous block in BC "genesis block" if index = 0.
     * @param nbTransactions Number of transactions in transactions
     *                       (redundant of transactions.length(); but still there for Json).
     * @param transactions   list of transactions.
     * @param difficulte     Number of 0 to have at the beginning of blockHash.
     */
    public Block(Integer index, String previousHash, Integer nbTransactions, ITransactions[] transactions, int difficulte) {
        this.index = index;
        Date curDate = new Date();
        this.timeStamp = new SimpleDateFormat("MMM dd, yyyy HH:mm:ss aa").format(curDate);
        this.previousHash = previousHash;
        this.nbTransactions = nbTransactions;
        this.transactions = transactions;
        this.merkleRoot = new MerkleRoot(this.toTransactionStringList()).getRoot();
        this.nonce = 0;
        this.blockHash = this.getHashedBlock(difficulte);//init aussi this.nonce
    }

    private String[] toTransactionStringList() {
        String ret[] = new String[nbTransactions];
        int i = 0;
        for (ITransactions t : this.transactions) {
            ret[i++] = t.toString();
        }
        return ret;
    }

    /**
     * Check if hash have enough 0 at the beginning to become hashBlock.
     * @param hash hash to check.
     * @param difficulte Number of 0 to have.
     * @return True if enough 0 else false.
     */
    private boolean isMiningFinished(String hash, int difficulte){
        for (int i = 0; i < difficulte; i++) {
            if ( hash.charAt(i) != '0') return false;
        }
        return true;
    }

    /**
     * @return a string with all transactions after each other.
     */
    private String getTransactionsString() {
        return Arrays.stream(this.toTransactionStringList()).collect(Collectors.joining(" "));
    }

    /**
     * Hash block check hash if good return else increment nonce and loop.
     * @param difficulte Number of 0 to have.
     * @return String of the hash of the block.
     */
    private String getHashedBlock(int difficulte){
        String input = this.index.toString() + this.previousHash + this.timeStamp + this.nbTransactions.toString() + this.getTransactionsString() + this.merkleRoot;
        String output;
        do{
            output = applySha256(input + this.nonce.toString());
            ++this.nonce;
        }while(!isMiningFinished(output, difficulte));
        --this.nonce;
        return output;
    }

    /* Tous les getter, pas de setter puisqu'un block ne peut pas être modifié sans modifié tous les suivant*/

    public Integer getIndex() {
        return index;
    }

    public String getTimeStamp() {
        return timeStamp;
    }

    public String getPreviousHash() {
        return previousHash;
    }

    public Integer getNbTransactions() {
        return nbTransactions;
    }

    public ITransactions[] getTransactions() {
        return transactions;
    }

    public String getMerkleRoot() {
        return merkleRoot;
    }

    public String getBlockHash() {
        return blockHash;
    }

    public Integer getNonce() {
        return nonce;
    }
}
