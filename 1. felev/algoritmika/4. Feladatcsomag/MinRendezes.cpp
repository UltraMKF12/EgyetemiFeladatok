// Széri József - sjim2307
//MinRendezes
/*
Rendezzünk egy 𝑛 elemű tömböt minimumkiválasztásra épülő rendezéssel!
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

void minimum_rendezes(vector<long long> &tomb)
{
    int hossz = tomb.size();
    for (int i = 0; i < hossz-1; i++)
    {
        long long minimum_index = i;
        for (int j = i+1; j < hossz; j++)
        {
            if(tomb[minimum_index] > tomb[j])
            {
                minimum_index = j;
            }
        }
        swap(tomb[i], tomb[minimum_index]);
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    vector<long long> tomb;

    adat_beolvasas(tomb);
    minimum_rendezes(tomb);
    tomb_kiiratas(tomb);

    return 0;
}