// Széri József - sjim2307
// HatvanasSzamrendszer
// Irjunk ki egy, a 60-as sz´amrendszerben megadott sz´amot a 10-es sz´amrendszerben!
#include <iostream>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    string szam;
    cin >> szam;

    long long eredmeny = 0;
    long long szorzo = 1;

    long long eredmenyCopy; // Ez hasonlítás miatt kell, hogyha a szám átugorná a megadott méretet. Overflow control.

    // A szam stringtol visszafele nezzuk a dolgokat.
    //Minden szam magaban van, viszont ha ) karakter van elotte, akkor 2db szam jon utanna.
    for (int i = szam.size() - 1; i >= 0;)
    {
        eredmenyCopy = eredmeny;
        if(szam[i] != ')')
        {
            eredmeny += stoi(szam.substr(i, 1)) * szorzo; // Csak egy szamjegyet kell kiszedni
            szorzo *= 60;
            i--;
        }
        else
        {
            eredmeny += stoi(szam.substr(i-2, 2)) * szorzo; // "12)" // 12-t kiszedi es int-e alaktija
            szorzo *= 60;
            i -= 4;
        }

        if(eredmenyCopy > eredmeny)
        {
            eredmeny = -1;
            break;
        }
    }

    cout << eredmeny;
    
    return 0;
}