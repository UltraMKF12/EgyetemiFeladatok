// Széri József - sjim2307
//BalraAt
/*
Szeptember 15-én az iskola igazgatója felkéri az első osztályos gyermekeket,
hogy forduljanak arccal felé, majd abból a célból, hogy felvezethesse őket az
osztálytermekbe, kiadja a parancsot: “Balra át!”. A gyermekek bizonytalanok.
Van, aki balra fordul, van, aki jobbra. Aki szemben találja magát a mellette
állóval, azt hiszi, hogy rosszul fordult és egy időegység alatt egyszer sarkon
fordul. Adott egy bizonyos kezdeti konfiguráció, amely a “Balra át!” parancs
után alakult ki. Állapítsuk meg, hány időegység alatt „nyugszik meg” a sor.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    // Ötlet: Meg kell keresni az utolsó b-t.
    // Ha önmagában van akkor a megoldás az előtte levő j-k száma.
    // Ha több b van, akkor a megoldás: (j_szam > b_szam) ? j_szam+1 : b_szam+1, szóval +1 ahhoz amelyikből több van

    string sorozat;
    cin >> sorozat;

    int index_utolso_b = sorozat.find_last_of('b');
    
    int b_szam = 0;
    int j_szam = 0;

    while(index_utolso_b >= 0 && sorozat[index_utolso_b] == 'b')
    {
        b_szam++;
        index_utolso_b--;
    }

    for (int i = 0; i <= index_utolso_b; i++)
    {
        if(sorozat[i] == 'j')
        {
            j_szam++;
        }
    }

    int eredmeny = 0;
    if(b_szam == 1)
    {
        eredmeny = j_szam;
    }
    else if(b_szam > 1)
    {
        eredmeny = (j_szam > b_szam) ? j_szam+1 : b_szam+1;
    }

    cout << eredmeny;

    return 0;
}