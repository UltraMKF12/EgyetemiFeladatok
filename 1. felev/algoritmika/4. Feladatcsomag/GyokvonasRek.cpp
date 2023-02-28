// Széri József - sjim2307
//GyokvonasRek
/*
Írjunk rekurzív algoritmust, amely meghatározza egy adott 𝑎 szám négyzetgyökét, 
felhasználva a következő sorozatot, melyről tudjuk, hogy √𝑎-hoz konvergál.
*/

#include <iostream> 
#include <iomanip>
using namespace std;

double gyokvonas_rek(unsigned long long szam, int n)
{
    if(n == 0)
    {
        return szam;
    }

    return (gyokvonas_rek(szam, n-1) + (szam/gyokvonas_rek(szam, n-1)))/2;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);
    unsigned long long a;
    cin >> a;

    double gyok = gyokvonas_rek(a, 10);

    cout << fixed << setprecision(6) << gyok;
    return 0;
}