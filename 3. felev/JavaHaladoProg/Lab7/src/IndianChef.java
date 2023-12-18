//Széri József - 514/2
public class IndianChef implements Chef{
    @Override
    public Soup prepareSoup() {
        return new AlmondSoup();
    }

    @Override
    public MainDish prepraeMainDish() {
        return new ChickpeaCurry();
    }
}
