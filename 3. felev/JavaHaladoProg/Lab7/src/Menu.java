//Széri József - 514/2
public class Menu {
    private Soup soup;
    private MainDish mainDish;

    public void createMenu(Chef chef) {
        soup = chef.prepareSoup();
        mainDish = chef.prepraeMainDish();
        soup.associateMainDish(mainDish);
    }

    public static void main(String[] args) {
        ChineseChef chineseChef = new ChineseChef();
        IndianChef indianChef = new IndianChef();

        Menu menu1 = new Menu();
        Menu menu2 = new Menu();

        menu1.createMenu(chineseChef);
        menu2.createMenu(indianChef);
    }
}
