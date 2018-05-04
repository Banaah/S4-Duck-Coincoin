package blockchain.transaction;

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

    public boolean checkValidity(String hexStringKey) throws Exception {
        ECKey keyFromSign = ECKey.signedMessageToKey(timeStamp + "," +
                        emetteur + "," +
                        destinataire + "," +
                        montant + ","
                        + index,
                this.signature);
        return keyFromSign.getPublicKeyAsHex().equals(hexStringKey);
        //Check if all atribute concatanate is the right signature
    }

    public String toString() {
        return timeStamp + "," +
                emetteur + "," +
                destinataire + "," +
                montant + ","
                + index;
    }
}
