// Széri József - sjim2307
//Torony
/*
Legyen 𝑛 építőkocka, amelyek 1-től 𝑛-ig vannak címkézve. Beolvassuk az
oldalaik hosszát és a színüket. Írjunk ki minden 𝑘 kockából álló tornyot, amelyeket
úgy építhetünk fel, hogy nem teszünk egymásra azonos színű kockát és oldalaik
mérete (lentről felfele) szigorúan csökkenő sorozatot alkotnak.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct kocka
{
    string szin;
    unsigned int hossz;
};

//Structok rendezésére kell egy speciális összehasonlító függvény
bool kocka_hossz_osszehasonlitas(const kocka &elso, const kocka &masodik)
{
    return elso.hossz < masodik.hossz;
}

void torony_generalas(const vector<kocka> &kockak, vector<int>torony, int melyseg, int max_magassag, int &darab, kocka elozo)
{
    if(melyseg == max_magassag)
    {
        darab++;
        for (int i = 0; i < melyseg; i++)
        {
            cout << torony[i] << " ";
        }
        cout << endl;
    }

    else
    {
        for (int i = 0; i < kockak.size(); i++)
        {
            if(melyseg == 0 || (kockak[i].szin != elozo.szin && kockak[i].hossz < elozo.hossz))
            {
                torony[melyseg] = kockak[i].hossz;
                torony_generalas(kockak, torony, melyseg+1, max_magassag, darab, kockak[i]);
            }
        }
        
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //Beolvasas
    int kockak_szama, max_magassag;
    cin >> kockak_szama >> max_magassag;

    vector<kocka> kockak;
    for (int i = 0; i < kockak_szama; i++)
    {
        string szin;
        int hossz;
        cin >> szin >> hossz;

        kocka temp;
        temp.szin = szin;
        temp.hossz = hossz;

        kockak.push_back(temp);
    }
    
    //Rendezni kell növekvő sorrendben a kockákat.
    //c++ algorithm sort-ot fogok használni, mivel a feladatnak a lényege a rekurzió és nem a sort.
    sort(kockak.begin(), kockak.end(), kocka_hossz_osszehasonlitas);

    vector<int>torony(max_magassag, 0);
    int darab = 0;

    torony_generalas(kockak, torony, 0, max_magassag, darab, kockak[0]);
    if(darab == 0)
    {
        cout << -1;
    }

    return 0;
}