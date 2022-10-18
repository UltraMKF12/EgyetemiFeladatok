// Széri József - 514
// sjim2307

#include <stdio.h>
#include <stdlib.h>
int main()
{
    //Bemenet megnyitása, és leellenőrzni, hogy sikerült megnyitni.
    //Max 255 karakter hosszuságu karakterlánc
    char szoveg[255];
    scanf("%s", szoveg);

    //Standard bemenet:
    //3db szám 0-9 között + hibaellenőrzés
    //1db 3 betüs karakterlánc + hibaellenőrzés

    //Három darak szám beolvasása
    int szam1, szam2, szam3;
    printf("Szam1 = ");
    scanf("%d", &szam1);

    printf("Szam2 = ");
    scanf("%d", &szam2);

    printf("Szam3 = ");
    scanf("%d", &szam3);

    if((szam1 < 0 || szam1 > 9) || (szam2 < 0 || szam2 > 9) || (szam3 < 0 || szam3 > 9))
    {
        printf("HIBA: A szamok kozul egy vagy tobb nincs benne a [0-9] intervallumban!");
        //Kilepes a programbol
    }

    char titkosKulcs[100];
    printf("Titkos Kulcs = ");
    scanf("%s", titkosKulcs);
    if(1)
    {
        //Kileps ha kevesebb vagy tobb mint 3 karakter
    }

    /*
        TitkositÁsi formula:

        C ^ D ^ szo_bitterkep
        D = X << ~|Y - Z|
        szo_bitterkep = szo[0] | szo[1] & szo[2]

        ahol C egy tetszőleges karakter a karakterláncból, míg X, Y és Z a standard bemenetről beolvasott számok.
    */

    char szo_bitterkep = titkosKulcs[0] | titkosKulcs[1] & titkosKulcs[2];
    int D = szam1 << ~abs(szam2 - szam3);

    for(int i = 0; i < 255; i++)
    {
            szoveg[i] = szoveg[i] ^ D ^ szo_bitterkep;
    }


    //kiiratni output.txt be az igy kapott uj karakterlancot.
    printf("%s", szoveg);

    //Kiiratni az ascii táblát
        for(int i = 0; i <= 25; i++)
        {
            int value = i;
            while(value <= 255)
            {   
                if(value == 0)
                {
                    printf("|%*d [0x00]:   ", 3, value);
                }
                else if((value > 6 && value < 16) || value == 27 || value == 127)
                {
                    printf("|%*d [%#0*x]:   ", 3, value, 4, value);
                }
                else
                {
                    printf("|%*d [%#0*x]: %c ", 3, value, 4, value, value);
                }
                value += 26;
            }
            printf("\n");
        }
        return 0;
}