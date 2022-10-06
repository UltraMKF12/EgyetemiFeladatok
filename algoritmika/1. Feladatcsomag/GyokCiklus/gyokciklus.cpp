// Széri József - sjim2307
// GyokCiklus
// Hasonl´ıtsuk ¨ossze egy ism´etl˝od˝o ciklus sebess´eg´et amely a beolvasott sz´am gy¨ok´eig megy el, h´aromf´elek´eppen implement´alva
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

int gyokNegyzet(unsigned long long n)
{
    int iteracio = 1;
    while (iteracio*iteracio <= n)
    {
        iteracio++;
    }
    return iteracio-1; // mivel n legkisebb erteke 0 lehet, az iteracio 1 tol indul, hogy helyes ertek legyen visszateritve ki kell vonni egyet.
}

int gyokSegedvaltozoWhile(unsigned long long n)
{
    int iteracio = 1;
    while (iteracio <= n)
    {
        iteracio++;
    }
    return iteracio-1;
}

int gyokSqrtWhile(unsigned long long n)
{
    int iteracio = 1;
    while (iteracio <= sqrt(n))
    {
        iteracio++;
    }
    return iteracio-1;
}

void futasiIdo(int index, unsigned long long n)
{
    clock_t start = clock();

    switch (index)
    {
    case 1:
        cerr << "while (i*i <= n): ";
        start = clock();
        gyokNegyzet(n);
        break;
    
    case 2:
        cerr << "segedvaltozoval: ";
        start = clock();
        gyokSegedvaltozoWhile(sqrt(n));
        break;

    case 3:
        cerr << "while (i <= sqrt(n)) ";
        start = clock();
        gyokSqrtWhile(n);
        break;
    }

    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;

    cerr << "futasi ido: " << elapsed << endl;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned long long n;
    cin >> n;
    
    futasiIdo(1, n);
    futasiIdo(2, n);
    futasiIdo(3, n);

    int iteracioDarab;
    iteracioDarab = gyokNegyzet(n);
    cout << iteracioDarab;
    return 0;
}