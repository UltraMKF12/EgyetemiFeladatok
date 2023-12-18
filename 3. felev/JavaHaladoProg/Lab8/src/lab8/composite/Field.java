// Széri József - 514/2
package lab8.composite;
import lab8.Plant;
import java.util.HashSet;

public class Field implements Plant{
    private HashSet<Plant> list;

    public Field() {
        list = new HashSet<>();
    }

    public void add(Plant plant) {
        list.add(plant);
    }

    public void remove(Plant plant) {
        list.remove(plant);
    }

    @Override
    public double getOxigenAmountPerYear() {
        double sum = 0;
        for(Plant current : list) {
            sum += current.getOxigenAmountPerYear();
        }

        return sum;
    }

    @Override
    public int getLifeTime() {
        int max = -1;
        for(Plant current : list) {
            if(current.getLifeTime() > max) {
                max = current.getLifeTime();
            }
        }

        return max;
    }

    @Override
    public String getRepresentation() {
        StringBuilder representation = new StringBuilder("[");
        for(Plant current : list) {
            representation.append(current.getRepresentation()).append(", ");
        }
        representation = new StringBuilder(representation.substring(0, representation.length() - 2));
        representation.append("]");

        return representation.toString();
    }
}
