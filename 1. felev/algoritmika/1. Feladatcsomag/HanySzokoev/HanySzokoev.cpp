// Széri József - sjim2307
// HanySzokoev
// Sz´am´ıtsuk ki h´any sz¨ok˝o´ev volt/lesz k´et k¨ul¨onb¨oz˝o ´evsz´am k¨oz¨ott! A k´et ´evsz´am el˝ojel n´elk¨uli 32-bites eg´esz.
#include <iostream>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned long kezdet, veg;
    cin >> kezdet >> veg;

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
    
    cout << szokoEvekSzama;
    return 0;
}