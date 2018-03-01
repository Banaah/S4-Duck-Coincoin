package BlockChain;

import java.util.ArrayList;

public class BlockChain {
    private int difficulte;
    private int nbBlocks;
    private ArrayList<Block> BlockChain;

    public BlockChain(int difficulte) {
        this.difficulte = difficulte;
        this.nbBlocks = 0;
        BlockChain = new ArrayList<Block>();
        String transactions[] = new String[1];
        transactions[0] = "genesis block";
        BlockChain.add(new Block(this.nbBlocks++, "0", 1, transactions, this.difficulte));
    }

    public int getDifficulte() {
        return difficulte;
    }

    public int getNbBlocks() {
        return nbBlocks;
    }

    public ArrayList<Block> getBlockChain() {
        return BlockChain;
    }
}