// Széri József - sjim2307
// HanySzokoev
// Sz´am´ıtsuk ki h´any sz¨ok˝o´ev volt/lesz k´et k¨ul¨onb¨oz˝o ´evsz´am k¨oz¨ott! A k´et ´evsz´am el˝ojel n´elk¨uli 32-bites eg´esz.
#include <iostream>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int kezdet, veg;
    cin >> kezdet >> veg;

    int szokoEvekSzama = 0;
    //((kezdet % 4 == 0 && kezdet % 100 != 0) || (kezdet % 400 == 0))
    int ugrasEv = 1; // Ez at fog valtani 4-re mikor megvan a legelso szokoev.
    for (kezdet; kezdet <= veg; kezdet += ugrasEv)
    {
        if((kezdet % 4 == 0 && kezdet % 100 != 0) || (kezdet % 400 == 0))
        {
            ugrasEv = 4;
            szokoEvekSzama++;
            break;
        }
    }
    
    cout << szokoEvekSzama;
    return 0;
}