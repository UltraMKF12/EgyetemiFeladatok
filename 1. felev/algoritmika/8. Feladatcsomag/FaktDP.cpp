// Széri József - sjim2307
//FaktDP
/*
Számoljátok ki 𝑛 faktoriálisát a dinamikus programozás módszerével!
*/

#include <iostream> 
#include <vector>
using namespace std;

long long faktorialisDP(int n)
{
    vector<long long> ertekek(n+1);
    ertekek[0] = 1;
    ertekek[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        ertekek[i] = ertekek[i-1] * i;
    }
    
    return ertekek[n];
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int n;
    cin >> n;
    cout << faktorialisDP(n);

    return 0;
}