// Széri József - 514
// sjim2307

#include <stdio.h>
#include <stdlib.h>

int kiszamitSzovegHossz(int maxHossz, char * szoveg)
{
    int szovegHossz = 0;
    for(int i = 0; i < maxHossz; i++)
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

int kitorolSpace(int szoveg_hossz, char *szoveg)
{
    int ujHossz = szoveg_hossz;
    for (int i = 0; i < szoveg_hossz; i++)
    {
        if(szoveg[i] == ' ')
        {
            ujHossz--;
            for (int j = 0; j < szoveg_hossz-i; j++)
            {
                szoveg[i+j] = szoveg[i+j+1];
            }
        }
    }

    //Kitorli a ramasolas utan maradt felesleges karaktereket
    for (int i = szoveg_hossz-1; i >= ujHossz; i--)
    {
        szoveg[i] = '\0';
    }
    
    return ujHossz;
}

void megforditas(int szoveg_hossz, char *szoveg)
{
    int i = 0;
    int j = szoveg_hossz-1;
    while(i < j)
    {
        char temp = szoveg[i];
        szoveg[i] = szoveg[j];
        szoveg[j] = temp;
        i++;
        j--;
    }
}

void beolvasas(char *imei)
{
    FILE *f = fopen("input.txt", "r");
    
    if(f == NULL)
    {
        FILE *f2 = fopen("output.txt", "w");
        fprintf(f2, "Hiba");
        fclose(f2);
        exit(0);
    }

    fgets(imei, 20, f); // Fgets automatikusan leall EOF, \n, vagy 20 karakter beolvasas utan. Tudjuk, hogy kb 17 karakter kell nekunk, meg van hatarozva, ezert 20 karaktert olvasunk be hogy leellenorizzuk, hogy tobb van e mint kellene.

    fclose(f);
}

int ellenorzes(char * imei)
{
    // Az input 8 - 2 - stb formatumban van, ami azt jelenti csak az utolso tagoals valtozhat.
    // Ha a beolvasott szoveg hossza 15 + 2 space karakter = 17 karakter, akkor helyes.
    if(kiszamitSzovegHossz(20, imei) == 17)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int karakter_szamjegybe(char karakter)
{
    return (int)(karakter - '0');
}

char szamjegy_karakterbe(int szamjegy)
{
    return (char)(szamjegy + '0');
}

int azonositas(char *imei)
{
    int kontroll = karakter_szamjegybe(imei[16]);
    int imei_hossz = kitorolSpace(16, imei); // Levalasztottuk az utolso karaktert, ezert mar 16 a hossz
    megforditas(imei_hossz, imei);

    //Paratlan pozicioju szamok lekezelese
    for (int i = 0; i < imei_hossz; i += 2)
    {
        int szamjegy = karakter_szamjegybe(imei[i]);
        szamjegy *= 2;
        if(szamjegy > 9)
        {
            szamjegy -= 9;
        }
        imei[i] = szamjegy_karakterbe(szamjegy);
    }

    //Szamjegyek osszeadasa
    int szamjegy_osszeg = 0;
    for (int i = 0; i < imei_hossz; i++)
    {
        szamjegy_osszeg += karakter_szamjegybe(imei[i]);
    }
    szamjegy_osszeg += kontroll;

    // Ha a vegso szamjegy oszthato 0-val akkor ervenyes a szam;
    return (szamjegy_osszeg % 10 == 0);
}

int kodMegszerzes(char *imei)
{
    return ((100 * karakter_szamjegybe(imei[0])) + (10 * karakter_szamjegybe(imei[1])) + (karakter_szamjegybe(imei[2])));
}

void kiiras(int ervenyesseg, int kod)
{
    FILE *f = fopen("output.txt", "w");
    
    if(ervenyesseg)
    {
        if(kod == 359)
        {
            fprintf(f, "Samsung");
        }

        else if(kod == 358)
        {
            fprintf(f, "Google");
        }

        else if(kod == 351)
        {
            fprintf(f, "Motorola");
        }

        else if(kod == 356)
        {
            fprintf(f, "Nokia");
        }

        else
        {
            fprintf(f, "Apple");
        }
    }
    else
    {
        fprintf(f, "ervenytelen");
    }

    fclose(f);
}

int main()
{   
    char imei[20]; // 12+ karakter lehet a sor. 17 karakter amennyit kapni akarunk. Lehet tobbet kapunk es annak is kell helyet foglalni (de 20 nal tobb hely felesleges).
    beolvasas(imei);
    if(ellenorzes(imei))
    {
        int kod = kodMegszerzes(imei);
        kiiras(azonositas(imei), kod);
    }
    else
    {
        kiiras(0, 123); // 0 - jelzi, hogy ervenytelen a kod. 123 - random kod (nem kerul leellenorzesre)
    }

    return 0;
}