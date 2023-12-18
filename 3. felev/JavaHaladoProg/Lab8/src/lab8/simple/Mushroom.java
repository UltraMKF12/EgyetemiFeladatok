// Széri József - 514/2
package lab8.simple;

import lab8.Plant;

public class Mushroom implements Plant {
    @Override
    public double getOxigenAmountPerYear() {
        return 100;
    }

    @Override
    public int getLifeTime() {
        return 100;
    }

    @Override
    public String getRepresentation() {
        return "M";
    }
}
