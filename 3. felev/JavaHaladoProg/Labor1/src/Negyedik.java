//Széri József - 524/2
public class Negyedik {
    public static void main(String[] args) {
        //Parameter beolvasas
        int n = 10;
        if(args.length > 0) {
            try {
                n = Integer.parseInt(args[0]);
            }
            catch(NumberFormatException e) {
                System.out.println("Helytelen parameter! n 10-re lett allitva");
            }
        }

        int szam = 1;
        int[][] sorTomb = new int[n][];
        for (int i = 0; i < n; i++) {
            sorTomb[i] = new int[i+1];
            for (int k = 0; k <= i; k++) {
                sorTomb[i][k] = szam;
                szam++;
            }
        }

        for(int i = 0; i < sorTomb.length; i++) {
            for(int k = 0; k < sorTomb[i].length; k++) {
                System.out.print(sorTomb[i][k] + " ");
            }
            System.out.println();
        }
    }
}
