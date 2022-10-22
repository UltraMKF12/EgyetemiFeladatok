// Széri József - sjim2307
// 3n+1
/*
Ismert sejtés, miszerint ha egy adott 𝑛 természetes számot ismételten alávetünk
a következő feldolgozásnak, eljutunk az 1-es számhoz: ha 𝑛 páros, akkor elosztjuk
2-vel, ha 𝑛 páratlan, megszorozzuk 3-mal és az eredményhez hozzáadunk 1-et.
Azoknak a lépéseknek a számát, amelyek egy adott 𝑛-ből az 1-hez vezetnek,
karakterisztikának nevezzük. Írjunk programot, amely meghatározza azt az 𝑛
számot, amely az [𝑥, 𝑦] intervallumhoz tartozik és amelynek a karakterisztikája
a legnagyobb!
*/

#include <iostream>
using namespace std;

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    int x, y;
    cin >> x, y;
    return 0;
}