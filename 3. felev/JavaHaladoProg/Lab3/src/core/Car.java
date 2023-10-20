//Széri József - 514/2
package core;

public class Car implements Vehicle {
    private String type;
    private int age;

    public Car(String type, int age) {
        this.type = type;
        this.age = age;
    }

    public void numberOfWheels() {
        System.out.println("The car has 4 wheels");
    }

    @Override
    public String toString() {
        return "Type: " + this.type + "\nAge: " + this.age;
    }
}