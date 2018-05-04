package blockchain;

import blockchain.transaction.ITransactions;
import blockchain.transaction.Transactions;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class BlockChain {
    private int difficulty;
    private int nbBlocks;
    private ArrayList<Block> BC;

    public BlockChain(int difficulty) {
        this.difficulty = difficulty;
        this.nbBlocks = 0;
        this.BC = new ArrayList<Block>();
        Transactions transactions[] = new Transactions[1];
        Date curDate = new Date();
        transactions[0] = new Transactions(0, "genesis", "block", new SimpleDateFormat("MMM dd, yyyy HH:mm:ss aa").format(curDate), 0, "");
        this.BC.add(new Block(this.nbBlocks++,
                "0",
                1,
                transactions,
                this.difficulty));
    }

    /**
     * Add a block in the blockchain.
     *
     * @param transactions transactions list of the block.
     */
    public void addBlock(ITransactions transactions[]) {
        this.BC.add(0,
                new Block(this.nbBlocks++,
                        BC.get(0).getBlockHash(),
                        transactions.length,
                        transactions,
                        this.difficulty));
    }

    public int getDifficulty() {
        return difficulty;
    }

    public int getNbBlocks() {
        return nbBlocks;
    }

    public ArrayList<Block> getBC() {
        return BC;
    }
}