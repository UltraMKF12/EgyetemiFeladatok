// Széri József - sjim2307
//OroszRek
/*
Implementáljuk rekurzívan az orosz szorzás algoritmusát!
*/

#include <iostream> 
using namespace std;

unsigned long long orosz_szorzas(unsigned long long szam1, unsigned long long szam2, unsigned long long eredmeny)
{
    if(szam1 == 0)
    {
        return eredmeny;
    }

    if(szam1 % 2 == 1)
    {
        return orosz_szorzas(szam1 / 2, szam2 * 2, eredmeny + szam2);
    }
    else
    {
        return orosz_szorzas(szam1 / 2, szam2 * 2, eredmeny);
    }

}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned long long szam1, szam2, eredmeny;
    cin >> szam1 >> szam2;
    eredmeny = orosz_szorzas(szam1, szam2, 0);
    cout << eredmeny;


    return 0;
}