// Széri József - 514
// sjim2307

#include <stdio.h>
#include <stdlib.h>

int kiszamitSzovegHossz(int karakterHossz, char * szoveg)
{
    int szovegHossz = 0;
    for(int i = 0; i < karakterHossz; i++)
    {
        if(szoveg[i] != '\0')
        {
            szovegHossz++;
        }
        else
        {
            break;
        }
    }
    return szovegHossz;
}

int main()
{
    FILE *f;
    f = fopen("input.txt", "r");
    //Bemenet megnyitása, és leellenőrzni, hogy sikerült megnyitni.
    //Max 255 karakter hosszuságu karakterlánc
    if(f == NULL)
    {
        printf("HIBA: Nem lehetett megnyitni a fajlt!");
        exit(0);
    }
    char szoveg[256];
    fgets(szoveg, 256, f);
    fclose(f);
    int szovegHossz = kiszamitSzovegHossz(255, szoveg);

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
        exit(0);
    }

    char titkosKulcs[100];
    printf("Titkos Kulcs = ");
    getchar();

    gets(titkosKulcs);

    int titkosKulcsHossz = kiszamitSzovegHossz(4, titkosKulcs);
    if(titkosKulcsHossz < 3 || titkosKulcsHossz > 3)
    {
        printf("HIBA: A titkos kulcs hossza pontosan 3 karakter hosszu kell legyen!");
        exit(0);
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

    char ujSzoveg[255] = {'\0'};
    for(int i = 0; i < szovegHossz; i++)
    {
        ujSzoveg[i] = szoveg[i] ^ D ^ szo_bitterkep;
    }


    //kiiratni output.txt be az igy kapott uj karakterlancot.
    f = fopen("output.txt", "w");
    fprintf(f, "%s", ujSzoveg);
    fclose(f);

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