/*
Egy épitkezési anyagokat árúsító cég különböző hosszúságú csöveket árul és
tudja minden méterhosszra, hogy hány lejt kaphat az adott hosszúságú darabért.
Hogyan daraboljon fel a cég egy 𝑛 hosszúságú csövet, ahhoz, hogy maximális
profitot érjen el?
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int cso_hossz;
    cin >> cso_hossz;

    vector<unsigned> darabolt_arak(cso_hossz+1, 0);
    for (int i = 1; i <= cso_hossz; i++)
    {
        cin >> darabolt_arak[i];
    }

    //Megszerezni mennyit az ár érték arány
    vector<double> ar_ertek_arany(cso_hossz+1);
    for (int i = 1; i <= cso_hossz; i++)
    {
        ar_ertek_arany[i] = cso_hossz / i * darabolt_arak[i];
    }
    
    
    
    return 0;
}