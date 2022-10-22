// Széri József - sjim2307
// TorolBuko
// Adott egy csoport év végi vizsgajegyeinek listája. Töröljük ki az 5-ösnél kisebb jegyeket a listából. A módósítást a beolvasott tömbben kell elvégezni, nem elég csak kiíratni az eredményt.

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    int hossz;
    cin >> hossz;

    vector<double> vizsgajegyek(hossz);

    for (int i = 0; i < hossz; i++)
    {
        cin >> vizsgajegyek[i]; 
    }
    
    return 0;
}