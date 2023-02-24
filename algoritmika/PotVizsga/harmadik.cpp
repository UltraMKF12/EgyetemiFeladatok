#include <iostream>
#include <vector>
using namespace std;

/*
Adott egy 𝑛 elemű egész számokat tartalmazó 𝑎 sorozat. Állapítsuk meg
a sorozatban található inverziók számát! Inverziónak nevezünk minden olyan
𝑖 < 𝑗 indexpárt, amelyre 𝑎𝑖 > 𝑎𝑗 .
*/

int feloszt(const vector<int> &tomb, int bal, int jobb, int &darab)
{
    int m = (bal + jobb) / 2;
    int meret = tomb.size();
    for (int i = m+1; i < meret; i++)
    {
        if(tomb[m] > tomb[i])
        {
            darab++;
        }
    }
    return m;
}

void divide(const vector<int> &tomb, int bal, int jobb, int &darab)
{
    if(bal <= jobb)
    {
        int m = feloszt(tomb, bal, jobb, darab);
        divide(tomb, bal, m-1, darab);
        divide(tomb, m+1, jobb, darab);
    }
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

    int maradek = 0;
    divide(tomb, 0, n-1, maradek);
    cout << maradek;
    
    return 0;
}