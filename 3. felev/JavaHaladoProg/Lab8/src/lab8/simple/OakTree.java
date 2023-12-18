// Széri József - 514/2
package lab8.simple;

import lab8.Plant;

public class OakTree implements Plant {
    @Override
    public double getOxigenAmountPerYear() {
        return 10000;
    }

    @Override
    public int getLifeTime() {
        return 10000;
    }

    @Override
    public String getRepresentation() {
        return "O";
    }
}
