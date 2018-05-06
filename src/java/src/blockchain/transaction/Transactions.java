package blockchain.transaction;

import blockchain.BlockChain;
import org.bitcoinj.core.ECKey;

public class Transactions implements ITransactions {
    private final int index;
    private final String timeStamp;
    private final String emetteur;
    private final String destinataire;
    private final int montant;
    private final String signature;

    public Transactions(int index,
                        String emetteur,
                        String destinataire,
                        String timeStamp,
                        int montant,
                        String signature) {
        this.index = index;
        this.emetteur = emetteur;
        this.destinataire = destinataire;
        this.montant = montant;
        this.timeStamp = timeStamp;
        this.signature = signature;
    }

    /**
     * Check Validity of Transactions.
     *
     * @param b BlockChain to get correspondance of publicKey and Address.
     * @return True if address and key match else false.
     * @throws Exception ECKey get public key exception.
     */
    public boolean checkValidityTransaction(BlockChain b) throws Exception {
        ECKey keyFromSign = ECKey.signedMessageToKey(timeStamp + "," +
                        emetteur + "," +
                        destinataire + "," +
                        montant + ","
                        + index,
                this.signature);
        return keyFromSign.getPublicKeyAsHex().equals(b.getPublicKey().get(this.emetteur));
        //Check if all atribute concatanate is the right signature
    }


    /**
     * Redefinition of toString(); .
     * @return A string with few attributes.
     */
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
