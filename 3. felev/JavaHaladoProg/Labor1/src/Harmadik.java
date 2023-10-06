//Széri József - 524/2
public class Harmadik {
    public static void main(String[] args) {
        for (String szoveg : args) {
            for (int i = 0; i < szoveg.length(); i++) {
                char karakter = szoveg.charAt(i);
                if (Character.isLowerCase(karakter)) {
                    System.out.print(Character.toUpperCase(karakter));
                }
                else {
                    System.out.print(Character.toLowerCase(karakter));
                }
            }
            System.out.println();
        }
    }
}
