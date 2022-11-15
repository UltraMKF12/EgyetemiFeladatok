// Széri József - sjim2307
//HegyszamVolgyszam
/*
Döntsük el egy adott számról, hogy völgyszám-e vagy hegyszám.
*/

#include <iostream> 
using namespace std;

unsigned long long szamjegy_megforditas(unsigned long long szam)
{
    unsigned long long uj_szam = 0;
    while(szam > 0)
    {
        uj_szam += szam % 10;
        uj_szam *= 10;
        szam /= 10;
    }
    uj_szam /= 10; // Letorolni a vegen a felesleges 0-st.

    return uj_szam;
}

unsigned long long levag_noveked_csokken(unsigned long long szam, bool novekszik)
{
    //Addig vagunk le a szám elejéből ameddig növekszik vagy csökken a szám
    //Ha teljesen levágtuk a számot 0-t térítünk vissza, különben a számot amiből annyit vágtunk le amennyit tudtunk, hibás szám esetén -1-et

    if(szam <= 0)
    {
        return -1; // Ha a szám 0 vagy kisebb, akkor érvénytelen.
    }

    unsigned long long jelenlegi_szam, kovetkezo_szam;
    unsigned long long szam_masolat = szam;

    while(szam_masolat > 9)
    {
        jelenlegi_szam = szam_masolat % 10;
        kovetkezo_szam = (szam_masolat/10) % 10;
        if(novekszik && (kovetkezo_szam <= jelenlegi_szam))
        {
            return szam_masolat;
        }
        else if(!novekszik && (kovetkezo_szam >= jelenlegi_szam))
        {
            return szam_masolat;
        }

        szam_masolat /= 10;
    }

    return 0;
}

bool hegyszam_e(unsigned long long szam)
{
    if(szam < 100)
    {
        return false;
    }

    // A hegyszám nő, majd csökken
    unsigned long long levagas_eredmeny;
    levagas_eredmeny = levag_noveked_csokken(szam, true);
    if(levagas_eredmeny == szam)
    {
        return false; // Ha az első levágással nem lett semmi levágva, akkor a szám egy irányú
    }

    levagas_eredmeny = levag_noveked_csokken(levagas_eredmeny, false);

    // Ha a végén nem marad szám, akkor hegyszám.
    if(levagas_eredmeny == 0)
    {
        return true;
    }

    return false;
}

bool volgyszam_e(unsigned long long szam)
{
    if(szam < 100)
    {
        return false;
    }

    // A völgyszám csökken, majd nő
    unsigned long long levagas_eredmeny;

    levagas_eredmeny = levag_noveked_csokken(szam, false);
    if(levagas_eredmeny == szam)
    {
        return false; // Ha az első levágással nem lett semmi levágva, akkor a szám egy irányú
    }

    levagas_eredmeny = levag_noveked_csokken(levagas_eredmeny, true);

    // Ha a végén nem marad szám, akkor hegyszám.
    if(levagas_eredmeny == 0)
    {
        return true;
    }

    return false;
}

string hegyszam_volgyszam(unsigned long long szam)
{
    if(hegyszam_e(szam))
    {
        return "hegyszam";
    }
    else if(volgyszam_e(szam))
    {
        return "volgyszam";
    }

    while(szam > 1000)
    {
        szam /= 10;
        if (hegyszam_e(szam) || volgyszam_e(szam))
        {
            return to_string(szamjegy_megforditas(szam));
        }
    }

    return "nincs benne hegyszam vagy volgyszam";
}


int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned long long szam;
    cin >> szam;
    szam = szamjegy_megforditas(szam); // Igy könnyebb levágni a szám elején lévő karaktereket
    cout << hegyszam_volgyszam(szam);

    return 0;
}