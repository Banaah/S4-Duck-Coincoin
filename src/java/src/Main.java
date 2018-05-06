import gui.HomePage;

import javax.swing.*;

class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            //Ouvre une page principale
            JPanel home = new HomePage().getHome();
            JFrame frame = new JFrame("Dcc");
            frame.setContentPane(home);
            frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
            frame.pack();
            frame.setVisible(true);
        });
    }
}
