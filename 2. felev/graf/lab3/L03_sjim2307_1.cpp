//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <queue>
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

struct rendezes
{   
    bool operator()(const el &elso, const el &masodik)
    {
        return elso.suly > masodik.suly;
    }
};

void prim_feszitofa(vector<csomopont> &csomopontok, int kezdet, vector<el> &elek, int &osszeg)
{
    priority_queue<el, vector<el>, rendezes> sor; 
    for(el vonal : csomopontok[kezdet].kifele)
    {
        sor.push(vonal);
    }

    csomopontok[kezdet].volt_mar = true;

    while(!sor.empty())
    {
        el jelenlegi = sor.top();
        sor.pop();

        if(!jelenlegi.vegpont->volt_mar)
        {
            jelenlegi.vegpont->volt_mar = true;
            osszeg += jelenlegi.suly;

            elek.push_back(jelenlegi);

            for(el vonal : csomopontok[jelenlegi.vegpont->id].kifele)
            {
                if(!vonal.vegpont->volt_mar)
                {
                    sor.push(vonal);
                }
            }
        }
    }
}

int main()
{
    freopen("graf.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<csomopont> csomopontok(n+1);
    for(int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i] = {i, false};
    }
    graf_beolvas(m, csomopontok);
    
    
    int osszeg = 0;
    vector<el> elek;
    prim_feszitofa(csomopontok, 1, elek, osszeg);
    cout << "Koltseg: " << osszeg << endl;
    for (int i = 0; i < elek.size(); i++)
    {
        cout << elek[i].kezdopont->id << " - " << elek[i].vegpont->id << ": " << elek[i].suly << endl;
    }
    
    return 0;
}