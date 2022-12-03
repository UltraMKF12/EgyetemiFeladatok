// Széri József - sjim2307
//Muveletek
/*
Adva van egy 𝑛 darab egész számot tartalmazó sorozat. Helyezzünk az
adott számok közé 𝑛 − 1 aritmetikai műveleti jelet a (+, −, *, /) halmazból, úgy,
hogy a kifejezés értéke legyen egyenlő egy adott 𝑥 számmal! A kifejezés értéke
minden lépésben legyen egész szám! A műveleteket nem a matematikából ismert
operátorprecedencia szerint végezzük, hanem megjelenésük sorrendjében.
*/

#include <iostream>
#include <vector>
using namespace std;

void beolvasas(int &n, vector<int> &szamok, int &eredmeny)
{
    cin >> n;
    szamok.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> szamok[i];
    }
    cin >> eredmeny;
}

int jel_konverzio(int szam1, int szam2, char jel)
{
    switch (jel)
    {
    case '+':
        return szam1 + szam2;
    case '-':
        return szam1 - szam2;
    case '*':
        return szam1 * szam2;
    case '/':
        return szam1 / szam2;

    default:
        return 0;
    }
}

void kiir(const vector<int> &szamok, const vector<char> &jelenlegi_jelek, int eredmeny)
{
    cout << eredmeny << "=";
    int hossz = jelenlegi_jelek.size();
    for (int i = 0; i < hossz; i++)
    {
        cout << szamok[i] << jelenlegi_jelek[i];
    }
    cout << szamok[hossz] << endl;
}

void muveletek(int n, int eredmeny, const vector<int> &szamok, const vector<char> &jelek, int melyseg, vector<char> &jelenlegi_jelek, int jelenlegi_eredmeny, int &darab)
{
    if(melyseg >= n-1)
    {
        if(eredmeny == jelenlegi_eredmeny)
        {
            kiir(szamok, jelenlegi_jelek, eredmeny);
            darab++;
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            char jel = jelek[i];
            jelenlegi_jelek[melyseg] = jel;
            int uj_eredmeny = jel_konverzio(jelenlegi_eredmeny, szamok[melyseg+1], jel);
            muveletek(n, eredmeny, szamok, jelek, melyseg+1, jelenlegi_jelek, uj_eredmeny, darab);
        }
        
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n, eredmeny;
    vector<int> szamok;
    beolvasas(n, szamok, eredmeny);

    vector<char> jelek = {'+', '-', '*', '/'};
    vector<char> jelenlegi_jelek(n-1, ' ');
    int darab = 0;
    muveletek(n, eredmeny, szamok, jelek, 0, jelenlegi_jelek, szamok[0], darab);

    if(darab == 0)
    {
        cout << -1;
    }

    return 0;
}