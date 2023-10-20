//Széri József - 514/2
package core;

public class Airplane implements Vehicle {
    private String type;
    private int age;
    private float length;

    public Airplane(String type, int age, float length) {
        this.type = type;
        this.age = age;
        this.length = length;
    }

    public void numberOfWheels() {
        System.out.println("The airplane has 6 wheels");
    }

    @Override
    public String toString() {
        return "Type: " + this.type + "\nAge: " + this.age + "\nLength: " + this.length;
    }
}