package BlockChain;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.stream.Collectors;

import static ProjectUtils.HashUtil.applySha256;

public class Block {

    private Integer index;
    private String timeStamp;
    private String previousHash;
    private Integer nbTransactions;
    private String transactions[] = new String[this.nbTransactions];
    private String merkleRoot;
    private String blockHash;
    private Integer nonce;

    public Block(Integer index, String previousHash, Integer nbTransactions, String[] transactions, int difficulte) {
        this.index = index;
        Date curDate = new Date();
        this.timeStamp = new SimpleDateFormat("MMM dd, yyyy HH:mm:ss aa").format(curDate);
        this.previousHash = previousHash;
        this.nbTransactions = nbTransactions;
        this.transactions = transactions;
        this.merkleRoot = new MerkleRoot(this.transactions).getRoot();
        this.blockHash = this.getHashedBlock(difficulte);//init aussi this.nonce
    }

    private boolean isMiningFinished(String hash, int difficulte){
        for (int i = 0; i < difficulte; i++) {
            if ( hash.charAt(i) != '0') return false;
        }
        return true;
    }

    private String getTransactionsString() {
        return Arrays.stream(this.transactions).collect(Collectors.joining(" "));
    }

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

    /*private String computeMerkleRoot(){
        String out;

        return out;
    }
    */


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

    public String[] getTransactions() {
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
