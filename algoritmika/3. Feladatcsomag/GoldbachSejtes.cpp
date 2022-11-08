// Széri József - sjim2307
//GoldbachSejtes
/*
Írjunk algoritmust, amely egy adott 𝑥 páros számot felír két különböző
prímszám összegeként (Goldbach-sejtés).
*/

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<bool> prim_szita_generator(unsigned int szam)
{
    //Legeneralja az osszes primszamot szam-ig
    vector<bool> primszamok(szam+1, true);
    primszamok[0] = false;
    primszamok[1] = false;

    unsigned int szam_gyok = sqrt(szam);
    for (unsigned int i = 2; i <= szam_gyok; i++)
    {
        if(primszamok[i])
        {
            for (int j = i*i; j <= szam; j += i)
            {
                primszamok[j] = false;
            }
            
        }
    }
    
    return primszamok;
}

void szita_primekbe(vector<bool> szita, vector<unsigned int> &vektor)
{
    int szita_hossz = szita.size();
    for (int i = 0; i < szita_hossz; i++)
    {
        if(szita[i])
        {
            vektor.push_back(i);
        }
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //Beolvasas
    unsigned int szam;
    cin >> szam;

    //Primszamok legeneralasa
    vector<unsigned int> primek;
    szita_primekbe(prim_szita_generator(szam), primek);

    //Kivalasztani a primeket
    unsigned int szam1, szam2;
    int primek_hossz = primek.size();
    for(int i = 1; i < primek_hossz-1; i++) // X garantaltan paros, ezert nem kell a 2-es primszam
    {
        for (int j = i+1; j < primek_hossz; j++)
        {
            if(primek[i] + primek[j] == szam)
            {
                szam1 = primek[i];
                szam2 = primek[j];
                break;
            }
        }
        
    }

    cout << szam << " = " << szam1 << " + " << szam2;
    return 0;
}