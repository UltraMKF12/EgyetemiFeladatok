import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

class Flower {
    private int currentSize;
    private final int maxSize;

    public Flower(int maxSize) {
        this.currentSize = 1;
        this.maxSize = maxSize;
    }

    public int getCurrentSize() {
        return currentSize;
    }

    public int getMaxSize() {
        return maxSize;
    }

    public void grow() {
        if (currentSize < maxSize) {
            currentSize++;
        }
    }
}

class GardenView extends JPanel {
    private ArrayList<Flower> flowers;

    public GardenView(ArrayList<Flower> flowers) {
        this.flowers = flowers;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        for (Flower flower : flowers) {
            int size = flower.getCurrentSize();
            int x = flowers.indexOf(flower) * 100 + 50; // Adjust position
            int y = getHeight() - size * 10; // Adjust position and size
            g.setColor(Color.RED); // Flower color
            g.fillRect(x, y, 10, size * 10); // Simple representation of a flower
        }
    }
}

class GardenController extends Thread {
    private ArrayList<Flower> flowers;
    private boolean running;

    public GardenController(ArrayList<Flower> flowers) {
        this.flowers = flowers;
        this.running = true;
    }

    public void stopController() {
        running = false;
    }

    @Override
    public void run() {
        while (running) {
            for (Flower flower : flowers) {
                flower.grow();
                if (flower.getCurrentSize() >= flower.getMaxSize()) {
                    running = false;
                    break;
                }
            }

            try {
                Thread.sleep(500); // Adjust growth speed
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class GardenSimulation {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Garden Simulation");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        ArrayList<Flower> flowers = new ArrayList<>();
        Random random = new Random();

        // Create some flowers with random max sizes
        for (int i = 0; i < 5; i++) {
            flowers.add(new Flower(random.nextInt(5) + 5));
        }

        GardenView gardenView = new GardenView(flowers);
        frame.getContentPane().add(gardenView);
        frame.setSize(600, 400);
        frame.setVisible(true);

        GardenController gardenController = new GardenController(flowers);
        gardenController.start();

        // Wait for the simulation to finish
        try {
            gardenController.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Display a message when the simulation is complete
        JOptionPane.showMessageDialog(frame, "Garden simulation completed!");

        frame.dispose(); // Close the frame when done
    }
}