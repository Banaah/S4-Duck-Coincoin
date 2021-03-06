package blockchain;

import blockchain.transaction.ITransactions;
import blockchain.transaction.Transactions;

import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.stream.Collectors;

import static projectutils.HashUtil.applySha256;

class Block {

    private final Integer index;
    private final String previousHash;
    private final String timeStamp;
    private final Integer nbTransactions;
    private final Transactions[] transactions;
    private final String merkleRoot;
    private final String blockHash;
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
    public Block(Integer index,
                 String previousHash,
                 Integer nbTransactions,
                 Transactions[] transactions,
                 int difficulte) {
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

    /**
     * Check every sensitive field of the blockchain.
     *
     * @param b BlockChain to verify correspondance of public key & Address.
     * @return true if valid else false.
     */
    boolean validityCheckBlock(BlockChain b) {
        String input = this.index.toString() +
                this.previousHash +
                this.timeStamp +
                this.nbTransactions.toString() +
                this.getTransactionsString() +
                this.merkleRoot +
                this.nonce;
        if (!this.blockHash.equals(applySha256(input))) return false;
        String merkle = new MerkleRoot(this.toTransactionStringList()).getRoot();
        if (!this.merkleRoot.equals(merkle)) return false;
        for (ITransactions transac : this.transactions) {
            try {
                if (!transac.checkValidityTransaction(b)) return false;
            } catch (Exception e) {
                System.out.println("ici");
            }
        }
        return true;
    }

    /**
     * Convert a Transaction[] into String[],
     * @return String[] version of this.transactions.
     */
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
        String input = this.index.toString() +
                this.previousHash +
                this.timeStamp +
                this.nbTransactions.toString() +
                this.getTransactionsString() +
                this.merkleRoot;
        String output;
        do{
            output = applySha256(input + this.nonce.toString());
            ++this.nonce;
        }while(!isMiningFinished(output, difficulte));
        --this.nonce;
        return output;
    }

    /* Tous les getter, pas de setter puisqu'un block ne peut pas être modifié sans modifier tous les suivants*/

    Integer getIndex() {
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

    String getBlockHash() {
        return blockHash;
    }

    public Integer getNonce() {
        return nonce;
    }
}
