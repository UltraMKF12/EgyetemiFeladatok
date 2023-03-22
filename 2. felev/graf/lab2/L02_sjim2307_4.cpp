//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct csomopont
{
    int id;
    bool volt_mar;
    vector<csomopont*> befele;
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
        csomopontok[masodik].befele.push_back(&csomopontok[elso]);

        //Iranyitatlan
        csomopontok[masodik].kifele.push_back(&csomopontok[elso]);
        csomopontok[elso].befele.push_back(&csomopontok[masodik]);
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

    
    return 0;
}