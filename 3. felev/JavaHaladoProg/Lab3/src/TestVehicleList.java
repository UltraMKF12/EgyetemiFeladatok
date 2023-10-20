import core.*;
import collection.*;

//Széri József - 514/2
public class TestVehicleList {
    public static void main(String[] args) {
        VehicleList vehicles = new VehicleList(4);
        vehicles.addVehicle(new Car("Nagykocsi", 11));
        vehicles.addVehicle(new Airplane("Repulos", 23, 100));
        vehicles.addVehicle(new Car("Reprep", 56));
        vehicles.addVehicle(new Airplane("Obelisk", 1, 234));
        vehicles.addVehicle(new Airplane("Hektor", 12, 120));

        VehicleIterator forward = vehicles.getForwardIterator();
        VehicleIterator backward = vehicles.getBackwardIterator();

        while (forward.hasMoreElements()) {
            Vehicle vehicle = forward.nextElement();
            System.out.println(vehicle);
            vehicle.numberOfWheels();
            System.out.println();
        }

        System.out.println("===========");

        while (backward.hasMoreElements()) {
            Vehicle vehicle = backward.nextElement();
            System.out.println(vehicle);
            vehicle.numberOfWheels();
            System.out.println();
        }
    }
}
