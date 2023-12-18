//Széri József - 514/2
public class AlmondSoup implements Soup {

    @Override
    public void associateMainDish(MainDish mainDish) {
        System.out.println("Az " + this + " leveshez a " + mainDish + " főételt társítottam.");
    }

    @Override
    public String toString() {
        return getClass().getSimpleName();
    }
}
