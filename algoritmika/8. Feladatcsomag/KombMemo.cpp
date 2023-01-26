// Széri József - sjim2307
//KombMemo
/*
Számoljátok ki 𝑛 elem 𝑘-ad rendű kombinációinak számát feljegyzéses módszerrel!
*/

#include <iostream>
#include <vector>
using namespace std;

void init_memo(int n, int k, vector<vector<long long>> &tomb)
{
    tomb[1][0] = 1;
    tomb[1][1] = 1;
    for (int i = 0; i <= n; i++)
    {
        tomb[i][0] = 1;
        tomb[i][i] = 1;
    }
}

long long komb_memo(int n, int k, vector<vector<long long>> &tomb)
{
    if(tomb[n][k] != -1)
    {
        return tomb[n][k];
    }
    else
    {
        tomb[n][k] = komb_memo(n-1, k, tomb) + komb_memo(n-1, k-1, tomb);
        return tomb[n][k];
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n, k;
    cin >> n >> k;
    vector<vector<long long>> tomb(n+1, vector<long long>(n+1, -1));
    init_memo(n, k, tomb);

    cout << komb_memo(n, k, tomb);
    return 0;
}