// Széri József - sjim2307
// ProgramozoFizetesek
/* 
Adott 𝑛 programozó fizetése. Válogassuk szét őket a fizetésük alapján. Az
első csoportba azok kerülnek, akiknek a fizetésük nagyobb mint 1000 EUR, a
másodikba a megmaradtak közül azok, akiknek a fizetése nagyobb mint 700 EUR,
a harmadikban maradnak a többiek (a sorrend nem fontos). Törekedjünk egyetlen
tömbbel dolgozni és abban elvégezni a szétválogatást, nem elég a kiíratásban
csoportokra osztani a számokat. 
*/


#include <iostream>
#include <vector>
using namespace std;

void szetvalogatas_helyben_ertek(int hossz, vector<double> &fizetesek, int ertek)
{
    int index = 0;
    int index_veg = hossz-1;
    while(index < index_veg)
    {
        while((index < index_veg) && (fizetesek[index] > ertek))
        {
            index++;
        }
        while((index < index_veg) && (fizetesek[index_veg] <= ertek))
        {
            index_veg--;
        }

        if(index < index_veg)
        {
            int temp = fizetesek[index];
            fizetesek[index] = fizetesek[index_veg];
            fizetesek[index_veg] = temp;
            index++;
            index_veg--;
        }
    }
}

void kiir_tomb(int hossz, const vector<double> &tomb, int elso_hatar, int masodik_hatar)
{
    int index = 0;
    while((index < hossz) && (tomb[index] > elso_hatar))
    {
        cout << tomb[index] << " ";
        index++;
    }

    cout << endl;

    while((index < hossz) && (tomb[index] > masodik_hatar))
    {
        cout << tomb[index] << " ";
        index++;
    }

    cout << endl;

    while(index < hossz)
    {
        cout << tomb[index] << " ";
        index++;
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int hossz;
    cin >> hossz;

    vector<double> fizetesek(hossz);

    for (int i = 0; i < hossz; i++)
    {
        cin >> fizetesek[i]; 
    }

    szetvalogatas_helyben_ertek(hossz, fizetesek, 1000);
    szetvalogatas_helyben_ertek(hossz, fizetesek, 700);

    kiir_tomb(hossz, fizetesek, 1000, 700);

    return 0;
}