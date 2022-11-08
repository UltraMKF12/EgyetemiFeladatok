// Széri József - sjim2307
//KisebbFibo
/*
Írjunk algoritmust, amely megadja a Fibonacci-sorozat egy adott 𝑥 számnál kisebb elemeinek számát!
A Fibonacci-sorozat nulladik elemét nem kell figyelembe venni.
*/

#include <iostream> 
using namespace std;

int fibonacci_nagyobb(unsigned long long szam)
{
    unsigned long long darab = 0; 
    unsigned long long elso = 0;
    unsigned long long masodik = 1;
    while(szam > masodik)
    {
        darab++;
        // Kiszamitani a kovetkezo elemet, es kicserelni a regieket
        int temp = elso;
        elso = masodik;
        masodik = masodik + temp;
    }

    return darab;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned long long szam;
    cin >> szam;

    cout << fibonacci_nagyobb(szam) <<" darab kisebb elem van a Fibonacci-sorozatban, mint " << szam;
    return 0;
}