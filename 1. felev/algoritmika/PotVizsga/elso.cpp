#include <iostream>
#include <vector>
using namespace std;

//Írjunk rekurzív algoritmust, amely generálja egy adott 𝑛 szám minden partícióját. Azok közül a partíciók közül, amelyek csak a tagok sorrendjében különböznek, csak egyet kell kiírnunk.

void kiir(const vector<int> &tomb, int k)
{
    for (int i = 0; i <= k; i++)
    {
        cout << tomb[i] << " ";
    }

    cout << endl;
}

void particio(int sum, int k, vector<int> &tomb, int elozo)
{

    for (int i = 1; i <= sum; i++)
    {
        if(i > elozo && k != 0)
        {
            break;
        }

        tomb[k] = i;
        int masolat = sum - i;
        if(masolat == 0)
        {
            kiir(tomb, k);
        }
        else if(masolat > 0)
        {
            particio(masolat, k+1, tomb, i);
        }
    }
    
}

int main()
{
    int n;
    cin >> n;
    vector<int> tomb(n);
    particio(n, 0, tomb, 1);
    return 0;
}