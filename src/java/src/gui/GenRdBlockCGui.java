package gui;

import blockchain.BlockChain;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GenRdBlockCGui {
    BlockChain b;

    private JPanel Dcc;
    private JButton creer;
    private JPanel menu1;
    private JSpinner spinnerdiff;
    private JSpinner spinnernb;
    private JLabel labeldiff;
    private JLabel labelnb;
    private JProgressBar creation;
    private JTextField fichierfield;
    private JPanel fichierpabel;
    private JButton fichierbouton;

    GenRdBlockCGui() {

        creer.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                creation.setStringPainted(true);
                creation.setMaximum((int) spinnernb.getValue());
                BlockChain b = new BlockChain((int) spinnerdiff.getValue());
                String sortie = fichierfield.getText();
                if (sortie.equals("")) {
                    JFileChooser fileChooser = new JFileChooser();
                    if (fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
                        sortie = fileChooser.getSelectedFile().toString();
                    }
                }
                AddBlockWorker w = new AddBlockWorker(b, (int) spinnernb.getValue(), creation, sortie);
                w.execute();
                creation.setValue(0);
            }
        });
        spinnernb.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if ((int) spinnernb.getValue() > 99) {
                    spinnernb.setValue(0);
                }
                if ((int) spinnernb.getValue() < 0) {
                    spinnernb.setValue(99);
                }
            }
        });

        spinnerdiff.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                if ((int) spinnerdiff.getValue() > 15) {
                    spinnerdiff.setValue(0);
                }
                if ((int) spinnerdiff.getValue() < 0) {
                    spinnerdiff.setValue(15);
                }
            }
        });
        fichierbouton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
                    fichierfield.setText(fileChooser.getSelectedFile().toString());
                }
            }
        });
    }

    JPanel getDcc() {
        return Dcc;
    }
}
