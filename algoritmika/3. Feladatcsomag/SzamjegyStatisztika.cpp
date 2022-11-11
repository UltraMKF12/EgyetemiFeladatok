// Széri József - sjim2307
//SzamjegyStatisztika
/*
Határozzuk meg, hogy melyik számjegyet hányszor kell leírnunk, ha egyenként
minden természetes számot le akarunk írni az [𝑥, 𝑦] intervallumból!
*/

#include <iostream>
#include <vector>
using namespace std;

void kiir_statisztika(const vector<unsigned long long> &statisztika)
{
    for (int i = 0; i < 10; i++)
    {
        cout << statisztika[i] << " ";
    }
}

void szamjegy_szamlalas(unsigned long long szam, vector<unsigned long long> &statisztika)
{
    unsigned long long szam_masolat = szam;

    while(szam_masolat > 0)
    {
        int szamjegy = szam_masolat % 10;
        statisztika[szamjegy]++;
        szam_masolat /= 10;
    }
}

void szamjegy_szamlalas_intervallum(unsigned long long szam1, unsigned long long szam2, vector<unsigned long long> &statisztika)
{
    for (unsigned long long i = szam1; i <= szam2; i++)
    {
        szamjegy_szamlalas(i, statisztika);
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned long long szam1, szam2;
    cin >> szam1 >> szam2;

    vector<unsigned long long> statisztika(10, 0);
    
    szamjegy_szamlalas_intervallum(szam1, szam2, statisztika);
    kiir_statisztika(statisztika);
    return 0;
}