import java.awt.*;
import java.awt.image.BufferedImage;

//Széri József - 514
public class PizzaBase implements Pizza {
    private BufferedImage img;

    public PizzaBase() {

    }

    @Override
    public void bake(Graphics g) {

    }

    @Override
    public int getPrice() {
        return 0;
    }

    @Override
    public String getIngredients() {
        return null;
    }
}
