// Széri József - sjim2307
//Szamkitalalos
/*
Legyen a következő játék: az egyik játékos (Játékos1) gondol egy 1 és 1000
közötti természetes számra. A másik játékosnak (Játékos2) ki kell találnia ezt
a számot minél kevesebb próbálgatással. A titkos szám „birtokosa” (Játékos1)
egy-egy találgatásra csak annyit válaszol, hogy a titkos szám kisebb vagy nagyobb
mint a másik játékos (Játékos2) által feltételezett szám.
Írjunk programot amely a fenti játékot szimulálja, úgy, hogy a programunk a
Játékos2, azaz ő találja ki a felhasználó titkos számát.
*/

#include <iostream> 
using namespace std;

void tippeles(int minimum, int maximum)
{
    int kozep = (minimum + maximum) / 2;
    cout << kozep << endl;

    int szamitogep_valasz;
    cin >> szamitogep_valasz;

    //Helyes
    if(szamitogep_valasz == 0)
    {
        return;
    }

    //Kisebb
    if(szamitogep_valasz == -1)
    {
        tippeles(minimum, kozep-1);
    }

    //Nagyobb
    if(szamitogep_valasz == 1)
    {
        tippeles(kozep+1, maximum);
    }

}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int minimum = 1;
    int maximum = 1000;
    tippeles(minimum, maximum);

    return 0;
}