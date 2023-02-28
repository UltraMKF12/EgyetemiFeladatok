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

int binaris_kereses(const vector<elem_eredeti> &tomb, int elem_keresett, int index_bal, int index_jobb)
{
    if(index_bal > index_jobb)
    {
        return -1;
    }

    int index_kozep = (index_bal + index_jobb) / 2;
    int elem_kozep = tomb[index_kozep].ertek;
    if(elem_keresett > elem_kozep)
    {
        return binaris_kereses(tomb, elem_keresett, index_kozep+1, index_jobb);
    }
    else if(elem_keresett < elem_kozep)
    {
        return binaris_kereses(tomb, elem_keresett, index_bal, index_kozep-1);
    }
    else
    {
        return index_kozep;
    }
}

void ket_szam_osszege(const vector<elem_eredeti> &tomb, int &elso_index, int &masodik_index, int osszeg)
{
    for (int i = 0; i < tomb.size(); i++)
    {
        int keresett_elem = osszeg - tomb[i].ertek;
        int keresett_index = binaris_kereses(tomb, keresett_elem, i+1, tomb.size()-1);
        if(keresett_index != -1)
        {
            if((elso_index == -1 && masodik_index == -1) || (elso_index > tomb[i].index) || (elso_index == tomb[i].index && masodik_index > tomb[i].index))
            {
                elso_index = tomb[i].index;
                masodik_index = tomb[keresett_index].index;
            }
        }
    }
    
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
    ket_szam_osszege(tomb, elso, masodik, x);
    if(elso != -1)
    {
        cout << "1\n" << elso+1 << " " << masodik+1;
    }
    else
    {
        cout << 0;
    }

    return 0;
}