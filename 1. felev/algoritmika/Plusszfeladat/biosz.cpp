#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    freopen("bemenet.txt", "r", stdin);

    string szulo1;
    string szulo2;

    // cout << "Szulo1: ";
    cin >> szulo1;

    // cout << "Szulo2: ";
    cin >> szulo2;

    string bemenet;
    // cout << "Keresett aranyok: ";
    cin >> bemenet;


    string genLehetosegek = "";

    for(int szulo1_R = 0; szulo1_R < 2; szulo1_R++) // Visszatérit 4 változatot a szulo 1 re
    {
        for(int szulo1_Y = 2; szulo1_Y < 4; szulo1_Y++)
        {
            for(int szulo2_R = 0; szulo2_R < 2; szulo2_R++) // Visszatérit 4 változatot szulo 2-re igy osszesen 16 lesz
            {
                for(int szulo2_Y = 2; szulo2_Y < 4; szulo2_Y++)
                {
                    if(szulo1[szulo1_R] < szulo2[szulo2_R]) // Nagyobbetük ascii karakter erteke kisebb mint a kisbetüké
                    {
                        genLehetosegek += szulo1[szulo1_R]; 
                        genLehetosegek += szulo2[szulo2_R];
                    }
                    else
                    {
                        genLehetosegek += szulo2[szulo2_R];
                        genLehetosegek += szulo1[szulo1_R];
                    }

                    if(szulo1[szulo1_Y] < szulo2[szulo2_Y]) // Lekezeles Y-ra
                    {
                        genLehetosegek += szulo1[szulo1_Y];
                        genLehetosegek += szulo2[szulo2_Y];
                    }
                    else
                    {
                        genLehetosegek += szulo2[szulo2_Y];
                        genLehetosegek += szulo1[szulo1_Y];
                    }

                    genLehetosegek += " ";
                }
            }
        }
    }

    //Bemenet levalasztasa darabokra
    vector<string> keresettBemenetek;
    char delimeter = ':';
    int mutato = 4;
    keresettBemenetek.push_back(bemenet.substr(0, 4));
    while(mutato < bemenet.length())
    {   
        keresettBemenetek.push_back(bemenet.substr(mutato+1, 4));
        mutato += 5;
    }

    vector<int> keresettBemenetekErteke;

    // Előfordulás keresés
    for(int i = 0; i < keresettBemenetek.size(); i++)
    {
        string keresett = keresettBemenetek[i];
        int darabszam = 0;
        int position = genLehetosegek.find(keresett, 0);
        while(position != string::npos)
        {
            darabszam++;
            position = genLehetosegek.find(keresett, position + keresett.length());
        }

        keresettBemenetekErteke.push_back(darabszam);
    }

    //Szam egyszerusites
    //lnko - osszesnek megkeresni, majd ha mindegyiknek ugyanaz az lnkoja akkor osztani oket annyival
    int lnko = 0;
    for(int i = 0; i < keresettBemenetekErteke.size()-1; i++)
    {
        int a = keresettBemenetekErteke[i];
        int b = keresettBemenetekErteke[i+1];

        if(lnko == 0) lnko = a;
        if(a == 0 || b == 0) continue;
        while(a != b)
        {
            if(a > b) a -= b;
            else b -= a;
        }


        while(a != lnko)
        {
            if(a > lnko) a -= lnko;
            else lnko -= a;
        }
        // Most le kell tesztelni lnkora.
    }

    //Kiiratas
    cout << endl << bemenet << " -> ";
    for(int i = 0; i < keresettBemenetekErteke.size()-1; i++)
    {
        if(lnko > 1) cout << keresettBemenetekErteke[i]/lnko << ":";
        else cout << keresettBemenetekErteke[i] << ":";
    }

    if(lnko > 1) cout << keresettBemenetekErteke[keresettBemenetekErteke.size()-1]/lnko;
    else cout << keresettBemenetekErteke[keresettBemenetekErteke.size()-1];
    return 0;
}