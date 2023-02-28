// Széri József - sjim2307
//Motel
/*
Az Encián motelben évekkel előre is fogadnak foglalásokat az odaérkező
𝑛 turistacsoport számára. Ismervén a napot, amellyel kezdve foglalni lehet
és amelyet 1-el számozunk, a csoportok megjelölik az első és az utolsó napot,
amelyet a motelben szeretnének tölteni. Az Encián tulajdonosa mindegyik
csoport számára szeretne egy tradicionális előadást szervezni, amire csak a motel
dísztermében kerülhet sor, ahova egyszerre csak egy turistacsoport fér be. Ezeken
az előadásokon fel fog lépni egy előadó, aki megszabja azt az 𝑛 napot, amikor
el tud jönni az előadásokra. Segítsetek a tulajdonosnak eldönteni, hogy melyik
turistacsoportnak melyik napra szervezze meg az előadást.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct turista_csoport
{
    int kezdet;
    int veg;
    int id;
};

struct eloadas_datum
{
    int nap;
    int id;
};

bool rendez_veg_struct(const turista_csoport &a, const turista_csoport &b)
{
    return a.veg > b.veg;
}

bool rendez_nap_struct(const eloadas_datum &a, const eloadas_datum &b)
{
    return a.nap > b.nap;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //BEOLVASAS
    int n;
    cin >> n;
    vector<turista_csoport> turista_csoportok;
    vector<eloadas_datum> eloadas_datumok;
    for (int i = 0; i < n; i++)
    {
        int elso, masodik;
        cin >> elso >> masodik;
        turista_csoportok.push_back({elso, masodik, i+1});
    }
    for (int i = 0; i < n; i++)
    {
        int nap;
        cin >> nap;
        eloadas_datumok.push_back({nap, i+1});
    }
    
    //Rendezni kell csokkeno sorrendbe a dolgokat.
    sort(turista_csoportok.begin(), turista_csoportok.end(), rendez_veg_struct);
    sort(eloadas_datumok.begin(), eloadas_datumok.end(), rendez_nap_struct);

    vector<turista_csoport> eredmeny;
    for (int i = 0; i < n; i++)
    {
        if(turista_csoportok[i].veg >= eloadas_datumok[i].nap && turista_csoportok[i].kezdet <= eloadas_datumok[i].nap)
        {
            eredmeny.push_back({turista_csoportok[i].id, eloadas_datumok[i].id, i});
        }
        else
        {
            break;
        }
    }

    if(eredmeny.size() == n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << eredmeny[i].kezdet << " " << eredmeny[i].veg << endl;
        }
        
    }
    else
    {
        cout << "0 0";
    }
    

    return 0;
}