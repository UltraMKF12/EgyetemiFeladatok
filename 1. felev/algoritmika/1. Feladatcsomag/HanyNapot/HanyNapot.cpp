// Széri József - sjim2307
// HanyNapot
// Sz´am´ıtsuk ki, h´any napot ´elt¨unk a mai nappal bez´ar´olag! Ha valaki janu´ar 1.-´en sz¨uletett, akkor janu´ar 2.-´an ´elt 1 napot.
#include <iostream>
using namespace std;

// ----------Előző feladat kódja----------
int HanySzokoev(unsigned long kezdet, unsigned long veg)
{
    int szokoEvekSzama = 0;
    //((kezdet % 4 == 0 && kezdet % 100 != 0) || (kezdet % 400 == 0))
    int ugrasEv = 1; // Ez at fog valtani 4-re mikor megvan a legelso szokoev.
    //Az algoritmus elmegy az első 400-as szökőévhez.
    for (kezdet = kezdet; kezdet <= veg; kezdet += ugrasEv)
    {
        if(kezdet % 4 == 0 && kezdet % 100 != 0)
        {
            ugrasEv = 4;
            szokoEvekSzama++;
        }
        else if(kezdet % 400 == 0)
        {
            szokoEvekSzama++;
            break; // Itt ki kell törni, mivel módszert kell váltani, hogy gyorsabb legyen a számítás, de előtte 400 ra kellett hozni a kezdeti évet. (nagy év különbség esetén)
        }
    }

    //Ez kiszámolja 0 tól x ig a szökőévek számát.
    long long ujEv = (long long)veg - kezdet; // Erre szükség van, mert másként integer overflow lesz.
    if(ujEv > 0)
    {
        szokoEvekSzama += (ujEv / 4) - (ujEv / 100) + (ujEv / 400);
    }
    
    return szokoEvekSzama;
}


int NapInHonap(int honap, bool isSzokoev=false)
{
    //Alternatívaként lehetne tárolni egy tömbben a napok számát.
    switch(honap)
    {
        case 1: //Január
            return 31;
            break;

        case 2: //Február
            if(isSzokoev) return 29;
            return 28;
            break;

        case 3: //Március
            return 31;
            break;

        case 4: //Április
            return 30;
            break;

        case 5: //Május
            return 31;
            break;

        case 6: //Június
            return 30;
            break;
        case 7: //Július
            return 31;
            break;

        case 8: //Augusztus
            return 31;
            break;

        case 9: //Szeptember
            return 30;
            break;

        case 10: //Október
            return 31;
            break;

        case 11: //November
            return 30;
            break;

        case 12: //December
            return 31;
            break;
    }

    return 0;
}

bool IsSzokoEv(int ev)
{
    return ((ev % 4 == 0 && ev % 100 != 0) || (ev % 400 == 0));
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    // Adat beolvasas
    int evSzuletes, evMai, honapSzuletes, honapMai, napSzuletes, napMai;
    char nyelo; // Elnyelni a .-okat

    cin >> evSzuletes >> nyelo >> honapSzuletes >> nyelo >> napSzuletes;
    cin >> evMai >> nyelo >> honapMai >> nyelo >> napMai;

    int napEgyEvben = 365;
    int napokSzama = 0;

    //1-re vinni a napok számát.
    napokSzama -= napSzuletes - 1;
    napSzuletes = 1;

    napokSzama += napMai - 1;
    napMai = 1;
    
    //1-re vinni a hónapok számát. (az előző hónaptol számítva a hónapban lévő össze napot kivonjuk vagy hozzáadjuk a végösszeghez).
    bool isEvSzuletesSzokoEv = IsSzokoEv(evSzuletes);
    for (int honapJelenlegi = 1; honapJelenlegi < honapSzuletes; honapJelenlegi++)
    {
        napokSzama -= NapInHonap(honapJelenlegi, isEvSzuletesSzokoEv);
    }

    bool isEvMaiSzokoEv = IsSzokoEv(evMai);
    for (int honapJelenlegi = 1; honapJelenlegi < honapMai; honapJelenlegi++)
    {
        napokSzama += NapInHonap(honapJelenlegi, isEvMaiSzokoEv);
    }

    //Végül hozzáadni az éveket
    int hanySzokoev = HanySzokoev(evSzuletes, evMai);
    int evKulonbseg = evMai - evSzuletes;

    napokSzama += (evKulonbseg - hanySzokoev) * napEgyEvben; // Átlag évek hozzáadása
    napokSzama += hanySzokoev * (napEgyEvben+1); // Szökő évek hozzáadása

    cout << napokSzama;
    return 0;
}