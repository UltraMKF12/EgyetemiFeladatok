import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Random;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

public class GameField {
    public static final int EMPTY = 0;
    public static final int APPLE = 1;
    public static final int SNAKE_BODY = 2;

    private int[][] grid;
    private int gridSize;
    private LinkedList<Point> snake;

    private static class Point {
        int x, y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    };

    public GameField(int gridSize) {
        this.gridSize = gridSize;
        this.grid = new int[gridSize][gridSize];
        this.snake = new LinkedList<>();
        initializeGame();
    }

    private void initializeGame() {
        // Empty cells
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                grid[i][j] = EMPTY;
            }
        }

        // Snake in middle as a single snake head
        int initialSnakeX = gridSize / 2;
        int initialSnakeY = gridSize / 2;
        snake.add(new Point(initialSnakeX, initialSnakeY));
        grid[initialSnakeX][initialSnakeY] = SNAKE_BODY;

        // Place apple to random location
        placeApple();
    }

    private void placeApple() {
        Random random = new Random();
        int appleX, appleY;

        do {
            appleX = random.nextInt(gridSize);
            appleY = random.nextInt(gridSize);
        } while (grid[appleX][appleY] != EMPTY && grid[appleX][appleY] != SNAKE_BODY);

        grid[appleX][appleY] = APPLE;
    }

    public void moveSnake(String direction) {
        // Move the snake based on the specified direction
        Point head = snake.getFirst();
        int newHeadX = head.x;
        int newHeadY = head.y;

        switch (direction) {
            case "UP":
                newHeadY--;
                break;
            case "DOWN":
                newHeadY++;
                break;
            case "LEFT":
                newHeadX--;
                break;
            case "RIGHT":
                newHeadX++;
                break;
        }

        // Check if out of bounds or
        if (newHeadX < 0 || newHeadX >= gridSize || newHeadY < 0 || newHeadY >= gridSize
                || grid[newHeadX][newHeadY] == SNAKE_BODY) {
            // Game over
            System.out.println("Game Over");
            System.exit(0);
        }

        // Check for apple
        if (grid[newHeadX][newHeadY] == APPLE) {
            // Snake ate an apple
            snake.addFirst(new Point(newHeadX, newHeadY));
            grid[newHeadX][newHeadY] = SNAKE_BODY;
            placeApple();
            playSound();
        } else {
            // Move the snake
            Point tail = snake.removeLast();
            grid[tail.x][tail.y] = EMPTY;

            Point newHead = new Point(newHeadX, newHeadY);

            snake.addFirst(newHead);
            grid[newHeadX][newHeadY] = SNAKE_BODY;
        }
    }

    private void playSound() {
        try {
            // File URL relative to project folder
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(new File("src/Menu1.wav"));
            Clip clip = AudioSystem.getClip();
            clip.open(audioInputStream);
            clip.start();
        } catch (UnsupportedAudioFileException | LineUnavailableException | IOException e) {
            System.out.println("IO error");
        }
    }

    public int getSize() {
        return gridSize;
    }

    public int getCell(int i, int j) {
        return grid[i][j];
    }
}