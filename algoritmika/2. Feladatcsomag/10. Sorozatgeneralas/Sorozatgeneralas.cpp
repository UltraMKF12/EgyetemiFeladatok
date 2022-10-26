// Széri József - sjim2307
// Sorozatgeneralas
/*
Adott a következő sorozat, amelynek minden elemét – az elsőt kivéve – az
előző elem segítségével generáljuk: 1, 11, 21, 1211, 111221, . . .
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

string sorozat_generalas(string sorozat)
{
    string uj_sorozat;

    int index = 0;
    while(index < sorozat.size())
    {
        char szamjegy = sorozat[index];
        int darab = 0;
        while(sorozat[index] == szamjegy)
        {
            index++;
            darab++;
        }

        uj_sorozat += to_string(darab) + szamjegy;
    }
    
    return uj_sorozat;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n;
    cin >> n;

    string sorozat = "1";
    for (int i = 1; i < n; i++)
    {
        sorozat = sorozat_generalas(sorozat);
    }

    cout << sorozat;
    
    return 0;
}