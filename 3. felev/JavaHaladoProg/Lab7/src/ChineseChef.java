//Széri József - 514/2
public class ChineseChef implements Chef{
    @Override
    public Soup prepareSoup() {
        return new KlangBakKutTehSoup();
    }

    @Override
    public MainDish prepraeMainDish() {
        return new KungPaoChicken();
    }
}
