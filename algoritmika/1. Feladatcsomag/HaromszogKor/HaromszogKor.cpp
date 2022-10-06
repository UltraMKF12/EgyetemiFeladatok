// Széri József - sjim2307
// HaromszogKor
// Adott h´arom szigor´uan pozit´ıv 64-bites val´os sz´am (double): a, b, c. K´epezhetike ezek a sz´amok egy h´aromsz¨og oldalait? Ha igen, hat´arozzuk meg ´es ´ırjuk ki a h´aromsz¨ogbe ´ırt, illetve a h´aromsz¨og k¨or´e ´ırt k¨or sugar´at! Ha nem, ´ırjunk ki -1-et!

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    double a, b, c;
    cin >> a >> b >> c;

    // A háromszög bármely két oldalának összege nagyobb kell legyen mint a harmadik
    if(a+b > c && a+c > b && b+c > a)
    {
        double s = (a+b+c) / 2;
        double terulet = sqrt(s*(s-a)*(s-b)*(s-c)); // Heron formula
        double kerulet = a+b+c;

        double haromszogbeIrtKorSugara = 2 * terulet / kerulet;
        double haromszogKoreIrtKorSugara = (a*b*c) / (4 * terulet);
        cout << fixed << setprecision(3) << haromszogbeIrtKorSugara << " " << haromszogKoreIrtKorSugara;
    }

    else
    {
        cout << -1;
    }

    return 0;
}