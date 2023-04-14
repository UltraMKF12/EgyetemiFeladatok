//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct csomopont
{
    int id;
    int index;
    int lowlink;
    bool on_stack;
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

void strongconnect(csomopont *pont, stack<csomopont*> &verem, int &index, vector<vector<int>> &komponensek, vector<csomopont> &csomopontok)
{
    pont->index = index;
    pont->lowlink = index;
    index++;
    verem.push(pont);
    pont->on_stack = true;

    for (int i = 0; i < pont->kifele.size(); i++)
    {
        csomopont *uj = pont->kifele[i];
        if(uj->index == -1)
        {
            strongconnect(uj, verem, index, komponensek, csomopontok);
            pont->lowlink = min(pont->lowlink, uj->lowlink);
        }
        else if(uj->on_stack)
        {
            pont->lowlink = min(pont->lowlink, uj->index);
        }
    }

    if(pont->lowlink == pont->index)
    {
        komponensek.resize(komponensek.size()+1);
        while(!verem.empty() && verem.top()->index >= pont->index)
        {   
            komponensek[komponensek.size()-1].push_back(verem.top()->id);
            csomopontok[verem.top()->index].on_stack = false;
            verem.pop();
        }
    }
}

void tarjan(vector<csomopont> &csomopontok, vector<vector<int>> &komponensek)
{
    int index = 1;
    stack<csomopont*> verem;

    for (int i = 1; i < csomopontok.size(); i++)
    {
        if(csomopontok[i].index == -1)
        {
            strongconnect(&csomopontok[i], verem, index, komponensek, csomopontok);
        }
    }
}

int main()
{
    freopen("graf2.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<csomopont> csomopontok(n+1);
    for(int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i] = {i, -1, -1, false};
    }
    graf_beolvas(m, csomopontok);
    
    vector<vector<int>> komponensek;
    tarjan(csomopontok, komponensek);

    for (int i = 0; i < komponensek.size(); i++)
    {
        for (int j = 0; j < komponensek[i].size(); j++)
        {
            cout << komponensek[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}