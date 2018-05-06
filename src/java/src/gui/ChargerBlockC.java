package gui;

import blockchain.BlockChain;
import projectutils.BCJsonUtil;

import javax.swing.*;

class ChargerBlockC {
    private BlockChain b;

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

        ouvrirBouton.addActionListener(e -> {
            b = BCJsonUtil.BCJsonReader(affiFichier.getText());
            if (b == null) {
                JOptionPane.showMessageDialog(null,
                        "BlockChain non-valide",
                        "Alerte",
                        JOptionPane.INFORMATION_MESSAGE);
            } else if (b.validityCheckBC()) {
                addBlock.setEnabled(true);
                ecrireJson.setEnabled(true);
            } else {
                JOptionPane.showMessageDialog(null,
                        "BlockChain altéré",
                        "Alerte",
                        JOptionPane.INFORMATION_MESSAGE);
            }
        });

        ecrireJson.addActionListener(e -> {
            BCJsonUtil.BCJsonWriter(b, affiFichier.getText());
            addBlock.setEnabled(false);
            ecrireJson.setEnabled(false);
        });

        addBlock.addActionListener(e -> {
            ajoutBlockPgb.setStringPainted(true);
            ajoutBlockPgb.setMaximum((int) spinnernb.getValue());
            AddBlockWorker w = new AddBlockWorker(b, (int) spinnernb.getValue(), ajoutBlockPgb);
            w.execute();
            ajoutBlockPgb.setValue(0);
        });

        spinnernb.addChangeListener(e -> {
            if ((int) spinnernb.getValue() > 99) {
                spinnernb.setValue(0);
            }
            if ((int) spinnernb.getValue() < 0) {
                spinnernb.setValue(99);
            }
        });

        choisirButton.addActionListener(e -> {
            JFileChooser dialogue = new JFileChooser();
            dialogue.showOpenDialog(null);
            affiFichier.setText(dialogue.getSelectedFile().toString());
        });
    }

    JPanel getCharger() {
        return charger;
    }
}
