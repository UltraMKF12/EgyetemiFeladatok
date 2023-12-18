package lab8;

import lab8.composite.*;
import lab8.simple.*;

// Széri József - 514/2
public class Main {
    public static void main(String[] args) {
        Field field1 = new Field();
        Field field2 = new Field();
        Forest forest = new Forest();

        field1.add(new Grass());
        field1.add(new Flower());

        field2.add(new Mushroom());
        field2.add(new Mushroom());

        forest.add(field1);
        forest.add(field2);
        forest.add(new PineTree());
        forest.add(new OakTree());

        System.out.println("Forest:");
        System.out.println(forest.getRepresentation());
        System.out.println("Oxygen: " + forest.getOxigenAmountPerYear());
        System.out.println("Lifetime: " + forest.getLifeTime());

        System.out.println("\n");

        System.out.println("Field 1:");
        System.out.println("Oxygen: " + field1.getOxigenAmountPerYear());
        System.out.println("Lifetime: " + field1.getLifeTime());

        System.out.println("\n");

        System.out.println("Field 2:");
        System.out.println("Oxygen: " + field2.getOxigenAmountPerYear());
        System.out.println("Lifetime: " + field2.getLifeTime());
    }
}
