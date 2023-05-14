//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
using namespace std;

struct el;
struct csomopont
{
    int id;
    int ertek;
    bool latogatott;
    csomopont* elozo;
    vector<el> kifele;
};

struct el
{
    int suly;
    csomopont* jelenlegi;
    csomopont* kovetkezo;
};

void graf_beolvas(int m, vector<csomopont> &csomopontok)
{
    int elso, masodik, suly;
    for (int i = 0; i < m; i++)
    {
        cin >> elso >> masodik >> suly;

        el vonal;
        vonal.suly = suly;
        vonal.jelenlegi = &csomopontok[elso];
        vonal.kovetkezo = &csomopontok[masodik];
        //Iranyitott
        csomopontok[elso].kifele.push_back(vonal);
    }
}

int main()
{

    return 0;
}