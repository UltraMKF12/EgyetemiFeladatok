// Széri József - sjim2307
//BeszuroRendezes
/*
Rendezzünk egy 𝑛 elemű tömböt beszúró rendezéssel!
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

void beszuro_rendezes(vector<long long> &tomb)
{
    int hossz = tomb.size();
    for (int i = 1; i < hossz; i++)
    {
        long long seged = tomb[i];
        int j = i-1;
        while (j >= 0 && tomb[j] > seged)
        {
            tomb[j+1] = tomb[j];
            j--;
        }
        tomb[j+1] = seged;
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    vector<long long> tomb;

    adat_beolvasas(tomb);
    beszuro_rendezes(tomb);
    tomb_kiiratas(tomb);

    return 0;
}