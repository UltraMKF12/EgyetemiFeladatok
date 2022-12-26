// Széri József - sjim2307
//MatrixOsszeg
/*
Adott egy 𝑛 × 𝑚-es mátrix. Határozzuk meg azt a legnagyobb 𝑛 elemű
összeget, amelyet úgy kapunk meg, hogy minden elem a mátrix különböző
soraiból “származik” és az 𝑖. sorból kiválasztott elem kisebb mint az 𝑖+ 1. sorból
kiválasztott elem.
*/

#include <iostream>
#include <vector>
using namespace std;

int maximum(vector<int> tomb)
{
    int maximum = tomb[0];
    for (int i = 0; i < tomb.size(); i++)
    {
        if(maximum < tomb[i])
        {
            maximum = tomb[i];
        }
    }

    return maximum;
}

int maximum_hatar(vector<int> tomb, int hatar)
{
    int maximum = hatar;
    for (int i = 0; i < tomb.size(); i++)
    {
        if(tomb[i] < hatar && maximum < tomb[i])
        {
            maximum = tomb[i];
        }
        else if(maximum == hatar && tomb[i] < hatar)
        {
            maximum = tomb[i];
        }
    }

    return maximum;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> matrix[i][j];
        }
    }
    int osszeg = maximum(matrix[matrix.size()-1]);
    int hatar = osszeg;
    bool van_megoldas = true;
    for (int i = n-2; i >= 0; i--)
    {
        int hozzaadando = maximum_hatar(matrix[i], hatar);
        if(hozzaadando == hatar)
        {
            cout << "nincs megoldas";
            van_megoldas = false;
            break;
        }
        osszeg += hozzaadando;
        hatar = hozzaadando;
    }
    
    if(van_megoldas)
    {
        cout << osszeg;
    }

    return 0;
}