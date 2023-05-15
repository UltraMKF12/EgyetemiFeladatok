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


int main()
{
    freopen("3_be.txt", "r", stdin);
    // freopen("1_ki.txt", "w", stdout);
    int n, forras, nyelo;
    cin >> n >> forras >> nyelo;

    vector<csomopont> csomopontok(n+1);
    for (int i = 0; i < csomopontok.size(); i++)
    {
        csomopontok[i] = {i, false, nullptr, nullptr};
    }
    vector<el> elek;
    graf_beolvas(csomopontok, elek);

    return 0;
}