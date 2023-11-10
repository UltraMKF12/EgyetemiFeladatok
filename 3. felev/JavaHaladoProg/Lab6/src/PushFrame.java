// Széri József - 514

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Random;

public class PushFrame extends JFrame {
    private JButton pushMe;
    private Random random;

    public PushFrame() {
        setBounds(100, 100, 500, 500);
        setLayout(null);

        random = new Random();
        pushMe = new JButton("Push me!");
        pushMe.setBounds(0, 0, 100, 30);
        pushMe.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                move();
            }
        });

        add(pushMe);
        move();

        setVisible(true);
        setMinimumSize(new Dimension(500, 500));
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }

    public void move() {
        int maxX = getWidth() - pushMe.getWidth();
        int maxY = getHeight() - pushMe.getHeight();

        Point mouseCord = MouseInfo.getPointerInfo().getLocation();
        int newX, newY;
        do {
            newX = random.nextInt(maxX);
            newY = random.nextInt(maxY);
        } while ((mouseCord.x >= newX && mouseCord.x <= newX + pushMe.getWidth()) ||
                 (mouseCord.y >= newY && mouseCord.y <= newY + pushMe.getWidth()));

        pushMe.setLocation(newX, newY);
    }

    public static void main(String[] args) {
        new PushFrame();
    }
}