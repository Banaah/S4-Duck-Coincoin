package gui;

import blockchain.BlockChain;
import projectutils.BCJsonUtil;
import randomgen.TransactionsRdGen;

import javax.swing.*;
import java.util.List;

public class AddBlockWorker extends SwingWorker<Void, Integer> {
    private BlockChain b;
    private int nbBlock;
    private JProgressBar jp;

    AddBlockWorker(BlockChain b, int nbBlock, JProgressBar jp) {
        this.b = b;
        this.nbBlock = nbBlock;
        this.jp = jp;
    }

    @Override
    protected Void doInBackground() throws Exception {
        for (int i = 0; i < nbBlock; i++) {
            b.addBlock(TransactionsRdGen.getTransactionRdList());
            publish(i);
        }
        BCJsonUtil.BCJsonWriter(b, "testfen.json");
        return null;
    }

    @Override
    protected void process(List<Integer> chunks) {
        int i = chunks.get(chunks.size() - 1);
        System.out.println(i);
        this.jp.setValue(i);
    }

    @Override
    protected void done() {
        jp.setValue(0);
        jp.setStringPainted(false);
    }
}
