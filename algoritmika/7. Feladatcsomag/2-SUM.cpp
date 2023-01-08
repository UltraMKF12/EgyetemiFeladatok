// Széri József - sjim2307
//2-SUM
/*
Adott egy 𝑛 elemű tömb, mely 32 bites előjeles egész számokat tartalmaz
és egy 𝑥 32 bites előjeles egész szám. Határozzuk meg, hogy létezik-e két olyan
eleme a tömbnek, melyek összege pontosan 𝑥. Alkalmazzunk bináris keresést!
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct elem_eredeti
{
    int ertek;
    int index;
};

bool elem_ertek_rendezes(elem_eredeti &elso, elem_eredeti&masodik)
{
    return elso.ertek < masodik.ertek;
}

void binaris_kereses(vector<elem_eredeti> &tomb, int &elso, int &masodik, int osszeg, int index_also, int index_felso)
{
    int index_kozep = (index_also + index_felso) / 2;
    int elem_kozep = tomb[index_kozep].ertek;
    if(elem_kozep > )
}

int main()
{
    freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n, x;
    cin >> n >> x;
    vector<elem_eredeti> tomb;

    for (int i = 0; i < n; i++)
    {
        int szam;
        cin >> szam;
        tomb.push_back({szam, i});
    }
    
    //Binaris kereseshez rendezni kell
    sort(tomb.begin(), tomb.end(), elem_ertek_rendezes);

    int elso = -1;
    int masodik = -1;
    binaris_kereses(tomb, elso, masodik, x, 0, tomb.size()-1);

    return 0;
}