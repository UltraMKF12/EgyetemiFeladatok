// Széri József - sjim2307
// EgyetemistaNevsor
/*
Adottak az elsőéves egyetemisták névsorai (abc sorrendben), csoportonként.
Állítsunk elő ezekből egyetlen névsort, mely szintén abc sorrendben van!
*/

#include <iostream>
#include <vector>
using namespace std;

bool nagyobb_abc(string elso, string masodik)
{
    bool nagyobb = true;
    int index = 0;
    int elso_hossz = elso.size();
    int masodik_hossz = masodik.size();
    int kissebb_hossz = (elso_hossz < masodik_hossz) ? elso_hossz : masodik_hossz;

    int index1 = 0;
    int index2 = 0;
    while((index <= kissebb_hossz-1) && nagyobb)
    {
        if(elso[index1] > masodik[index2])
        {
            //
        }
    }

    return nagyobb;
}

int string_osszefesulet(int hossz1, vector<string> &vektor1, 
                        int hossz2, vector<string> &vektor2,
                                    vector<string> &vektor_eredmeny)
{
    return 1;
}

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    int csoportok_szama;
    cin >> csoportok_szama; 

    // Megszerezni az első diákokat.
    int jelenlegi_csoport_hossz;
    cin >> jelenlegi_csoport_hossz;
    getchar(); // Elnyelni a new line karaktert
    vector<string> eredmeny;
    int eredmeny_hossz = jelenlegi_csoport_hossz;
    for (int i = 0; i < jelenlegi_csoport_hossz; i++)
    {
        string diak;
        getline(cin, diak);
        eredmeny.push_back(diak);
    }
    
    //Osszefesulni az eredmenyt egyenként a többi diák csoporttal
    for (int i = 1; i < csoportok_szama; i++)
    {
        //
    }
    

    //Kiiratas
    for (int i = 0; i < eredmeny_hossz; i++)
    {
        cout << eredmeny[i] << endl;
    }
    

    return 0;
}