// Széri József - sjim2307
// TorolBuko
// Adott egy csoport év végi vizsgajegyeinek listája. Töröljük ki az 5-ösnél kisebb jegyeket a listából. 
// A módósítást a beolvasott tömbben kell elvégezni, nem elég csak kiíratni az eredményt.

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int hossz;
    cin >> hossz;

    vector<double> vizsgajegyek(hossz);

    for (int i = 0; i < hossz; i++)
    {
        cin >> vizsgajegyek[i]; 
    }

    // Kiválogatás helyben tétel
    int hossz_index = 0; // i
    int tomb_veg_index = hossz-1; // n
    while(hossz_index <= tomb_veg_index)
    {
        if(vizsgajegyek[hossz_index] < 5)
        {
            vizsgajegyek[hossz_index] = vizsgajegyek[tomb_veg_index];
            tomb_veg_index--;
        }
        else
        {
            hossz_index++;
        }
    }

    //Kiiratas
    for (int i = 0; i < hossz_index; i++)
    {
        cout << vizsgajegyek[i] << " ";
    }
    
    
    return 0;
}