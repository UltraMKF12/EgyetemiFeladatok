// sjim2307
// stabil leszamlalao

#include <iostream>
#include <vector>
using namespace std;

void stabil_leszamlalo(int hossz, vector<int> &tomb, int k)
{
    vector<int> szamok(k+1, 0);
    for (int i = 0; i < tomb.size(); i++)
    {
        szamok[tomb[i]]++;
    }
    for (int i = 1; i < szamok.size(); i++)
    {
        szamok[i] += szamok[i-1];
    }

    vector<int> seged(tomb.size(), 0);
    for (int i = tomb.size()-1; i >= 0; i--)
    {
        seged[szamok[tomb[i]]-1] = tomb[i];
        szamok[tomb[i]]--;
    }

    for(int i = 0; i < tomb.size(); i++)
    {
        tomb[i] = seged[i];
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> tomb;
    for (int i = 0; i < n; i++)
    {
        int szam;
        cin >> szam;
        tomb.push_back(szam);
    }

    stabil_leszamlalo(n, tomb, 1000000);

    for (int i = 0; i < n; i++)
    {
        cout << tomb[i] << endl;
    }

    return 0;
}