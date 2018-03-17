import blockchain.BlockChain;
import projectutils.BCJsonUtil;
import randomgen.TransactionsRdGen;

public class Main {
    public static void main(String[] args) {
        BlockChain b = new BlockChain(4);
        for (int i = 0; i < 5; i++) {
            b.addBlock(TransactionsRdGen.getTransactionRdList());
        }
        BCJsonUtil.BCJsonWriter(b, "bc.json");
        BlockChain b2 = BCJsonUtil.BCJsonReader("bc.json");
        b2.addBlock(TransactionsRdGen.getTransactionRdList());
        BCJsonUtil.BCJsonWriter(b2, "bc2.json");
    }
}
