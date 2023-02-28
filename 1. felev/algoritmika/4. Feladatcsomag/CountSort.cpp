// Széri József - sjim2307
//CountSort
/*
Rendezzünk egy 𝑛 elemű tömböt leszámláló rendezéssel!
*/

#include <iostream>
#include <vector>
using namespace std;

void adat_beolvasas(vector<long long> &tomb)
{
    long long n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        long long szam;
        cin >> szam;
        tomb.push_back(szam);
    }
}

void tomb_kiiratas(const vector<long long> &tomb)
{
    int hossz = tomb.size();
    for(int i = 0; i < hossz; i++)
    {
        cout << tomb[i] << endl;
    }
}

void leszamlalo_rendezes(vector<long long> &tomb, int k)
{
    int hossz = tomb.size();
    vector<int> darab(k+1, 0);

    for (int i = 0; i < hossz; i++)
    {
        darab[tomb[i]]++;
    }
    
    int q = 0;
    for (int i = 0; i <= k; i++)
    {
        for (int j = 0; j < darab[i]; j++)
        {
            tomb[q] = i;
            q++;
        }
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    vector<long long> tomb;

    adat_beolvasas(tomb);
    leszamlalo_rendezes(tomb, 1000000);
    tomb_kiiratas(tomb);

    return 0;
}