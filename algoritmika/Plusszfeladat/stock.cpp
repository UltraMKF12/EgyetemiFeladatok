#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // Tomb beolvasasa
    // Ki kell szamitani a legnagyobb loss-t, a tombben.
    
    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<int> tomb(n);
    vector<int> veszteseg(n, 0);

    for (int i = 0; i < n; i++)
    {
        cin >> tomb[i];
    }

    int legnagyobb_veszteseg = 0;
    int legnagyobb_ertek = tomb[0];
    for (int i = 1; i < n; i++)
    {
        if(tomb[i] > legnagyobb_ertek)
        {
            legnagyobb_ertek = tomb[i];
        }

        veszteseg[i] = tomb[i] - legnagyobb_ertek;
        if(veszteseg[i] < legnagyobb_veszteseg)
        {
            legnagyobb_veszteseg = veszteseg[i];
        }
    }
    
    cout << legnagyobb_veszteseg;
    
    return 0;
}