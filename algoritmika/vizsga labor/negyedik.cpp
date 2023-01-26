/*
Egy ügyvédi irodába egyszerre érkezik 𝑛 személy, akiknek az intéznivalóit az
ügyvéd ismeri, így azt is tudja, hogy egy-egy személlyel hány percet fog eltölteni.
Állapítsuk meg azt a sorrendet, amelyben fogadnia kellene a személyeket ahhoz,
hogy az átlagos várakozási idő minimális legyen!
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> tomb(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tomb[i];
    }

    //átlag várakozási idő úgy minimális, hogy növekvő sorrendbe vannak a kliensek idő szerint.
    sort(tomb.begin(), tomb.end());

    double varakozasi_idok = 0;
    for (int i = 0; i < n-1; i++)
    {
        //PL: 10 30 60-ra:
        //10 percet kel lvarjon a 30 as és a 60-as, ami 20 perc összesen.
        //30 percet kell várjon a 60-as
        //ez összesen 50 perc. ezt elosszuk n-el, mert n kliens van ami 16.66...

        //A képlet, az utolsó előtti kliens idejéig megy.
        // Hozzáadja, a bentléti idejét annyiszor ahány ember van még utánna. (-1 a tomb cimezes miatt kell)
        varakozasi_idok += (tomb[i] * (n-i-1));
    }

    //Atlag kiszamitasa
    varakozasi_idok /= n;
    
    cout << fixed << setprecision(2) << varakozasi_idok;
    
    return 0;
}