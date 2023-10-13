//Széri József - 514/2
import core.*;
import collection.*;

public class TestCarList {
    public static void main(String[] args) {
        Car a = new Car("Alma", 56, 12.2f);
        Car b = new Car("Audi", 12, 218.9f);
        Car c = new Car("GogoMobile", 256, 2.8f);
        Car d = new Car("Rufus", 8, 514.25f);
        Car e = new Car("BMW", 14, 211.31f);
        Car f = new Car("NosARB", 26, 165.24f);

        CarList lista = new CarList(2);
        lista.addCar(a);
        lista.addCar(b);
        lista.addCar(c);
        lista.addCar(d);
        lista.addCar(e);
        lista.addCar(f);

        CarList.CarIterator iter = lista.getIterator();
        while (iter.hasMoreElements()) {
            Car element = iter.nextElement();
            System.out.println(element);
        }
    }
}
