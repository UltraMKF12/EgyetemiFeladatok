// Széri József - sjim2307
// Masodfoku
// Irjunk algoritmust az ax2+bx+c = 0 val´os egy¨utthat´oj´u egyenlet megold´as´ara! Az egy¨utthat´ok 128-bites val´os sz´amok (long double).

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    long double a, b, c;
    cin >> a >> b >> c;

    long double delta = (b*b) - (4*a*c);

    if (delta > 0 && a != 0) // Delta > 0 - Azt jelenti, hogy 2 megoldas van, a != 0, ha az elso szam 0, akkor csak x van, azaz 1 megoldas.
    {
        long double megoldas1 = (-b + sqrt(delta)) / (2*a);
        long double megoldas2 = (-b - sqrt(delta)) / (2*a);

        if (megoldas1 < megoldas2)
        {
            cout << fixed << setprecision(1) << megoldas1 << " " << megoldas2;
        }
        else
        {
            cout << fixed << setprecision(1) << megoldas2 << " " << megoldas1;
        }
    }

    else if (delta == 0)
    {
        long double megoldas = (-b + sqrt(delta)) / (2*a);
        cerr << "Az egyenletnek egy megoldasa van: " << megoldas;
    }

    else
    {
        cerr << "Az egyenlet nem megoldható!";
    }

    // else
    // {
    //     cerr << "Hiba!";
    // }
    
    return 0;
}