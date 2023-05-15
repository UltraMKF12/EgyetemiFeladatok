//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct el;
struct csomopont
{
    int id;
    bool latogatott;
    csomopont* elozo;
    el* elozo_el;
    vector<el*> kifele;
};

struct el
{
    int flow;
    int kapacitas;

    csomopont* jelenlegi;
    csomopont* kovetkezo;
};

void graf_beolvas(vector<csomopont> &csomopontok, vector<el>& elek)
{
    int elso, masodik, kapacitas;
    while (cin >> elso >> masodik >> kapacitas)
    {
        elek.push_back({0, kapacitas, &csomopontok[elso], &csomopontok[masodik]});

    }
    for (int i = 0; i < elek.size(); i++)
    {
        csomopontok[elek[i].jelenlegi->id].kifele.push_back(&elek[i]);
    }
}

void clear_visit(vector<csomopont> &csomopontok)
{
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i].elozo = nullptr;
        csomopontok[i].elozo_el = nullptr;
    }
}

int Edmonds_Karp(vector<csomopont> &csomopontok, vector<el>& elek, int forras, int nyelo)
{
    int flow = 0;

    do
    {
        clear_visit(csomopontok);
        queue<csomopont*> sor;
        sor.push(&csomopontok[forras]);
        csomopontok[forras].latogatott = true;

        while (!sor.empty())
        {
            csomopont *jelenlegi_csomopont = sor.front();
            sor.pop();
            for(el* jelenlegi_el : jelenlegi_csomopont->kifele)
            {
                if(jelenlegi_el->kovetkezo->elozo == nullptr &&
                   jelenlegi_el->kovetkezo->id != forras &&
                   jelenlegi_el->kapacitas > jelenlegi_el->flow)
                {
                        jelenlegi_el->kovetkezo->elozo = jelenlegi_el->jelenlegi;
                        jelenlegi_el->kovetkezo->elozo_el = jelenlegi_el;
                        sor.push(jelenlegi_el->kovetkezo);
                }
            }
        }

        if(csomopontok[nyelo].elozo != nullptr)
        {
            int folyamat_novekedes = INT_MAX;
            for(el *jelenlegi_el = csomopontok[nyelo].elozo_el; 
                    jelenlegi_el != nullptr; 
                    jelenlegi_el = jelenlegi_el->jelenlegi->elozo_el)
            {
                folyamat_novekedes = min(folyamat_novekedes, jelenlegi_el->kapacitas - jelenlegi_el->flow);
                jelenlegi_el->jelenlegi->latogatott = true;
                jelenlegi_el->kovetkezo->latogatott = true;
            }

            for(el *jelenlegi_el = csomopontok[nyelo].elozo_el; 
                    jelenlegi_el != nullptr; 
                    jelenlegi_el = jelenlegi_el->jelenlegi->elozo_el)
            {
                jelenlegi_el->flow += folyamat_novekedes;
                //visszael
            }

            flow += folyamat_novekedes;
        }
    }while(csomopontok[nyelo].elozo != nullptr);

    return flow;
}


int main()
{
    freopen("1_be.txt", "r", stdin);
    freopen("1_ki.txt", "w", stdout);
    int n, forras, nyelo;
    cin >> n >> forras >> nyelo;

    vector<csomopont> csomopontok(n+1);
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i] = {i, false, nullptr, nullptr};
    }
    vector<el> elek;
    graf_beolvas(csomopontok, elek);

    cout << Edmonds_Karp(csomopontok, elek, forras, nyelo) << endl;
    for (int i = 1; i < csomopontok.size(); i++)
    {
        if(csomopontok[i].latogatott)
        {
            cout << csomopontok[i].id << " ";
        }
    }

    cout << "; ";

    for (int i = 1; i < csomopontok.size(); i++)
    {
        if(!csomopontok[i].latogatott)
        {
            cout << csomopontok[i].id << " ";
        }
    }

    return 0;
}