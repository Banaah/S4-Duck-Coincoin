package blockchain.transaction;

import blockchain.BlockChain;
import org.bitcoinj.core.ECKey;

public class Transactions implements ITransactions {
    private int index;
    private String timeStamp;
    private String emetteur;
    private String destinataire;
    private int montant;
    private String signature;

    public Transactions(int index, String emetteur, String destinataire, String timeStamp, int montant, String signature) {
        this.index = index;
        this.emetteur = emetteur;
        this.destinataire = destinataire;
        this.montant = montant;
        this.timeStamp = timeStamp;
        this.signature = signature;
    }

    public boolean checkValidityTransaction(BlockChain b) throws Exception {
        ECKey keyFromSign = new ECKey().signedMessageToKey(timeStamp + "," +
                        emetteur + "," +
                        destinataire + "," +
                        montant + ","
                        + index,
                this.signature);
        //System.out.println(emetteur+" "+destinataire);
        return keyFromSign.getPublicKeyAsHex().equals(b.getPublicKey().get(this.emetteur));
        //Check if all atribute concatanate is the right signature
    }


    public String toString() {
        return timeStamp + "," +
                emetteur + "," +
                destinataire + "," +
                montant + ","
                + index;
    }

    public String getSignature() {
        return signature;
    }
}
