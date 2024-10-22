//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


struct csomopont
{
    int id;
    bool volt_mar;
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

// void kiir_szomszedsagi_lista(vector<csomopont> &csomopontok)
// {
//     for (int i = 1; i < csomopontok.size(); i++)
//     {
//         cout << i << ": ";
//         for (int j = 0; j < csomopontok[i].kifele.size(); j++)
//         {
//             cout << csomopontok[i].kifele[j]->id;
//             if(csomopontok[i].kifele[j]->volt_mar) cout << "(!)";
//             cout << " ";
//         }
//         cout << endl;
//     }
// }

void clear_visit(vector<csomopont> &csomopontok)
{
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i].volt_mar = false;
    }
}

void dfs_visit(vector<csomopont> &csomopontok, vector<int> &csucsok, int jelenlegi)
{
    csomopontok[jelenlegi].volt_mar = true;
    csucsok.push_back(jelenlegi);
    for (int i = 0; i < csomopontok[jelenlegi].kifele.size(); i++)
    {
        if(!csomopontok[jelenlegi].kifele[i]->volt_mar)
        {
            dfs_visit(csomopontok, csucsok, csomopontok[jelenlegi].kifele[i]->id);
        }
    }
}

void dfs(vector<csomopont> &csomopontok, vector<int> &csucsok, int kezdet)
{
    clear_visit(csomopontok);
    dfs_visit(csomopontok, csucsok, kezdet);
}


void bfs(vector<csomopont> &csomopontok, vector<int> &csucsok, int kezdet)
{
    clear_visit(csomopontok);
    queue<csomopont*> sor;
    sor.push(&csomopontok[kezdet]);
    csomopontok[kezdet].volt_mar = true;
    csucsok.push_back(kezdet);
    sor.front()->volt_mar = true;

    while (!sor.empty())
    {
        csomopont *kovetkezo = sor.front();
        sor.pop();
        csucsok.push_back(kovetkezo->id);
        for (int i = 0; i < kovetkezo->kifele.size(); i++)
        {
            if(!kovetkezo->kifele[i]->volt_mar)
            {
                sor.push(kovetkezo->kifele[i]);
                kovetkezo->kifele[i]->volt_mar = true;
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
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i] = {i, false};
    }
    
    graf_beolvas(m, csomopontok);
    // kiir_szomszedsagi_lista(csomopontok);

    cout << "Melysegi bejaras: ";
    vector<int> melysegi_csucsok;
    dfs(csomopontok, melysegi_csucsok, 1);
    for (int i = 0; i < melysegi_csucsok.size(); i++)
    {
        cout << melysegi_csucsok[i] << " ";
    }
    cout << endl;


    cout << "Szelessegi bejaras: ";
    vector<int> szelessegi_csucsok;
    bfs(csomopontok, szelessegi_csucsok, 1);
    for (int i = 1; i < szelessegi_csucsok.size(); i++)
    {
        cout << szelessegi_csucsok[i] << " ";
    }
    
    return 0;
}