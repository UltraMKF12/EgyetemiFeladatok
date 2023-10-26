//Széri József - 514/2
import core.*;
import collection.*;

public class TestMyHashMap {
    public static void main(String[] args) {
        MyHashMap hm = new MyHashMap(10);
        hm.put(1001, new Car("Audi", 1));
        hm.put(1001, new Car("BMW", 2));
        hm.put(101, new Car("Nissan", 3));
        hm.put(10001, new Car("Mazda", 4));
        hm.put(2001, new Car("VW", 5));
        hm.put(3001, new Car("Ford", 6));
        hm.put(4003, new Car("Opel", 7));
        System.out.println(hm.get(1001));
        System.out.println(hm.get(2001));
        System.out.println(hm.get(3001));
        System.out.println(hm.get(4003));
        System.out.println(hm.get(5001));
        System.out.println(hm.get(5002));
        System.out.println(hm.get(5003));
        System.out.println(hm.containsKey(1001));
        System.out.println(hm.containsKey(5001));
        System.out.println(hm.containsKey(5002));
    }
}
