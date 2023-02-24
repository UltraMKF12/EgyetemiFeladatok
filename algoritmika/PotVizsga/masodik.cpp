#include <iostream>
#include <vector>
using namespace std;

/*
Adott egy számháromszög, amelynek az első sorában egy elem van, a másodikban kettő és így tovább. Határozzuk meg a legkisebb összeget, amelyet úgy
kaphatunk, hogy a háromszög tetejéről indulva egészen az utolsó sorig haladunk
úgy, hogy egy mezőről csak a két alatta lévő mezőre léphetünk és egy ilyen
minimális összegű útvonalat.
*/

int minimum(int elso, int masodik)
{
    return (elso < masodik) ? elso : masodik;
}

int dinamikus(const vector<vector<int>> &tomb, vector<vector<int>> &pont_tomb, int n)
{
    //Feltolteni rendesen a legalso sort.
    for (int i = 0; i < n; i++)
    {
        pont_tomb[n-1][i] = tomb[n-1][i];
    }
    
    for (int i = n-2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            pont_tomb[i][j] = minimum(pont_tomb[i+1][j], pont_tomb[i+1][j+1]) + tomb[i][j];
        }        
    }
    
    return pont_tomb[0][0];
}

void bejaras(const vector<vector<int>> &pont_tomb, int n)
{
    int position = 0;
    for (int i = 1; i < n; i++)
    {
        if(pont_tomb[i][position] < pont_tomb[i][position+1])
        {
            cout << "B";
        }
        else
        {
            position += 1;
            cout << "J";
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> tomb(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cin >> tomb[i][j];
        }   
    }
    
    vector<vector<int>> pont_tomb(n, vector<int>(n, 0));
    int legrovidebb = dinamikus(tomb, pont_tomb, n);
    
    cout << legrovidebb << endl;
    bejaras(pont_tomb, n);
    return 0;
}