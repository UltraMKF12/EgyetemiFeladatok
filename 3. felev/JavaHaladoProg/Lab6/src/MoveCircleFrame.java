// Széri József - 514

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MoveCircleFrame extends JFrame {
    private MovePanel panel;
    private JButton left;
    private JButton right;
    private JButton up;
    private JButton down;

    public MoveCircleFrame() {
        setBounds(100, 100, 500, 500);
        setLayout(new BorderLayout());

        panel = new MovePanel();
        up = new JButton("↑");
        down = new JButton("↓");
        left = new JButton("←");
        right = new JButton("→");

        up.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                panel.moveCircle(0, -20);
            }
        });

        down.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                panel.moveCircle(0, 20);
            }
        });

        left.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                panel.moveCircle(-20, 0);
            }
        });

        right.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                panel.moveCircle(20, 0);
            }
        });


        add(panel, BorderLayout.CENTER);
        add(up, BorderLayout.NORTH);
        add(down, BorderLayout.SOUTH);
        add(left, BorderLayout.WEST);
        add(right, BorderLayout.EAST);

        setVisible(true);
        setResizable(false);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }

    public static void main(String[] args) {
        new MoveCircleFrame();
    }
}
