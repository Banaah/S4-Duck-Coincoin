import gui.HomePage;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        /*BlockChain b = new BlockChain(4);
        for (int i = 0; i < 5; i++) {
            b.addBlock(TransactionsRdGen.getTransactionRdList());
        }
        BCJsonUtil.BCJsonWriter(b, "bc.json");
        BlockChain b2 = BCJsonUtil.BCJsonReader("bc.json");
        assert b2 != null;
        b2.addBlock(TransactionsRdGen.getTransactionRdList());
        BCJsonUtil.BCJsonWriter(b2, "bc2.json");*/
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                JPanel home = new HomePage().getHome();
                JFrame frame = new JFrame("Dcc");
                frame.setContentPane(home);
                frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
                frame.pack();
                frame.setVisible(true);
            }
        });
    }
}
