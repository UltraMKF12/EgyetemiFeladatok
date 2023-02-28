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
#include <vector>
using namespace std;

int karakterisztika_szamitas(int szam)
{
    int karakterisztika = 0;
    while(szam != 1)
    {
        karakterisztika++;
        if(szam % 2 == 0)
        {
            szam /= 2;
        }
        else
        {
            szam = szam*3 + 1;
        }
    }

    return karakterisztika;
}

void maximum_karakterisztika_intervallum(int elso, int masodik, int &szam_eredmeny, int &karakterisztika_eredmeny)
{
    int maximum_szam = elso;
    int maximum_karakterisztika = karakterisztika_szamitas(elso);

    for (int i = elso+1; i <= masodik; i++)
    {
        int temp_karakterisztika = karakterisztika_szamitas(i);
        if(temp_karakterisztika >= maximum_karakterisztika)
        {
            maximum_karakterisztika = temp_karakterisztika;
            maximum_szam = i;
        }
    }
    
    szam_eredmeny = maximum_szam;
    karakterisztika_eredmeny = maximum_karakterisztika;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int x, y;
    cin >> x >> y;

    int szam;
    int karakterisztika;
    maximum_karakterisztika_intervallum(x, y, szam, karakterisztika);

    cout << szam << " " << karakterisztika;

    return 0;
}