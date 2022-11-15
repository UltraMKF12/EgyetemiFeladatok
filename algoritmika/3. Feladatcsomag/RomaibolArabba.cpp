// Széri József - sjim2307
//RomaibolArabba
/*
Adott egy római szám, írjuk ki arab számjegyekkel!
*/

#include <iostream> 
using namespace std;

int romai_arab_tabla(char karakter)
{
    switch (karakter)
    {
    case 'M':
        return 1000;
    case 'D':
        return 500;
    case 'C':
        return 100;
    case 'L':
        return 50;
    case 'X':
        return 10;
    case 'V':
        return 5;
    case 'I':
        return 1;
    
    default:
        return 0; // ha rossz karaktert kapnánk
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    string romai_szam;
    cin >> romai_szam;

    //Minden római számnak az értékét hozzáadjuk az eredményhez
    //Ha a jelenlegi szám értéke nagyobb mint az előzőé, akkor az előzőt ki kellett volna vonni, ezért 2x kivonjuk az előző számot.
    int jelenlegi_ertek = 1000;
    int elozo_ertek = 1000;
    int eredmeny = 0;

    for (int i = 0; i < romai_szam.length(); i++)
    {
        jelenlegi_ertek = romai_arab_tabla(romai_szam[i]);
        if(elozo_ertek < jelenlegi_ertek)
        {
            eredmeny -= (2*elozo_ertek);
        }

        eredmeny += jelenlegi_ertek;
        elozo_ertek = jelenlegi_ertek;
    }
    
    cout << "A megadott szam arab szamjegyekkel: " << eredmeny;
    return 0;
}