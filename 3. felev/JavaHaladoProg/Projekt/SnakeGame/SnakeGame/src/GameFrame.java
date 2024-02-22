import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class GameFrame extends JFrame {
    private GamePanel gamePanel;
    private GameField gameField;
    private String direction = "UP";

    public GameFrame(int gridSize) {
        setTitle("Snake Game");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        GameField gameField = new GameField(gridSize);

        gamePanel = new GamePanel(gameField);
        add(gamePanel);

        addKeyListener(new KeyListener() {
            @Override
            public void keyPressed(KeyEvent e) {
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_UP:
                        direction = "UP";
                        break;
                    case KeyEvent.VK_DOWN:
                        direction = "DOWN";
                        break;
                    case KeyEvent.VK_LEFT:
                        direction = "LEFT";
                        break;
                    case KeyEvent.VK_RIGHT:
                        direction = "RIGHT";
                        break;
                }
            }

            @Override
            public void keyTyped(KeyEvent e) {
                // Nothing
            }

            @Override
            public void keyReleased(KeyEvent e) {
                // Nothing
            }
        });

        setBounds(200, 200, 500, 500);
        setVisible(true);

        Timer timer = new Timer(200, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gameField.moveSnake(direction);
                gamePanel.repaint(); // Repaint the panel
            }
        });
        timer.start();
    }

    public static void main(String[] args) {
        new GameFrame(20);
    }
}