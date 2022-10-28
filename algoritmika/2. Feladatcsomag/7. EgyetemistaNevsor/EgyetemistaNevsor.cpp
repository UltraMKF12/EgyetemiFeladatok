// Széri József - sjim2307
// EgyetemistaNevsor
/*
Adottak az elsőéves egyetemisták névsorai (abc sorrendben), csoportonként.
Állítsunk elő ezekből egyetlen névsort, mely szintén abc sorrendben van!
*/

#include <iostream>
#include <vector>
using namespace std;

vector<string> osszefesules(const vector<string> &vektor1, const vector<string> &vektor2)
{
    int hossz1 = vektor1.size();
    int hossz2 = vektor2.size();

    vector<string> vektor_eredmeny;
    int i = 0;
    int j = 0;
    while((i < hossz1) && (j < hossz2))
    {
        if(vektor1[i].compare(vektor2[j]) < 0) // ha .compare() visszteritett erteke < 0 akkor az elso string elobb van abc sorrendben
        {
            vektor_eredmeny.push_back(vektor1[i]);
            i++;
        }
        else
        {
            vektor_eredmeny.push_back(vektor2[j]);
            j++;
        }
    }

    while(i < hossz1)
    {
        vektor_eredmeny.push_back(vektor1[i]);
        i++;
    }

    while(j < hossz2)
    {
        vektor_eredmeny.push_back(vektor2[j]);
        j++;
    }

    return vektor_eredmeny;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //Beolvasas
    int csoportok_szama;
    cin >> csoportok_szama; 

    vector<vector<string>> diakok(csoportok_szama, vector<string>());
    for (int i = 0; i < csoportok_szama; i++)
    {
        int diakok_szama;
        cin >> diakok_szama;
        getchar(); //Elnyelni a new linet
        for (int j = 0; j < diakok_szama; j++)
        {
            string diak;
            getline(cin, diak);
            diakok[i].push_back(diak);
        }
    }

    
    //Feladat megoldasa - minden diak osszefesulese az eredmeny-el egyenkent.
    vector<string> eredmeny;
    int diakok_hossz = diakok.size();
    for (int i = 0; i < diakok_hossz; i++)
    {
        eredmeny = osszefesules(diakok[i], eredmeny);
    }


    //Feladat kiirasa
    int eredmeny_hossz = eredmeny.size();
    for (int i = 0; i < eredmeny_hossz; i++)
    {
        cout << eredmeny[i];
        if(i < eredmeny_hossz-1) // A feladat vegen ne legyen egy felesleges new line
        {
            cout << endl;
        }
    }
    
    return 0;
}