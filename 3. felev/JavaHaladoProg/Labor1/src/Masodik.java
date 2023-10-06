//Széri József - 524/2
public class Masodik {
    public static void main(String[] args) {
        int paros = 0;
        int paratlan = 0;
        for (int i = 0; i < args.length; i++) {
            try {
                int szam = Integer.parseInt(args[i]);
                if (szam % 2 == 0) {
                    paros += szam;
                } else {
                    paratlan += szam;
                }
            } catch (NumberFormatException e) {
                System.out.println(args[i] + ", NEM SZAM!");
            }
        }

        System.out.println("Paros: " + paros);
        System.out.println("Paratlan: " + paratlan);
    }
}