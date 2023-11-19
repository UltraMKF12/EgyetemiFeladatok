import javax.swing.*;
import java.awt.*;

public class RaceTrack extends JPanel {
    private Car[] cars;

    public RaceTrack() {
        this.setBackground(Color.CYAN);
    }

    public Car[] getCars() {
        return cars;
    }

    public void setCars(Car[] cars) {
        this.cars = cars;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.RED);
        for (int i = 0; i < cars.length; i++) {
            g.fillRect(cars[i].getX(), i * 20, 20, 10);
        }
    }
}
