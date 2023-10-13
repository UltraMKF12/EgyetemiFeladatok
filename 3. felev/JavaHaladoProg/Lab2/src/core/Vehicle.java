//Széri József - 514/2
package core;

public class Vehicle {
    protected String type;
    protected int age;

    public Vehicle(String type, int age) {
        this.type = type;
        this.age = age;
    }

    public String getType() {
        return this.type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}