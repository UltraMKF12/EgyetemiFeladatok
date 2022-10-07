// Széri József - sjim2307
// HanyNapot
// Sz´am´ıtsuk ki, h´any napot ´elt¨unk a mai nappal bez´ar´olag! Ha valaki janu´ar 1.-´en sz¨uletett, akkor janu´ar 2.-´an ´elt 1 napot.
#include <iostream>
using namespace std;

bool IsSzokoEv(int ev)
{
    return ((ev % 4 == 0 && ev % 100 != 0) || (ev % 400 == 0));
}

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    // Adat beolvasas
    int evSzuletes, evMai, honapSzuletes, honapMai, napSzuletes, napMai;
    char nyelo; // Elnyelni a .-okat

    cin >> evSzuletes >> nyelo >> honapSzuletes >> nyelo >> napSzuletes;
    cin >> evMai >> nyelo >> honapMai >> nyelo >> napMai;

    int napEgyEvben = 365;
    int napokSzama = 0;

    while((evSzuletes != evMai) && (honapSzuletes != honapMai) && (napSzuletes != napMai))
    {
        
    }


    cout << "Hello World!";
    return 0;
}