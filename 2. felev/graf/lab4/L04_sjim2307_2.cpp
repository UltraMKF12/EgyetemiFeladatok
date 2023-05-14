//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

struct el;
struct csomopont
{
    int id;
    int ertek;
    bool latogatott;
    csomopont* elozo;
    // vector<el> kifele;
};

struct el
{
    int suly;
    csomopont* jelenlegi;
    csomopont* kovetkezo;
};

void graf_beolvas(int m, vector<csomopont>& csomopontok, vector<el>& elek)
{
    int elso, masodik, suly;
    for (int i = 0; i < m; i++)
    {
        cin >> elso >> masodik >> suly;

        el vonal;
        vonal.suly = suly;
        vonal.jelenlegi = &csomopontok[elso];
        vonal.kovetkezo = &csomopontok[masodik];

        // //Iranyitott
        // csomopontok[elso].kifele.push_back(vonal);

        // Itt csak élek kellenek
        elek.push_back(vonal);
    }
}

void init_s(vector<csomopont>& csomopontok, int kezdopont)
{
    csomopontok[kezdopont].ertek = 0;
    csomopontok[kezdopont].latogatott = true;
}

void relax(el &vonal)
{
    if(vonal.jelenlegi->latogatott && 
       vonal.kovetkezo->ertek > vonal.jelenlegi->ertek + vonal.suly)
    {
        vonal.kovetkezo->ertek = vonal.jelenlegi->ertek + vonal.suly;
        vonal.kovetkezo->elozo = vonal.jelenlegi;
        
        vonal.kovetkezo->latogatott = true;
    }
}

bool Bellman_Ford(vector<csomopont> &csomopontok, vector<el>& elek, int kezdopont)
{
    init_s(csomopontok, kezdopont);
    for (int i = 0; i < csomopontok.size()-2; i++) // 0-tol szamozzuk, 1-tol hasznaljuk ezert -2
    {
        for (int i = 0; i < elek.size(); i++)
        {
            relax(elek[i]);
        }
    }

    for (int i = 0; i < elek.size(); i++)
    {
        if(elek[i].jelenlegi->latogatott && elek[i].kovetkezo->latogatott && 
           elek[i].kovetkezo->ertek > elek[i].jelenlegi->ertek + elek[i].suly)
        {
            return false;
        }
    }
    
    return true;
}

int main()
{
    freopen("graf.in", "r", stdin);
    int n, m, kezdopont;
    cin >> n >> m >> kezdopont;
    vector<csomopont> csomopontok(n+1);
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i] = {i, INT_MAX, false, nullptr};
    }
    vector<el> elek;
    graf_beolvas(m, csomopontok, elek);

    if(Bellman_Ford(csomopontok, elek, kezdopont))
    {
        for (int i = 1; i < csomopontok.size(); i++)
        {
            if(i != kezdopont)
            {
                if(!csomopontok[i].latogatott)
                {
                    cout << "A legrovidebb ut hossza " << i << " fele: NEM ELERHETO" << endl;
                    cout << "A legrovidebb ut " << i << " fele: NEM ELERHETO" ;
                }
                else
                {
                    cout << "A legrovidebb ut hossza " << i << " fele: " << csomopontok[i].ertek << endl;
                    cout << "A legrovidebb ut " << i << " fele: ";
                    
                    csomopont* jelenlegi = &csomopontok[i];
                    while (jelenlegi->id != kezdopont)
                    {
                        cout << jelenlegi->id << " ";
                        if(jelenlegi->elozo != nullptr)
                        {
                            jelenlegi = jelenlegi->elozo;
                        }
                    }
                    cout << jelenlegi->id; // Kiirni a kezdopontot.
                }
                cout << endl << endl;
            }
        }
    }
    else
    {
        cout << "Van negativ kor";
    }

    return 0;
}