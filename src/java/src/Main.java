import java.text.SimpleDateFormat;
import java.util.Date;

public class Main {

    public static void main(String[] args) {
        Date curDate = new Date();
        String DateToStr = new SimpleDateFormat("MMM dd, yyyy HH:mm:ss aa").format(curDate);
        System.out.println("Default pattern: " + DateToStr);
    }
}
