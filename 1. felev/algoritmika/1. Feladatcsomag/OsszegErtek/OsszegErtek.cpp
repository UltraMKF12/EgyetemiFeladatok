// Széri József - sjim2307
// OsszegErtek
// Sz´am´ıtsuk ki, adott n ´es x ´ert´ekekre, a k¨ovetkez˝o ¨osszeget:
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n;
    double x;
    cin >> n >> x;

    double eredmeny = 1;
    double negyzetesSzam = 1;
    unsigned long long faktorialisSzam = 1;
    int faktorialisIndex = 1;
    for (int i = 1; i <= n; i++)
    {
        int minuszVagyPlusz = (i % 2 == 0) ? 1 : -1; // Minden páratlan számnál negatív.
        negyzetesSzam = negyzetesSzam * x * x;
        faktorialisSzam = faktorialisSzam * faktorialisIndex * (faktorialisIndex+1);
        faktorialisIndex += 2;

        eredmeny = eredmeny + (minuszVagyPlusz * (negyzetesSzam / faktorialisSzam));
    }
    
    cout << fixed << setprecision(2) << eredmeny;
    return 0;
}