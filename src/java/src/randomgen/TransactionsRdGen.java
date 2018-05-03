package randomgen;
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
}
