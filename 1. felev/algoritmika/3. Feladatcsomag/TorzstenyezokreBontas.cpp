// Széri József - sjim2307
//TorzstenyezokreBontas
/*
Bontsunk törzstényezőkre egy adott természetes számot!
*/

#include <iostream> 
#include <vector>
using namespace std;


void kiszamit_torzstenyezok(unsigned long szam, vector<unsigned long> &torzstenyezok)
{
    unsigned int szam_masolat = szam;
    unsigned int oszto = 2;
    int hanyszor;
    while(szam_masolat != 1)
    {
        hanyszor = 0;
        while (szam_masolat % oszto == 0)
        {
            szam_masolat /= oszto;
            hanyszor++;
        }
        if(hanyszor > 0)
        {
            torzstenyezok.push_back(oszto);
            torzstenyezok.push_back(hanyszor);
        }

        oszto++;
    }
}

void kiir_torzstenyezok(const vector<unsigned long> &torzstenyezok)
{
    int torzstenyezok_meret = torzstenyezok.size();
    for (int i = 0; i < torzstenyezok_meret; i += 2)
    {
        if (i != 0)
        {
            cout << "*";
        }

        cout << torzstenyezok[i];

        if(torzstenyezok[i+1] > 1)
        {
            cout << "^" << torzstenyezok[i+1];
        }
    }
    
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned long szam;
    cin >> szam;

    // A vektorban a törzstényezőt és az előforduálsi számát tároljuk.
    // v[0] = szam
    // v[1] = hanyszor
    vector<unsigned long> torzstenyezok;

    kiszamit_torzstenyezok(szam, torzstenyezok);
    kiir_torzstenyezok(torzstenyezok);

    return 0;
}