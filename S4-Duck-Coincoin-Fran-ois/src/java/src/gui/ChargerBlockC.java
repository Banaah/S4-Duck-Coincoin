package gui;

import blockchain.BlockChain;
import projectutils.BCJsonUtil;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChargerBlockC {
    BlockChain b;

    private JPanel charger;
    private JPanel core;
    private JLabel titre;
    private JPanel rightCore;
    private JPanel leftCore;
    private JToolBar.Separator sep;
    private JPanel chargerJson;
    private JLabel chargerLabel;
    private JButton ouvrirBouton;
    private JLabel modifLabel;
    private JButton addBlock;
    private JButton ecrireJson;
    private JTextField affiFichier;
    private JButton choisirButton;
    private JPanel choix;
    private JSpinner spinnernb;
    private JProgressBar ajoutBlockPgb;

    ChargerBlockC() {
        ouvrirBouton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                b = BCJsonUtil.BCJsonReader(affiFichier.getText());
                addBlock.setEnabled(true);
                ecrireJson.setEnabled(true);
            }
        });
        ecrireJson.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                BCJsonUtil.BCJsonWriter(b, affiFichier.getText());
                addBlock.setEnabled(false);
                ecrireJson.setEnabled(false);
            }
        });
        addBlock.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //TODO à tester
                ajoutBlockPgb.setStringPainted(true);
                ajoutBlockPgb.setMaximum((int) spinnernb.getValue());
                AddBlockWorker w = new AddBlockWorker(b, (int) spinnernb.getValue(), ajoutBlockPgb);
                w.execute();
                ajoutBlockPgb.setValue(0);
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
        choisirButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser dialogue = new JFileChooser();
                dialogue.showOpenDialog(null);
                affiFichier.setText(dialogue.getSelectedFile().toString());
            }
        });
    }

    public JPanel getCharger() {
        return charger;
    }
}
