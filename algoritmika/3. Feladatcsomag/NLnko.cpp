// Széri József - sjim2307
//NLnko
/*
Írjuk ki 𝑛 darab természetes szám legnagyobb közös osztóját!
*/

#include <iostream> 
using namespace std;

unsigned long long lnko(unsigned long long szam1, unsigned long long szam2)
{
    // Ha 0 az egyik szam, visszateritjuk a nagyobbikat.
    if(szam1 == 0 || szam2 == 0)
    {
        return (szam1 > szam2) ? szam1 : szam2;
    }

    while(szam1 != szam2)
    {
        if(szam1 > szam2)
        {
            szam1 -= szam2;
        }
        else
        {
            szam2 -= szam1;
        }
    }

    return szam1;
}

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    int darabszam;
    cin >> darabszam;

    unsigned long long szam;
    unsigned long long eredmeny = 0;
    for (int i = 0; i < darabszam; i++)
    {
        cin >> szam;
        eredmeny = lnko(szam, eredmeny);
    }
    
    cout << eredmeny;
    return 0;
}