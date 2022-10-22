// Széri József - sjim2307
// EgyetemistaNevsor
/*
Adottak az elsőéves egyetemisták névsorai (abc sorrendben), csoportonként.
Állítsunk elő ezekből egyetlen névsort, mely szintén abc sorrendben van!
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    freopen("bemenet.txt", "r", stdin);
    freopen("kimenet.txt", "w", stdout);

    int hossz;
    cin >> hossz;

    vector<string> diakok;
    for(int i = 0; i < hossz; i++)
    {
        int csoportHossz;
        cin >> csoportHossz;
        for (int j = 0; j < csoportHossz; j++)
        {
            string nev;
            getline(cin, nev);
            if(nev == "") getline(cin, nev);
            diakok.push_back(nev);
        }
    }

    for (int i = 0; i < diakok.size(); i++)
    {
        cout << diakok[i] << endl;
    }
    
    return 0;
}