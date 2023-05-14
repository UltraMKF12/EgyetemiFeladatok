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
    int ertek;
    bool latogatott;
    csomopont* elozo;
    vector<el*> kifele;
};

struct el
{
    int suly;
    csomopont* jelenlegi;
    csomopont* kovetkezo;
};

void graf_beolvas(int m, vector<csomopont> &csomopontok, vector<el>& elek)
{
    int elso, masodik, suly;
    for (int i = 0; i < m; i++)
    {
        cin >> elso >> masodik >> suly;

        //El lista
        elek[i].suly = suly;
        elek[i].jelenlegi = &csomopontok[elso];
        elek[i].kovetkezo = &csomopontok[masodik];

        // //Iranyitott
        csomopontok[elso].kifele.push_back(&elek[i]);
    }
}

struct rendezes
{   
    bool operator()(const csomopont* elso, const csomopont* masodik)
    {
        return elso->ertek > masodik->ertek;
    }
};


void init_s(vector<csomopont>& csomopontok, int kezdopont)
{
    for (int i = 1; i < csomopontok.size(); i++)
    {
        csomopontok[i].ertek = INT_MAX;
        csomopontok[i].elozo = nullptr;
        csomopontok[i].latogatott = false;
    }
    csomopontok[kezdopont].ertek = 0;
    csomopontok[kezdopont].latogatott = true;
}

void relax(el& vonal)
{
    if(vonal.jelenlegi->latogatott &&
       vonal.kovetkezo->ertek > vonal.jelenlegi->ertek + vonal.suly)
    {
        vonal.kovetkezo->ertek = vonal.jelenlegi->ertek + vonal.suly;
        vonal.kovetkezo->elozo = vonal.jelenlegi;
        
        vonal.kovetkezo->latogatott = true;
    }
}

void Dijkstra_queue(vector<csomopont>& csomopontok, int kezdopont)
{
    init_s(csomopontok, kezdopont);
    priority_queue<csomopont*, vector<csomopont*>, rendezes> sor;
    for (int i = 1; i < csomopontok.size(); i++)
    {
        sor.push(&csomopontok[i]);
    }
    
    while(!sor.empty())
    {
        csomopont* legkisebb = sor.top();
        sor.pop();

        for (int i = 0; i < legkisebb->kifele.size(); i++)
        {
            relax(*legkisebb->kifele[i]);
        }
    }
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
    vector<el> elek(m);
    for (int i = 0; i < m; i++)
    {
        elek[i] = {0, nullptr, nullptr};
    }
    graf_beolvas(m, csomopontok, elek);

    Dijkstra_queue(csomopontok, kezdopont);

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
    
    return 0;
}