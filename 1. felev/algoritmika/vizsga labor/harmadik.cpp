/*
Adott egy 𝑛 egész számot tartalmazó sorozat. Határozzuk meg azt a legnagyobb összeget, amelyet a tömb egymás utáni elemeinek összeadásával kaphatunk
(vagyis a legnagyobb összegű tömbszakaszt keressük).
*/

#include <iostream>
#include <vector>
using namespace std;

int feloszt(int bal, int jobb, const vector<int> &tomb)
{
    for(int i = bal; i <= jobb; i++)
    {
        if(tomb[i] < 0)
        {
            return i;
        }
    }

    return jobb;
}

int legnagyobb_tombszakasz(const vector<int> &tomb, int bal, int jobb)
{
    if(bal == jobb)
    {
        return tomb[bal];
    }
    else if(bal < jobb)
    {
        int m = feloszt(bal, jobb, tomb);
        int bal_legnagyobb = legnagyobb_tombszakasz(tomb, bal, m-1);
        int jobb_legnagyobb = legnagyobb_tombszakasz(tomb, m, jobb);

        return bal_legnagyobb + jobb_legnagyobb

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

    cout << legnagyobb_tombszakasz(tomb, 0, n-1);

    return 0;
}