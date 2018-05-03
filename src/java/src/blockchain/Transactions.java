package blockchain;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Transactions {
    private int index;
    private String timeStamp;
    private String emetteur;
    private String destinataire;
    private int montant;
    private String signature;

    public Transactions(int index, String emetteur, String destinataire, int montant, String signature) {
        this.index = index;
        this.emetteur = emetteur;
        this.destinataire = destinataire;
        this.montant = montant;
        this.signature = signature;
        Date curDate = new Date();
        this.timeStamp = new SimpleDateFormat("MMM dd, yyyy HH:mm:ss aa").format(curDate);
    }

    public boolean checkValidity(String hexStringKey) {
        return true;
        //Check if all atribute concatanate is the right signature
    }
}
