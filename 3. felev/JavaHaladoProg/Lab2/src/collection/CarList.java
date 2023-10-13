//Széri József - 514/2
package collection;

import core.*;

public class CarList {
    private int current;
    private Car[] cars;

    public class CarIterator {
        private int index;

        public CarIterator() {
            this.index = 0;
        }

        public boolean hasMoreElements() {
            return this.index <= current;
        }

        public Car nextElement() {
            this.index++;
            return cars[this.index - 1];
        }
    }

    public CarList(int size) {
        this.current = -1;
        cars = new Car[size];
    }

    public void addCar(Car newCar) {
        try {
            this.current++;
            cars[current] = newCar;
        } catch (ArrayIndexOutOfBoundsException e) {
            this.current--;
            System.out.println("Tele a kocsi lista!");
        }
    }

    public CarIterator getIterator() {
        return new CarIterator();
    }
}