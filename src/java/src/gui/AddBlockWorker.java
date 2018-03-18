package gui;

import blockchain.BlockChain;
import projectutils.BCJsonUtil;
import randomgen.TransactionsRdGen;

import javax.swing.*;
import java.util.List;

public class AddBlockWorker extends SwingWorker<BlockChain, Integer> {
    private BlockChain b;
    private int nbBlock;
    private JProgressBar jp;
    private boolean write;
    private String path;

    public AddBlockWorker(BlockChain b, int nbBlock, JProgressBar jp, String path) {
        this.b = b;
        this.nbBlock = nbBlock;
        this.jp = jp;
        this.write = true;
        this.path = path;
    }

    AddBlockWorker(BlockChain b, int nbBlock, JProgressBar jp) {
        this.b = b;
        this.nbBlock = nbBlock;
        this.jp = jp;
        this.write = false;
    }


    @Override
    protected BlockChain doInBackground() throws Exception {
        for (int i = 0; i < nbBlock; i++) {
            b.addBlock(TransactionsRdGen.getTransactionRdList());
            publish(i);
        }
        return b;
    }

    @Override
    protected void process(List<Integer> chunks) {
        int i = chunks.get(chunks.size() - 1);
        System.out.println(i);
        this.jp.setValue(i);
    }

    @Override
    protected void done() {
        jp.setValue(jp.getValue() + 1);
        if (write) BCJsonUtil.BCJsonWriter(b, path);
        jp.setValue(0);
        jp.setStringPainted(false);

    }

}
