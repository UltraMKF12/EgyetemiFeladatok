//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct csomopont
{
    int id;
    bool volt_mar;
    bool szinezett;
    vector<csomopont*> kifele;
};

void graf_beolvas(int m, vector<csomopont> &csomopontok)
{
    int elso, masodik;
    for (int i = 0; i < m; i++)
    {
        cin >> elso >> masodik;

        //Iranyitott
        csomopontok[elso].kifele.push_back(&csomopontok[masodik]);

        //Iranyitatlan
        csomopontok[masodik].kifele.push_back(&csomopontok[elso]);
    }
}

void clear_visit(vector<csomopont> &csomopontok)
{
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i].volt_mar = false;
    }
}

bool bfs_paros_e(vector<csomopont> &csomopontok, int kezdet)
{
    clear_visit(csomopontok);
    queue<csomopont*> sor;
    sor.push(&csomopontok[kezdet]);
    csomopontok[kezdet].volt_mar = true;
    sor.front()->volt_mar = true;
    sor.front()->szinezett = false;

    while (!sor.empty())
    {
        csomopont *jelenlegi = sor.front();
        sor.pop();
        for (int i = 0; i < jelenlegi->kifele.size(); i++)
        {
            if(!jelenlegi->kifele[i]->volt_mar)
            {
                sor.push(jelenlegi->kifele[i]);
                jelenlegi->kifele[i]->volt_mar = true;
                jelenlegi->kifele[i]->szinezett = !jelenlegi->szinezett;
            }
            else if(jelenlegi->szinezett == jelenlegi->kifele[i]->szinezett)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    freopen("graf.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<csomopont> csomopontok(n+1);
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i] = {i, false, false};
    }
    
    graf_beolvas(m, csomopontok);
    cout << (bfs_paros_e(csomopontok, 1) ? "igen" : "nem");


    return 0;
}