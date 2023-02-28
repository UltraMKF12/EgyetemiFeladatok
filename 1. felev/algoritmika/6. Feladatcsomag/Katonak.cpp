// Széri József - sjim2307
//Katonak
/*
A háború során 𝑚 különböző helyen kell őrt állni, mindegyik helyről tudjuk,
hogy melyik nap kezdetétől melyik nap végéig kell ott szolgálatot teljesítsen egy
katona. Állapítsuk meg, hogy elegendő-e 𝑛 darab katona ahhoz, hogy őrt álljunk
mind az 𝑚 helyen!
*/

#include <iostream> 
#include <vector>
#include <algorithm>
using namespace std;

struct Hely
{
    int kezdeti;
    int veg;
};

bool rendezes_kezdeti(const Hely &hely1, const Hely& hely2)
{
    return hely1.kezdeti < hely2.kezdeti;
}

bool katona_ujrahelyezes(vector<int> &katonak, int uj_kezdet, int uj_veg)
{
    // true - ha ujra lett helyezve
    // false - ha nem lehetett ujrahelyezni
    for (int i = 0; i < katonak.size(); i++)
    {
        if(katonak[i] < uj_kezdet)
        {
            katonak[i] = uj_veg;
            return true;
        }
    }
    
    return false;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    vector<Hely> helyek;
    for (int i = 0; i < m; i++)
    {
        int kezdet, veg;
        cin >> kezdet >> veg;
        helyek.push_back({kezdet, veg});
    }
    
    // Növektvő sorrendbe rendezés
    sort(helyek.begin(), helyek.end(), rendezes_kezdeti);
    vector<int> katonak(n, 0);

    bool van_megoldas = true;

    for (int i = 0; i < m; i++)
    {
        if(!katona_ujrahelyezes(katonak, helyek[i].kezdeti, helyek[i].veg))
        {
            //Ha nem lehet ujra helyezni a kovetkezo helyre katonat.
            van_megoldas = false;
            break;
        }
    }
    
    if(van_megoldas)
    {
        cout << "igen";
    }
    else
    {
        cout << "nem";
    }


    return 0;
}