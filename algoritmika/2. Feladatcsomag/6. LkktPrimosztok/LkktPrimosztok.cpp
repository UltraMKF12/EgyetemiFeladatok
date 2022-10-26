// Széri József - sjim2307
// LkktPrimosztok
/*
Ismerjük két szám prímszám osztóit, határozzuk meg a két szám legkisebb
közös többszörösének prímszám osztóit! (A két számot nem ismerjük, csupán a
prim osztóikat).
*/

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int stringbol_vektorba(string szamok, vector<unsigned long long> &vektor)
{
    //istringsteam használatával a stringbe beolvasott sorokat vektorba be tudjuk tenni számokként.
    int hossz = 0;
    stringstream sstream(szamok);
    unsigned long long szam;
    while(sstream >> szam)
    {
        vektor.push_back(szam);
        hossz++;
    }

    return hossz;
}

int osszefesules(int hossz_elso, vector<unsigned long long> &vektor_elso, 
                 int hossz_masodik, vector<unsigned long long> &vektor_masodik,
                 vector<unsigned long long> &vektor_eredmeny)
{
    int index_elso = 0; // i
    int index_masodik = 0; // j
    int hossz_harmadik = 0; // db
    
    //Őrszemek
    vektor_elso.push_back(vektor_masodik[hossz_masodik-1] + 1);
    vektor_masodik.push_back(vektor_elso[hossz_elso-1] + 1);

    while((index_elso < hossz_elso) || (index_masodik < hossz_masodik))
    {   
        hossz_harmadik++;
        if(vektor_elso[index_elso] < vektor_masodik[index_masodik])
        {
            vektor_eredmeny.push_back(vektor_elso[index_elso]);
            index_elso++;
        }
        else if(vektor_elso[index_elso] == vektor_masodik[index_masodik])
        {
            vektor_eredmeny.push_back(vektor_elso[index_elso]);
            index_elso++;
            index_masodik++;
        }
        else
        {
            vektor_eredmeny.push_back(vektor_masodik[index_masodik]);
            index_masodik++;
        }
    }

    return hossz_harmadik;
}

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    // Megfigyelések:
    // Két szám lkktjának primszám osztói a két szám primszám osztói.
    // A számok sorrendben vannak. => Összefésülés, halmazt kell alkosson

    string string_elso, string_masodik;
    getline(cin, string_elso);
    getline(cin, string_masodik);

    vector<unsigned long long> vektor_elso_osztok, vektor_masodik_osztok;
    int hossz_elso = stringbol_vektorba(string_elso, vektor_elso_osztok);
    int hossz_masodik = stringbol_vektorba(string_masodik, vektor_masodik_osztok);

    vector<unsigned long long> vektor_eredmeny;
    int hossz_eredmeny = osszefesules(hossz_elso, vektor_elso_osztok, hossz_masodik, vektor_masodik_osztok, vektor_eredmeny);

    for (int i = 0; i < hossz_eredmeny; i++)
    {
        cout << vektor_eredmeny[i] << " ";
    }
    
    return 0;
}