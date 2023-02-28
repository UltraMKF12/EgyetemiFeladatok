// Széri József - sjim2307
//SzamjegyesRendezes
/*
Rendezzünk egy 𝑛 elemű tömböt számjegyes rendezéssel! A bemenet első
sora tartalmazza az 𝑛 értéket, a többi 𝑛 sor a sorozat elemeit.
*/

#include <iostream>
#include <vector>
using namespace std;

void adat_beolvasas(vector<unsigned long long> &tomb)
{
    long long n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        unsigned long long szam;
        cin >> szam;
        tomb.push_back(szam);
    }
}

void tomb_kiiratas(const vector<unsigned long long> &tomb)
{
    int hossz = tomb.size();
    for(int i = 0; i < hossz; i++)
    {
        cout << tomb[i] << endl;
    }
}

int maximum_szamjegy(const vector<unsigned long long> &tomb)
{
    int hossz = tomb.size();
    unsigned long long maximum_szam = tomb[0];

    //Maximum kivalasztas
    for (int i = 0; i < hossz; i++)
    {
        if(maximum_szam < tomb[i])
        {
            maximum_szam = tomb[i];
        }
    }
    
    //Szamjegy meghatarozas
    int szamjegy_szam = 0;
    while(maximum_szam > 0)
    {
        maximum_szam /= 10;
        szamjegy_szam++;
    }

    return szamjegy_szam;
}

void stabil_leszamlalo_rendezes(vector<unsigned long long> &tomb, int k, unsigned long long oszto)
{
    int hossz = tomb.size();
    vector<int> darab(k+1, 0);

    for (int i = 0; i < hossz; i++)
    {
        int tomb_index = ((tomb[i] / oszto) % 10);
        darab[tomb_index]++;
    }

    for (int i = 1; i < k; i++)
    {
        darab[i] += darab[i-1];
    }

    vector<unsigned long long> seged(hossz, 0);
    for (int i = hossz-1; i >= 0; i--)
    {
        int tomb_index = ((tomb[i] / oszto) % 10);
        seged[darab[tomb_index]-1] = tomb[i];
        darab[tomb_index]--;
    }

    for(int i = 0; i < hossz; i++)
    {
        tomb[i] = seged[i];
    }
}

void szamjegyes_rendezes(vector<unsigned long long> &tomb)
{
    int hossz = tomb.size();
    int szamjegy_szama = maximum_szamjegy(tomb);

    unsigned long long oszto = 1;
    for (int i = 0; i < szamjegy_szama; i++)
    {
        stabil_leszamlalo_rendezes(tomb, 10, oszto);
        oszto *= 10;
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    vector<unsigned long long> tomb;

    adat_beolvasas(tomb);
    szamjegyes_rendezes(tomb);
    tomb_kiiratas(tomb);

    return 0;
}