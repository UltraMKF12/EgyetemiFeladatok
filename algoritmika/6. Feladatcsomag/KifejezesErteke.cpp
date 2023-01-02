// Széri József - sjim2307
//KifejezesErteke
/*
Legyen két számsorozat 𝐴 = [𝑎1, 𝑎2, . . . , 𝑎𝑚] és 𝐵 = [𝑏1, 𝑏2, . . . , 𝑏𝑛]. Válasszuk
ki a 𝐵 sorozatból azon 𝑋 = [𝑥1, 𝑥2, . . . , 𝑥𝑚] elemeket, amelynek megfelelően az
𝐸 = 𝑎1𝑥1 + 𝑎2𝑥2 + . . . + 𝑎𝑚𝑥𝑚 kifejezés értéke a lehető legnagyobb.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //Beolvasas
    int hossz_elso, hossz_masodik;

    cin >> hossz_elso;
    vector<int> tomb_elso(hossz_elso);
    for (int i = 0; i < hossz_elso; i++)
    {
        cin >> tomb_elso[i];
    }

    cin >> hossz_masodik;
    vector<int> tomb_masodik(hossz_masodik);
    for (int i = 0; i < hossz_masodik; i++)
    {
        cin >> tomb_masodik[i];
    }
    

    //Rendezni kell a két tömböt növekvő sorrendben
    sort(tomb_elso.begin(), tomb_elso.end(), greater<int>());
    sort(tomb_masodik.begin(), tomb_masodik.end(), greater<int>());

    //Minden 1 tömb beli elemet össze kell szorozni a 2. tömb beliekkel ameddig lehet.
    long long osszeg = 0;
    for (int i = 0; i < hossz_elso; i++)
    {
        osszeg += (tomb_elso[i] * tomb_masodik[i]);
    }
    
    cout << osszeg;

    return 0;
}