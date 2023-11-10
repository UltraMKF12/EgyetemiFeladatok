// Széri József - 514

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DataFrame extends JFrame {
    private JLabel label;
    private JButton button;

    public DataFrame() {
        setBounds(100, 100, 500, 500);
        setLayout(new FlowLayout());


        label = new JLabel("");
        button = new JButton("Datum kiiras");

        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
                String formattedDate = LocalDateTime.now().format(formatter);
                label.setText(formattedDate);
            }
        });

        add(label);
        add(button);

        setVisible(true);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }

    public static void main(String[] args) {
        new DataFrame();
    }
}