//Széri József - 514/2
package core;

public class Car extends Vehicle {
    private float performance;

    public Car(String type, int age, float performance) {
        super(type, age);
        this.performance = performance;
    }

    public float getPerformance() {
        return this.performance;
    }

    public void setPerformance(float performance) {
        this.performance = performance;
    }

    @Override
    public String toString() {
        return "Type: " + this.type + "\nAge: " + this.age + "\nPerformance: " + this.performance;
    }
}