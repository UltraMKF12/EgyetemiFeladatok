// Széri József - sjim2307
// LegkisebbOszto
// Határozzuk meg egy adott 𝑥 természetes szám legkisebb osztóját, amely nagyobb mint 1!

#include <iostream>
using namespace std;

unsigned int legkisebbOszto(unsigned int szam)
{
    if(szam % 2 == 0) // Igy az összes páros számot kiszedjük
    {
        return 2;
    }

    // Szám legkisebb prím osztója
    unsigned int oszto = 3;
    while((oszto <= szam/2+1) && (szam % oszto != 0))
    {
        oszto += 2;
    }

    if(oszto > szam/2+1)
    {
        oszto = szam;
    }

    return oszto;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned int szam;
    cin >> szam;

    unsigned int oszto = legkisebbOszto(szam);
    cout << oszto;
    return 0;
}