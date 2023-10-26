//Széri József - 514/2
package core;

public class Car {
    private String type;
    private Integer age;

    public Car(String type, Integer age) {
        this.type = type;
        this.age = age;
    }

    public String toString() {
        return "Type: " + this.type + "\nAge: " + this.age + "\n";
    }
}
