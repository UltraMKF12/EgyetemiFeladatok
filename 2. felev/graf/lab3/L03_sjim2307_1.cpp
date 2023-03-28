//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct el;

struct csomopont
{
    int id;
    bool volt_mar;
    vector<el> kifele;
};

struct el
{
    int suly;
    csomopont *kezdopont;
    csomopont *vegpont;
};

void graf_beolvas(int m, vector<csomopont> &csomopontok)
{
    int elso, masodik, suly;
    for (int i = 0; i < m; i++)
    {
        cin >> elso >> masodik >> suly;

        //Iranyitott
        csomopontok[elso].kifele.push_back({suly, &csomopontok[elso], &csomopontok[masodik]});
        //Iranyitatlan
        csomopontok[masodik].kifele.push_back({suly, &csomopontok[masodik], &csomopontok[elso]});
    }
}

bool rendezes(el* elso, el* masodik)
{
    return elso->suly > masodik->suly;
}

void prim_feszitofa(vector<csomopont> &csomopontok, int kezdet, vector<el> &elek, int osszeg)
{
    vector<el*> lehetseges_utak;
    csomopont *jelenlegi_pont = &csomopontok[kezdet];

    jelenlegi_pont->volt_mar = true;

    while (!lehetseges_utak.empty())
    {
        //Kitorolni a mar rossz elemeket
        for (int i = 0; i < lehetseges_utak.size(); i++)
        {
            if(lehetseges_utak[i]->vegpont->volt_mar)
            {
                lehetseges_utak.erase(lehetseges_utak.begin() + i);
            }
        }
        
        //Hozzadni a listahoz az uj lehetseges eleket.
        for (int i = 0; i < jelenlegi_pont->kifele.size(); i++)
        {
            if(!jelenlegi_pont->kifele[i].vegpont->volt_mar)
            {
                lehetseges_utak.push_back(&jelenlegi_pont->kifele[i]);
            }
        }
        
        //Kivalasszuk a legrovidebb utat // A vegere tesszuk
        sort(lehetseges_utak.begin(), lehetseges_utak.end(), rendezes);

        el *jo_el = lehetseges_utak.back();
        lehetseges_utak.pop_back();

        jelenlegi_pont = jo_el->vegpont;
        elek.push_back({jo_el->suly, jo_el->kezdopont, jo_el->vegpont});
        osszeg += jo_el->suly;
    }
}

int main()
{
    freopen("graf.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<csomopont> csomopontok(n+1);
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i] = {i, false};
    }
    graf_beolvas(m, csomopontok);

    // for (int i = 1; i < csomopontok.size(); i++)
    // {
    //     cout << csomopontok[i].id << ": ";
    //     for (int j = 0; j < csomopontok[i].kifele.size(); j++)
    //     {
    //         cout << csomopontok[i].kifele[j].vegpont->id << "[" << csomopontok[i].kifele[j].suly << "], ";
    //     }
    //     cout << endl;
    // }
    
    int osszeg;
    vector<el> elek;
    prim_feszitofa(csomopontok, 1, elek, osszeg);
    cout << "Koltseg: " << osszeg << endl;
    for (int i = 0; i < elek.size(); i++)
    {
        cout << elek[i].kezdopont->id << " - " << elek[i].vegpont->id << ": " << elek[i].suly;
    }
    
    return 0;
}