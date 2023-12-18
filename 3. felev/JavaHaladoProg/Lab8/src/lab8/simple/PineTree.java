// Széri József - 514/2
package lab8.simple;

import lab8.Plant;

public class PineTree implements Plant {
    @Override
    public double getOxigenAmountPerYear() {
        return 1000;
    }

    @Override
    public int getLifeTime() {
        return 1000;
    }

    @Override
    public String getRepresentation() {
        return "P";
    }
}
