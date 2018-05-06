package randomgen;

import blockchain.BlockChain;
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

    /**
     * Génère une liste de transaction niveau 2.
     *
     * @param b Blockchain pour ajouter les clé publique au dictionnaire.
     * @return Une liste de transactions niveau 2.
     */
    @SuppressWarnings("deprecation")
    public static Transactions[] getTransactionsRdListLvl2(BlockChain b) {
        Address addressFromKey1, addressFromKey2;
        ECKey key1, key2;
        String timestamp;
        int amount;
        int index;
        int nb;
        Random rd = new Random();
        final NetworkParameters netParams = NetworkParameters.testNet();// Deprecated mais on est obligé :( .
        Transactions tab[] = new Transactions[nb = (rd.nextInt(100) + 1)];
        Date curDate = new Date();
        for (int i = 0; i < nb; i++) {
            // Génération des 2 clés
            key1 = new ECKey();
            key2 = new ECKey();
            //Générations Des adresses source et destination
            addressFromKey1 = key1.toAddress(netParams);// Source
            addressFromKey2 = key2.toAddress(netParams);//Destination
            timestamp = new SimpleDateFormat("MMM dd, yyyy HH:mm:ss aa").format(curDate);
            amount = rd.nextInt(10000);
            index = i + 1;
            //Ajoute la clé publique dans un dictionnaire avec comme clé l'adresse
            // à partir de laquelle elle a été générée
            if (!b.getPublicKey().containsKey(addressFromKey1.toString())) {
                b.getPublicKey().put(addressFromKey1.toString(), key1.getPublicKeyAsHex());
            } else {
                System.out.print("Clé déjà référencé");
                if (b.getPublicKey().get(addressFromKey1.toString()).equals(key1.getPublicKeyAsHex()))
                    System.out.println("true");
            }
            tab[i] = new Transactions(i + 1,
                    addressFromKey1.toString(),
                    addressFromKey2.toString(),
                    timestamp,
                    amount,
                    //signature de la transaction
                    key1.signMessage(timestamp + "," +
                            addressFromKey1.toString() + "," +
                            addressFromKey2.toString() + "," +
                            amount + ","
                            + index)
            );
            //System.out.println(addressFromKey1.toString()+ " "+ addressFromKey2.toString());
            //System.out.println(tab[i].checkValidity(key1.getPublicKeyAsHex()));
        }
        return tab;
    }
}