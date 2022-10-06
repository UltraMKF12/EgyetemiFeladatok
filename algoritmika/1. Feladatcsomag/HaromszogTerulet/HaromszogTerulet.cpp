// Széri József - sjim2307
// HaromszogTerulet
// Sz´am´ıtsuk ki egy h´aromsz¨og ter¨ulet´et, ha ismerj¨uk oldalainak a hossz´at! Az oldalak hosszai 64-bites val´os sz´amok (double).
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    double elso, masodik, harmadik;
    cin >> elso >> masodik >> harmadik;

    double s = (elso + masodik + harmadik) / 2;
    double heronFormula = sqrt(s*(s-elso)*(s-masodik)*(s-harmadik));

    cout << fixed << setprecision(2) << heronFormula;
    return 0;
}