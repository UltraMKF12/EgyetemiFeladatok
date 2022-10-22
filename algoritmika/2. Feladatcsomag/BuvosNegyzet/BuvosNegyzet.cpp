// Széri József - sjim2307
// BuvosNegyzet
/*
Vizsgáljuk meg, hogy egy adott, 𝑛×𝑛 méretű négyzetes tömb bűvös négyzet-e
vagy sem. Egy természetes számokkal feltöltött négyzetes tömböt akkor nevezünk
bűvös négyzetnek, ha páronként különböző számokat tartalmaz, a számok összege
soronként és oszloponként, valamint a két átló mentén azonos. Alkalmazzuk a
Halmaz-e programozási tételt!
*/

#include <iostream>
#include <vector>
using namespace std;

// 1D vektorokat fogad be
bool halmazE(const vector<unsigned long long> &vektor)
{
    int hossz = vektor.size() - 1; // A legnagyobb elerheto index kell
    int i = 0;
    bool halmaz = true;
    while(halmaz && (i < hossz))
    {
        int j = i + 1;
        while((j <= hossz) && (vektor[i] != vektor[j]))
        {
            j++;
        }
        halmaz = (j > hossz);
        i++;
    }

    return halmaz;
}

// 1D vektorokat fogad be
unsigned long long vektorOsszeg(const vector<unsigned long long> &vektor)
{
    int hossz = vektor.size();
    unsigned long long osszeg = 0;

    for (int i = 0; i < hossz; i++)
    {
        osszeg += vektor[i];
    }
    
    return osszeg;
}

// 2D vektorokat fogad be
bool halmazEsHelyesSorok(const vector<vector<unsigned long long>> &vektor, unsigned long long helyesOsszeg)
{
    int sorokSzama = vektor.size();

    bool halmaz = true;
    bool osszeg = true;

    int sor = 0;
    while(halmaz && osszeg && (sor < sorokSzama))
    {
        halmaz = halmazE(vektor[sor]);
        osszeg = (helyesOsszeg == vektorOsszeg(vektor[sor]));
        sor++;
    }
    
    return halmaz && osszeg;
}

// 2D vektorokat fogad be
bool halmazEsHelyesOszlopok(const vector<vector<unsigned long long>> &vektor, unsigned long long helyesOsszeg)
{
    int oszlopokSzama = vektor.size();

    // Meg kell fordítani a vektort, mert könnyebb sorokkal dolgozni
    vector<vector<unsigned long long>> forditottVektor(vektor); // Nem számítanak az értékek benne csak akkora legyen mint a vektor
    for (int i = 0; i < oszlopokSzama; i++)
    {
        for (int j = 0; j < oszlopokSzama; j++)
        {
            forditottVektor[j][i] = vektor[i][j];
        }
    }
    
    return halmazEsHelyesSorok(forditottVektor, helyesOsszeg); // Meghívjuk a sorokra működő kódot
}

// 2D vektorokat fogad be
bool halmazEsHelyesAtlok(const vector<vector<unsigned long long>> &vektor, unsigned long long helyesOsszeg)
{
    int sorokSzama = vektor.size();

    // 2D vektor 2db N hosszuságú sorral.
    vector<vector<unsigned long long>> atloVektor(2, vector<unsigned long long>(sorokSzama, 0));

    // Főátló felépítése sorba
    int i = 0;
    int j = 0;
    while(i < sorokSzama)
    {
        atloVektor[0][i] = vektor[i][j];
        i++;
        j++;
    }

    // Mellékátló felépítése sorba
    i = sorokSzama-1;
    j = 0;
    while(i >= 0)
    {
        atloVektor[1][i] = vektor[i][j];
        i--;
        j++;
    }

    return halmazEsHelyesSorok(atloVektor, helyesOsszeg); // Meghívjuk a sorokra működő kódot
}

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    int nagysag;
    cin >> nagysag;

    vector<vector<unsigned long long>> magikusTomb(nagysag, vector<unsigned long long>(nagysag, 0)); // 2D tomb nagysag * nagysag meretu
    for (int i = 0; i < nagysag; i++)
    {
        for (int j = 0; j < nagysag; j++)
        {
            cin >> magikusTomb[i][j];
        }
    }

    // Kiszámítani, hogy mennyi kell legyen a számok összege;
    unsigned long long osszeg = vektorOsszeg(magikusTomb[0]);

    // Kiszamitani, hogy halmaz-e és helyes az összege a soroknak, oszlopoknak és átlóknak.
    if( halmazEsHelyesSorok(magikusTomb, osszeg) && 
        halmazEsHelyesOszlopok(magikusTomb, osszeg) &&
        halmazEsHelyesAtlok(magikusTomb, osszeg))
    {
        cout << "igen";
    }

    else
    {
        cout << "nem";
    }

    return 0;
}