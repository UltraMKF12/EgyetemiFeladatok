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

int minimum_kivalasztas(const vector<double> &tomb, int also, int felso, int hanyadik)
{

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
    
    minimum_kivalasztas(tomb, 0, tomb.size()-1, k);


    return 0;
}