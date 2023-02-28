// Széri József - sjim2307
//GoldbachSejtes
/*
Írjunk algoritmust, amely egy adott 𝑥 páros számot felír két különböző
prímszám összegeként (Goldbach-sejtés).
*/

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

bool prim_e(unsigned long szam)
{
    if(szam <= 1)
    {
        return false;
    }
    else if(szam % 2 == 0)
    {
        return (szam == 2);
    }
    else
    {
        unsigned long gyok = sqrt(szam);
        for (unsigned long i = 3; i <= gyok; i += 2)
        {
            if(szam % i == 0)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //Beolvasas
    unsigned long szam;
    cin >> szam;

    //Golbach sejtes
    unsigned long prim1, prim2;

    for (unsigned long i = 3; i <= szam/2; i+=2) // Mivel a szám mindig páros, ezért nem kell 2-re tesztelni.
    {
        prim1 = i;
        prim2 = szam - prim1;
        if(prim_e(prim1) && prim_e(prim2))
        {
            break; //Megkaptuk a két prím számot aminek összege egyenlő a számmal.
        }
    }
    
    cout << szam << " = " << prim1 << " + " << prim2;
    return 0;
}