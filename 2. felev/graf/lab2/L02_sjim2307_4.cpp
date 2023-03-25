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

void dfs_visit_topological(vector<csomopont> &csomopontok, vector<int> &csucsok, int jelenlegi)
{
    csomopontok[jelenlegi].volt_mar = true;
    for (int i = 0; i < csomopontok[jelenlegi].kifele.size(); i++)
    {
        if(!csomopontok[jelenlegi].kifele[i]->volt_mar)
        {
            dfs_visit_topological(csomopontok, csucsok, csomopontok[jelenlegi].kifele[i]->id);
        }
    }
    csucsok.push_back(jelenlegi);
}

void dfs_topological(vector<csomopont> &csomopontok, vector<int> &csucsok)
{
    clear_visit(csomopontok);
    for (int i = 0; i < csomopontok.size(); i++)
    {
        if(!csomopontok[i].volt_mar)
        {
            dfs_visit_topological(csomopontok, csucsok, csomopontok[i].id);
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

    vector<int> rendezett_csucsok;
    dfs_topological(csomopontok, rendezett_csucsok);
    for (int i = rendezett_csucsok.size()-1; i > 0; i--)
    {
        cout << rendezett_csucsok[i] << " ";
    }
    cout << endl;
    
    return 0;
}