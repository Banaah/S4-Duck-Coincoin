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

    /**
     * Constructor of the worker with saving BC in a file at the end.
     *
     * @param b       The blockChain being worked on.
     * @param nbBlock Number of block to mine.
     * @param jp      Progress bar to move.
     * @param path    path to export BC as Json at the end of work.
     */
    AddBlockWorker(BlockChain b, int nbBlock, JProgressBar jp, String path) {
        this.b = b;
        this.nbBlock = nbBlock;
        this.jp = jp;
        this.write = true;
        this.path = path;
    }

    /**
     * Constructor of the worker without saving BC in a file.
     * @param b The blockChain being worked on.
     * @param nbBlock Number of block to mine.
     * @param jp Progress bar to move.
     */
    AddBlockWorker(BlockChain b, int nbBlock, JProgressBar jp) {
        this.b = b;
        this.nbBlock = nbBlock;
        this.jp = jp;
        this.write = false;
    }

    /**
     * Mine Block and publish progression.
     * @return Blockchain modified.
     * @throws Exception :shrug:
     */
    @Override
    protected BlockChain doInBackground() throws Exception {
        for (int i = 0; i < nbBlock; i++) {
            b.addBlock(TransactionsRdGen.getTransactionsRdListLvl2(b));
            publish(i);
        }
        return b;
    }

    /**
     * Actualize porgress bar.
     */
    @Override
    protected void process(List<Integer> chunks) {
        int i = chunks.get(chunks.size() - 1);
        System.out.println(i);
        this.jp.setValue(i);
    }


    /**
     * Export Bc if needed then set progress bar to 0.
     */
    @Override
    protected void done() {
        System.out.println(b.validityCheckBC());
        jp.setValue(jp.getValue() + 1);
        if (write) BCJsonUtil.BCJsonWriter(b, path);
        jp.setValue(0);
        jp.setStringPainted(false);

    }
}
