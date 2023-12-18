// Széri József - 514/2
package lab8.simple;

import lab8.Plant;

public class Grass implements Plant {
    @Override
    public double getOxigenAmountPerYear() {
        return 10;
    }

    @Override
    public int getLifeTime() {
        return 10;
    }

    @Override
    public String getRepresentation() {
        return "G";
    }
}
