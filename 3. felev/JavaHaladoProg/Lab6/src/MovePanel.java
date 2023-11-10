// Széri József - 514

import javax.swing.*;
import java.awt.*;

public class MovePanel extends JPanel {
    private int posX = 200;
    private int posY = 200;
    private int size = 100;

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.BLACK);
        g.drawOval(posX, posY, size, size);
    }

    public void moveCircle(int x, int y) {
        if (    posX + x >= 0 && posX + x + size <= getWidth() &&
                posY + y >= 0 && posY + y + size <= getHeight()) {

            posX += x;
            posY += y;
            repaint();
        }
    }
}
