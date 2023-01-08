// Széri József - sjim2307
//Quickselect
/*
Adott egy 𝑛 elemű tömb, mely 64 bites valós számokat tartalmaz és egy 𝑘
természetes szám. Határozzuk meg a tömb 𝑘. legkisebb elemét, anélkül, hogy
rendeznénk azt, vagy használnánk az nth_element függvényt!
*/

#include <iostream>
#include <vector>
using namespace std;

int feloszt2(vector<double> &tomb, int bal, int jobb)
{
    double pivot = tomb[jobb];
    int i = bal - 1;
    
    for (int j = bal; j <= jobb - 1; j++)
    {
        if(tomb[j] <= pivot)
        {
            i++;
            swap(tomb[i], tomb[j]);
        }
    }

    swap(tomb[i+1], tomb[jobb]);
    return i+1;
    
}

int minimum_kivalasztas(vector<double> &tomb, int bal, int jobb, int hanyadik)
{
    if(bal < jobb)
    {
        int m = feloszt2(tomb, bal, jobb);
        if(m == hanyadik-1)
        {
            return m;
        }
        else if(m > hanyadik)
        {
            minimum_kivalasztas(tomb, bal, m-1, hanyadik);
        }
        else
        {
            minimum_kivalasztas(tomb, m+1, jobb, hanyadik);
        }
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n, k;
    cin >> n >> k;
    vector<double> tomb(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tomb[i];
    }
    
    int keresett_index = minimum_kivalasztas(tomb, 0, tomb.size()-1, k);

    cout << tomb[keresett_index];

    return 0;
}