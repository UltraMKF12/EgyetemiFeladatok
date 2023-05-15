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
    int height;
    int excess; 

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

void elofolyam_init(vector<csomopont>& csomopontok, vector<el>& elek, int forras, int nyelo)
{
    for (int i = 1; i < csomopontok.size(); i++)
    {
        csomopontok[i].height = 0;
        csomopontok[i].excess = 0;
    }

    for (int i = 0; i < elek.size(); i++)
    {
        elek[i].flow = 0;
    }

    csomopontok[forras].height = csomopontok.size()-1; // mert 1 tol szamolunk, 1 el nagyobb a vektor
    
    for(el* jelenlegi_el : csomopontok[forras].kifele)
    {
        jelenlegi_el->flow = jelenlegi_el->kapacitas;
        jelenlegi_el->kovetkezo->excess = jelenlegi_el->kapacitas;
        jelenlegi_el->jelenlegi->excess -= jelenlegi_el->kapacitas;
    }
}

void pumpalas_elofolyam(vector<csomopont>& csomopontok, vector<el>& elek, int forras, int nyelo)
{
    elofolyam_init(csomopontok, elek, forras, nyelo);
    bool volt_e_muvelet;
    do
    {   
        volt_e_muvelet = false;
        for(int i = 1; i < csomopontok.size(); i++)
        {
            if(csomopontok[i].id != forras && csomopontok[i].id != nyelo && csomopontok[i].excess > 0)
            {
                for (el* jelenlegi_el : csomopontok[i].kifele)
                {
                    if(jelenlegi_el->kapacitas - jelenlegi_el->flow > 0 &&
                       jelenlegi_el->jelenlegi->height == jelenlegi_el->kovetkezo->height + 1)
                       {
                            //Pumpalas
                            int delta_f = min(jelenlegi_el->jelenlegi->excess, jelenlegi_el->kapacitas - jelenlegi_el->flow);
                            
                            jelenlegi_el->flow += delta_f;

                            jelenlegi_el->jelenlegi->excess -= delta_f;
                            jelenlegi_el->kovetkezo->excess += delta_f; 

                            volt_e_muvelet = true;
                       }
                }
            }
        }

        for(int i = 1; i < csomopontok.size(); i++)
        {
            if(csomopontok[i].id != forras && csomopontok[i].id != nyelo && csomopontok[i].excess > 0)
            {
                int min_height = INT_MAX;
                for (el* jelenlegi_el : csomopontok[i].kifele)
                {
                    if(jelenlegi_el->jelenlegi->height <= jelenlegi_el->kovetkezo->height)
                       {
                            //Emeles
                            min_height = min(min_height, jelenlegi_el->kovetkezo->height);
                            volt_e_muvelet = true;
                       }
                }
                if(volt_e_muvelet)
                {
                    csomopontok[i].height = 1 + min_height;
                }
            }
        }
    }while(volt_e_muvelet);
}


int main()
{
    freopen("2_be.txt", "r", stdin);
    freopen("2_ki.txt", "w", stdout);
    // freopen("2_ki.txt", "w", stdout);
    int n, forras, nyelo;
    cin >> n >> forras >> nyelo;

    vector<csomopont> csomopontok(n+1);
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i] = {i, 0, 0};
    }
    vector<el> elek;
    graf_beolvas(csomopontok, elek);

    pumpalas_elofolyam(csomopontok, elek, forras, nyelo);
    cout << csomopontok[nyelo].excess;

    return 0;
}