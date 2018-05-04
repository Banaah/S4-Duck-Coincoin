package randomgen;

import blockchain.transaction.Transactions;
import org.bitcoinj.core.Address;
import org.bitcoinj.core.ECKey;
import org.bitcoinj.core.NetworkParameters;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;

public class TransactionsRdGen {

    /**
     * @return a random list of simples transactions with random amounts.
     */
    public static String[] getTransactionRdList(){
        Random rd = new Random();
        int nb = rd.nextInt(100)+1;
        String tab[] = new String[nb];
        for (int i = 0; i < nb; i++) {
            tab[i] = "Source-Destination:"+ rd.nextInt(100);
        }
        return tab;
    }

    public static Transactions[] getTransactionsRdListLvl2() {
        Random rd = new Random();
        int nb = rd.nextInt(100) + 1;
        Transactions tab[] = new Transactions[nb];
        ECKey key1;
        ECKey key2;
        final NetworkParameters netParams;
        netParams = NetworkParameters.testNet();
        Date curDate = new Date();
        String timestamp;
        int amount;
        for (int i = 0; i < nb; i++) {
            key1 = new ECKey();
            key2 = new ECKey();
            Address addressFromKey1 = key1.toAddress(netParams);
            Address addressFromKey2 = key2.toAddress(netParams);
            timestamp = new SimpleDateFormat("MMM dd, yyyy HH:mm:ss aa").format(curDate);
            amount = rd.nextInt(10000);
            tab[i] = new Transactions(i + 1,
                    addressFromKey1.toString(),
                    addressFromKey2.toString(),
                    timestamp,
                    amount,
                    key1.signMessage(timestamp + "," +
                            addressFromKey1.toString() + "," +
                            addressFromKey2.toString() + "," +
                            amount + ","
                            + i + 1)
            );
        }
        return tab;
    }
}
