//Kijelentés
//Generáljuk az összes 𝑓 : {1, 2, . . . , 𝑛} → {1, 2, . . . , 𝑚} injektív függvényt!

#include <iostream>
#include <vector>
using namespace std;

void injektiv_backtracking(int n, int m, int melyseg, vector<int> &tomb)
{
    if(melyseg >= 2)
    {
        if(tomb[0] != tomb[1])
        {
            cout << tomb[0] << " " << tomb[1] << endl;
        }
    }
    else
    {
        for (int i = 1; i <= m; i++)
        {
            tomb[melyseg] = i;
            injektiv_backtracking(n, m, melyseg+1, tomb);
        }
        
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> tomb (2, 0);
    injektiv_backtracking(n, m, 0, tomb);
    
    return 0;
}