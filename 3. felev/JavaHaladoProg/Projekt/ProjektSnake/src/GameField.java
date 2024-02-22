import java.util.LinkedList;
import java.util.Random;

public class GameField {
    private static final int EMPTY = 0;
    private static final int APPLE = 1;
    private static final int SNAKE_BODY = 2;

    private int[][] grid;
    private int gridSize;
    private LinkedList<Point> snake;

    public GameField(int gridSize) {
        this.gridSize = gridSize;
        this.grid = new int[gridSize][gridSize];
        this.snake = new LinkedList<>();
        initializeGame();
    }

    private void initializeGame() {
        // Initialize the grid with empty cells
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                grid[i][j] = EMPTY;
            }
        }

        // Place the initial snake head in the middle of the grid
        int initialSnakeX = gridSize / 2;
        int initialSnakeY = gridSize / 2;
        snake.add(new Point(initialSnakeX, initialSnakeY));
        grid[initialSnakeX][initialSnakeY] = SNAKE_BODY;

        // Place the initial apple on a random empty cell
        placeApple();
    }

    private void placeApple() {
        Random random = new Random();
        int appleX, appleY;

        do {
            appleX = random.nextInt(gridSize);
            appleY = random.nextInt(gridSize);
        } while (grid[appleX][appleY] != EMPTY);

        grid[appleX][appleY] = APPLE;
    }

    public void moveSnake(Direction direction) {
        // Move the snake based on the specified direction
        Point head = snake.getFirst();
        int newHeadX = head.x;
        int newHeadY = head.y;

        switch (direction) {
            case UP:
                newHeadX--;
                break;
            case DOWN:
                newHeadX++;
                break;
            case LEFT:
                newHeadY--;
                break;
            case RIGHT:
                newHeadY++;
                break;
        }

        // Check for collisions
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
        } else {
            // Move the snake
            Point tail = snake.removeLast();
            grid[tail.x][tail.y] = EMPTY;

            head.x = newHeadX;
            head.y = newHeadY;
            snake.addFirst(head);
            grid[newHeadX][newHeadY] = SNAKE_BODY;
        }
    }

    // Helper class to represent a point (x, y)
    private static class Point {
        int x, y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    public enum Direction {
        UP, DOWN, LEFT, RIGHT
    }
}