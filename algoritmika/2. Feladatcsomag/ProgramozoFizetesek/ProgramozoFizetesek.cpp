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

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    int hossz;
    cin >> hossz;

    vector<double> fizetesek(hossz);

    for (int i = 0; i < hossz; i++)
    {
        cin >> fizetesek[i]; 
    }

    return 0;
}