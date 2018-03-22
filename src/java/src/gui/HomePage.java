package gui;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class HomePage {
    private JPanel Home;
    private JPanel core;
    private JLabel titre;
    private JPanel rightCore;
    private JPanel leftCore;
    private JButton chargerBouton;
    private JButton creerBouton;
    private JLabel chargerLabel;
    private JLabel creerLabel;
    private JSeparator sep;

    public HomePage() {
        creerBouton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFrame pop = new JFrame("Créer");
                pop.setContentPane(new GenRdBlockCGui().getDcc());
                pop.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
                pop.pack();
                pop.setVisible(true);
            }
        });
        chargerBouton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFrame pop = new JFrame("Charger");
                pop.setContentPane(new ChargerBlockC().getCharger());
                pop.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
                pop.pack();
                pop.setVisible(true);
            }
        });
    }

    public JPanel getHome() {
        return Home;
    }
}
