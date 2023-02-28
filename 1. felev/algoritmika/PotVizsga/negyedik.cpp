#include <iostream>
#include <vector>
using namespace std;

/*
Adott egy 𝑛 elemű sorozat, melynek elemei páronként különbözőek. Határozzátok meg, hogy legkevesebb hány cserére van szükség, ahhoz, hogy a sorozat
növekvővé váljon!
*/

int greedy(const vector<int> &tomb, int n)
{
    int csere = 0;
    vector<bool> volt_mar(n, false);
    for(int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if(tomb[i] > tomb[j] && !volt_mar[j])
            {
                volt_mar[j] = true;
                csere++;
            }
        }
    }
    return csere;
}

int main()
{
    int n;
    cin >> n;
    vector<int> tomb(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tomb[i];
    }
    cout << greedy(tomb, n);
    return 0;
}