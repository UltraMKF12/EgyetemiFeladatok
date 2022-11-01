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


int masolas(int hossz_elso, vector<unsigned long long> &vektor_elso, vector<unsigned long long> &vektor_masodik)
{
    int hossz_masodik = 0;
    for (int i = 0; i < hossz_elso; i++)
    {
        vektor_masodik.push_back(vektor_elso[i]);
        hossz_masodik++;
    }

    return hossz_masodik;
}


int egyesites(int hossz_elso, vector<unsigned long long> &vektor_elso, 
                 int hossz_masodik, vector<unsigned long long> &vektor_masodik,
                 vector<unsigned long long> &vektor_eredmeny)
{
    int hossz_harmadik = masolas(hossz_elso, vektor_elso, vektor_eredmeny);

    for (int j = 0; j < hossz_masodik; j++)
    {
        int i = 0;
        while((i < hossz_elso) && (vektor_elso[i] != vektor_masodik[j]))
        {
            i++;
        }
        if(i >= hossz_elso)
        {
            vektor_eredmeny.push_back(vektor_masodik[j]);
            hossz_harmadik++;
        }
    }
    
    return hossz_harmadik;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);


    //Beolvasas
    string string_elso, string_masodik;
    getline(cin, string_elso);
    getline(cin, string_masodik);

    vector<unsigned long long> vektor_elso_osztok, vektor_masodik_osztok;
    int hossz_elso = stringbol_vektorba(string_elso, vektor_elso_osztok);
    int hossz_masodik = stringbol_vektorba(string_masodik, vektor_masodik_osztok);


    //Feladat megoldasa
    vector<unsigned long long> vektor_eredmeny;
    int hossz_eredmeny = egyesites(hossz_elso, vektor_elso_osztok, hossz_masodik, vektor_masodik_osztok, vektor_eredmeny);


    //Kiiratas
    for (int i = 0; i < hossz_eredmeny; i++)
    {
        cout << vektor_eredmeny[i] << " ";
    }
    
    return 0;
}