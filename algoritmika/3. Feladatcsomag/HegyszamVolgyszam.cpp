// Széri József - sjim2307
//HegyszamVolgyszam
/*
Döntsük el egy adott számról, hogy völgyszám-e vagy hegyszám.
*/

#include <iostream> 
using namespace std;

int szamjegy_megforditas(int szam)
{
    int uj_szam = 0;
    while(szam > 0)
    {
        uj_szam += szam % 10;
        uj_szam *= 10;
        szam /= 10;
    }
    uj_szam /= 10; // Letorolni a vegen a felesleges 0-st.

    return uj_szam;
}

bool hullamzik_e(int szam, bool felfele_tipp, int keresett_hullamzas)
{
    int hullamok_szama = 0;

    if(szam < 100) // 100 nal kisebb nem hullamzanak.
    {
        return false;
    }

    int elozo_szamjegy = szam % 10;
    szam /= 10;

    // Kiszámítjuk, hogy felfele mennek a számok vagy lefele. Ha ez nem egyezik a tippel, akkor nem nézzük tovább.
    // Szóval direkt meglehet adni, hogy hegy vagy völgyet várunk el a számtól.
    bool felfele = szam%10 > elozo_szamjegy;
    if(felfele != felfele_tipp)
    {
        return false;
    }

    while((szam > 0))
    {
        int szamjegy = szam % 10;
        szam /= 10;
        if(hullamok_szama <= keresett_hullamzas)
        {
            if(felfele)
            {
                if(szamjegy < elozo_szamjegy)
                {
                    felfele = false;
                    hullamok_szama++;
                }
            }
            else
            {
                if(szamjegy > elozo_szamjegy)
                {
                    felfele = true;
                    hullamok_szama++;
                }
            }
        }

        elozo_szamjegy = szamjegy;
    }

    return (hullamok_szama == keresett_hullamzas);
}

string hegyszam_volgyszam(int szam)
{
    if(hullamzik_e(szam, true, 1))
    {
        return "hegyszam";
    }
    else if(hullamzik_e(szam, false, 1))
    {
        return "volgyszam";
    }

    while(szam > 0)
    {
        szam /= 10;
        if (hullamzik_e(szam, true, 1) || hullamzik_e(szam, false, 1))
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

    int szam;
    cin >> szam;
    szam = szamjegy_megforditas(szam); // Igy könnyebb megkapni az "elso" szamjegyet
    cout << hegyszam_volgyszam(szam);

    return 0;
}