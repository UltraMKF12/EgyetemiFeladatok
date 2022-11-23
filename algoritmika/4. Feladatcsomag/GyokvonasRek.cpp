// Széri József - sjim2307
//GyokvonasRek
/*
Írjunk rekurzív algoritmust, amely meghatározza egy adott 𝑎 szám négyzetgyökét, 
felhasználva a következő sorozatot, melyről tudjuk, hogy √𝑎-hoz konvergál.
*/

#include <iostream> 
#include <iomanip>
using namespace std;

double gyokvonas_rek(unsigned long long szam, double x)
{
    if(x == 0)
    {
        return szam;
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);
    unsigned long long a;
    cin >> a;

    double gyok = gyokvonas_rek(a, a);

    cout << fixed << setprecision(6) << gyok;
    return 0;
}