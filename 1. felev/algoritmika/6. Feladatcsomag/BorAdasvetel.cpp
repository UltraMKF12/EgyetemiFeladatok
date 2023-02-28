// Széri József - sjim2307
//BorAdasvetel
/*
Egy falu főútcáján 𝑛 lakos él, minden két egymás melletti ház között
ugyanakkora a távolság. A falu jó bortermő vidéken található, így a lakók
szívesen fogyasztanak, de adnak is el bort. Érdekes módon a falun belül a
kereslet és a kínálat mindig egyenlő. Tudván, hogy két egymás melletti ház
között szállítani egy liter bort mindig egy egységnyi munkába kerül és ismervén,
hogy melyik lakos hány liter bort szeretne eladni vagy vásárolni, határozzuk
meg a minimális munkamennyiséget, amely szükséges ahhoz, hogy minden lakos
igénye ki legyen elégítve.*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n;
    cin >> n;

    vector<long long> lakosok_bor_igenyei(n);
    for (int i = 0; i < n; i++)
    {
        cin >> lakosok_bor_igenyei[i];
    }
    
    unsigned long long minimalis_munka = 0;

    // Mindig hozzáadjuk az eredményhez, hogy hány bort cipeltünk át a másik házhoz, majd onnan mennyit a következőhöz.
    // Ezért kell az Abszolút érték mindig
    for (int i = 0; i < n-1; i++)
    {
        minimalis_munka += abs(lakosok_bor_igenyei[i]);
        lakosok_bor_igenyei[i+1] += lakosok_bor_igenyei[i];
    }
    
    cout << minimalis_munka;
    return 0;
}