import java.awt.*;

//Széri József - 514
public abstract class PizzaIngredient implements Pizza{
    public Pizza pizza;

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
