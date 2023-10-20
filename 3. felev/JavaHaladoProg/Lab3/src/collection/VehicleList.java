//Széri József - 514/2
package collection;

import core.Vehicle;

public class VehicleList {
    private int current;
    private Vehicle[] vehicles;

    public VehicleList(int size) {
        this.current = -1;
        vehicles = new Vehicle[size];
    }

    public void addVehicle(Vehicle newCar) {
        try {
            this.current++;
            vehicles[current] = newCar;
        } catch (ArrayIndexOutOfBoundsException e) {
            this.current--;
            System.out.println("Tele a kocsi lista!");
        }
    }

    public class vehicleForwardIterator implements VehicleIterator {
        private int index;

        public vehicleForwardIterator() {
            this.index = 0;
        }

        public boolean hasMoreElements() {
            return this.index <= current;
        }

        public Vehicle nextElement() {
            this.index++;
            return vehicles[this.index - 1];
        }
    }

    public class vehicleBackwardIterator implements VehicleIterator {
        private int index;

        public vehicleBackwardIterator() {
            this.index = current;
        }

        public boolean hasMoreElements() {
            return this.index >= 0;
        }

        public Vehicle nextElement() {
            return vehicles[this.index--];
        }
    }

    public VehicleIterator getForwardIterator() {
        return new vehicleForwardIterator();
    }

    public VehicleIterator getBackwardIterator() {
        return new vehicleBackwardIterator();
    }

}
