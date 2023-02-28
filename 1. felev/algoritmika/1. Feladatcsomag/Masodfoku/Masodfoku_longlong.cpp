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

    if (delta > 0)
    {
        long double megoldas1 = (-b + sqrt(delta)) / (2*a);
        long double megoldas2 = (-b - sqrt(delta)) / (2*a);

        // Azért használok megoldas = int(megoldas) tesztet, mivel a feladat példájában az egész számoknak nincs precizitásuk. Még nem jöttem rá, hogyan kell ilyen esetben a double számoknál eldobni a 0-sokat ezért ezt az alternatívát használom. (Ha a szám egyenlő az long long változatával, akkor egész szám)
        if (megoldas1 < megoldas2)
        {
            if(megoldas1 == (long long)megoldas1)
            {
                cout << fixed << setprecision(0) << megoldas1;
            }
            else
            {
                cout << fixed << setprecision(1) << megoldas1;
            }

            if(megoldas2 == (long long)megoldas2)
            {
                cout << fixed << setprecision(0) << megoldas2;
            }
            else
            {
                cout << fixed << setprecision(1) << megoldas2 << " ";
            }
        }
        else
        {
            if(megoldas2 == (long long)megoldas2)
            {
                cout << fixed << setprecision(0) << megoldas2;
            }
            else
            {
                cout << fixed << setprecision(1) << megoldas2 << " ";
            }

            if(megoldas1 == (long long)megoldas1)
            {
                cout << fixed << setprecision(0) << megoldas1;
            }
            else
            {
                cout << fixed << setprecision(1) << megoldas1;
            }
        }
    }

    else if (delta == 0)
    {
        long double megoldas = (-b + sqrt(delta)) / (2*a);
        cerr << "Az egyenletnek egy megoldasa van: " << megoldas;
    }

    else
    {
        cerr << "Az egyenletnek nincs megoldasa";
    }
    
    return 0;
}