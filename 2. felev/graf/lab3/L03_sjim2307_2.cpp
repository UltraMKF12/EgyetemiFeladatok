//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct el
{
    int suly;
    int kezdopont;
    int vegpont;
};

void graf_beolvas(int m, vector<el> &el_sor)
{
    int elso, masodik, suly;
    for (int i = 0; i < m; i++)
    {
        cin >> elso >> masodik >> suly;
        el_sor.push_back({suly, elso, masodik});
    }
}

bool rendezes(const el &elso, const el &masodik)
{
    return elso.suly < masodik.suly;
}


int halmaz_kereses(int id, const vector<int> halmaz)
{
    if(id == halmaz[id])
    {
        return id;
    }
    else
    {
        return halmaz_kereses(halmaz[id], halmaz);
    }
}

void kruskal_feszitofa(vector<el> &elek, int &osszeg, vector<el> &el_sor, vector<int> halmaz)
{
    sort(el_sor.begin(), el_sor.end(), rendezes);
    for (int i = 0; i < el_sor.size(); i++)
    {
        int elso_halmaz = halmaz_kereses(el_sor[i].kezdopont, halmaz);
        int masodik_halmaz = halmaz_kereses(el_sor[i].vegpont, halmaz);

        if(elso_halmaz != masodik_halmaz)
        {
            elek.push_back(el_sor[i]);
            halmaz[elso_halmaz] = halmaz[masodik_halmaz];
            osszeg += el_sor[i].suly;
        }
    }
}

int main()
{
    freopen("graf.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<int> halmaz(n+1);
    for(int i = 0; i < halmaz.size(); i++)
    {
        halmaz[i] = i;
    }

    vector<el> el_sor;
    graf_beolvas(m, el_sor);
    

    int osszeg = 0;
    vector<el> elek;
    kruskal_feszitofa(elek, osszeg, el_sor, halmaz);
    cout << "Koltseg: " << osszeg << endl;
    for (int i = 0; i < elek.size(); i++)
    {
        cout << elek[i].kezdopont << " - " << elek[i].vegpont << ": " << elek[i].suly << endl;
    }
    
    return 0;
}