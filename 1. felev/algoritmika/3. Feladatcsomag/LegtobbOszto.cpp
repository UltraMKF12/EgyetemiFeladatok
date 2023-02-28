// Széri József - sjim2307
//LegtobbOszto
/*
Keressük meg adott számmal bezárólag a legtöbb osztójú természetes számot!
*/

#include <iostream> 
using namespace std;

int szam_osztoinak_szama(int szam)
{
    int osztok_szama = 0;
    for (int i = 2; i <= szam/2; i++)
    {
        if(szam % i == 0)
        {
            osztok_szama++;
        }
    }
    
    osztok_szama += 2; // Önmaga + 1
    return osztok_szama;
}

void legtobb_osztoju_szam(int szam_hatar, int &legnagyobb_szam, int &osztok_szama)
{
    legnagyobb_szam = 1;
    osztok_szama = 1;

    for (int i = 2; i <= szam_hatar; i+=2)
    {
        int jelenlegi_osztok_szama = szam_osztoinak_szama(i);
        if(jelenlegi_osztok_szama > osztok_szama)
        {
            legnagyobb_szam = i;
            osztok_szama = jelenlegi_osztok_szama;
        }
    }

    //Visszatéríteni a valódi osztót
    if(osztok_szama > 1)
    {
        osztok_szama -= 2; // Önmaga és 1
    }
    else
    {
        osztok_szama--; // 1
    }
}


int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int szam;
    cin >> szam;

    int legnagyobb_szam, osztok_szama;
    legtobb_osztoju_szam(szam, legnagyobb_szam, osztok_szama);

    cout << legnagyobb_szam << " " << osztok_szama;
    return 0;
}