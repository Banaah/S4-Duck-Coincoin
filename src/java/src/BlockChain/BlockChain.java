package BlockChain;

import java.util.ArrayList;

public class BlockChain {
    private int difficulty;
    private int nbBlocks;
    private ArrayList<Block> BC;

    public BlockChain(int difficulty) {
        this.difficulty = difficulty;
        this.nbBlocks = 0;
        BC = new ArrayList<Block>();
        String transactions[] = new String[1];
        transactions[0] = "genesis block";
        BC.add(new Block(this.nbBlocks++, "0", 1, transactions, this.difficulty));
    }

    void addBlock(String transactions[]){
        BC.add( new Block(this.nbBlocks++, BC.get(BC.size()-1).getBlockHash(), transactions.length, transactions, this.difficulty));
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