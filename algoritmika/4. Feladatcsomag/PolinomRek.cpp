// Széri József - sjim2307
//PolinomRek
/*
Írjunk rekurzív algoritmust, amely kiszámítja egy 𝑛-ed fokú polinom értékét
egy adott valós 𝑥 pontban! Ne használjunk ismétlő struktúrát a beolvasáson
kívül!
*/

#include <iostream>
#include <vector>
using namespace std;

void beolvasas(int &n, int &x, vector<int> &tomb)
{
    cin >> n;
    tomb.resize(n+1);
    for (int i = n; i >=0; i--)
    {
        int szam;
        cin >> szam;
        tomb[i] = szam;
    }
    cin >> x;
}

double polinom(int n, int x, vector<int> tomb, double eredmeny, int melyseg, long long szorzo)
{
    if(melyseg > n)
    {
        return eredmeny;
    }
    
    return polinom(n, x, tomb, (eredmeny+(tomb[melyseg])*szorzo), melyseg+1, szorzo*x);
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n, x;
    vector<int> tomb;
    beolvasas(n, x, tomb);
    double eredmeny = polinom(n, x, tomb, 0, 0, 1);
    cout << eredmeny;
    return 0;
}