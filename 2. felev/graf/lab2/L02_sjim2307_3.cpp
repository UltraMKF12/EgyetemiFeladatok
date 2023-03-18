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
    }
}

void clear_visit(vector<csomopont> &csomopontok)
{
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i].volt_mar = false;
    }
}

void dfs_visit_kor(vector<csomopont> &csomopontok, int jelenlegi, bool &kor)
{
    csomopontok[jelenlegi].volt_mar = true;
    for (int i = 0; i < csomopontok[jelenlegi].kifele.size(); i++)
    {
        if(!csomopontok[jelenlegi].kifele[i]->volt_mar)
        {
            dfs_visit_kor(csomopontok, csomopontok[jelenlegi].kifele[i]->id, kor);
        }
        else
        {
            kor = true;
        }
    }
}

bool dfs_kor(vector<csomopont> &csomopontok)
{
    for (int i = 1; i < csomopontok.size(); i++)
    {
        clear_visit(csomopontok);
        
        bool kor = false;
        dfs_visit_kor(csomopontok, i, kor);

        if (kor) return true;
    }

    return false;
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
    cout << (dfs_kor(csomopontok) ? "igen" : "nem");
    
    return 0;
}