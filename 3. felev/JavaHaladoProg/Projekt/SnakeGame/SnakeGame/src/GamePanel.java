import javax.swing.*;
import java.awt.*;

public class GamePanel extends JPanel {
    private GameField gameField;

    public GamePanel(GameField gameField) {
        this.gameField = gameField;
    }

    @Override
    protected void paintComponent(Graphics g) {
        // super.paintComponent(g);

        int gridSize = gameField.getSize();

        // Draw the game field
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                int cellValue = gameField.getCell(i, j);
                Color cellColor = determineColor(cellValue);
                g.setColor(cellColor);
                g.fillRect(i * gridSize, j * gridSize, 20, 20);
            }
        }
    }

    private Color determineColor(int cellValue) {
        switch (cellValue) {
            case GameField.EMPTY:
                return Color.BLACK;
            case GameField.APPLE:
                return Color.RED;
            case GameField.SNAKE_BODY:
                return Color.GREEN;
            default:
                return Color.BLACK; // Default color for unknown values
        }
    }
}