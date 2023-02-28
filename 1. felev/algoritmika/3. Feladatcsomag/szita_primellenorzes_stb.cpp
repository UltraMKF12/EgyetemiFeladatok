#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<bool> prim_szita_generator(unsigned long szam)
{
    //Legeneralja az osszes primszamot szam-ig
    vector<bool> primszamok(szam+1, true);
    primszamok[0] = false;
    primszamok[1] = false;

    unsigned int szam_gyok = sqrt(szam);
    for (unsigned long i = 2; i <= szam_gyok; i++)
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

void szita_primekbe(const vector<bool> &szita, vector<unsigned long> &vektor)
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

bool prim_e(unsigned long szam)
{
    if(szam <= 1)
    {
        return false;
    }
    else if(szam % 2 == 0)
    {
        return (szam == 2);
    }
    else
    {
        unsigned long gyok = sqrt(szam);
        for (int i = 3; i <= gyok; i += 2)
        {
            if(szam % i == 0)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //Beolvasas
    unsigned long szam;
    cin >> szam;

    //Primszamok legeneralasa
    vector<unsigned long> primek;
    szita_primekbe(prim_szita_generator(szam), primek);

    //Primek kiiratasa
    int primek_hossz = primek.size();
    for (int i = 0; i < primek_hossz; i++)
    {
        cout << primek[i] << "-" << prim_e(primek[i]) << "  ";
    }
    
    cout << endl;

    cout << prim_e(9977);

    return 0;
}