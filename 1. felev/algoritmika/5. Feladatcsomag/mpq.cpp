// Széri József - sjim2307
//mpq
/*
Generáljunk minden lehetséges sorozatot, amelynek elemei a 0, 1, 2 halmazból
vannak, és a 0 𝑚-szer, az 1 𝑝-szer és a 2 𝑞-szor fordul elő
*/

#include <iostream> 
#include <vector>
using namespace std;

void mpq(vector<int> &elofordulas, int melyseg, int max_melyseg, vector<int> &jelenlegi)
{
    if(melyseg == max_melyseg)
    {
        for (int i = 0; i < max_melyseg; i++)
        {
            cout << jelenlegi[i] << " ";
        }
        cout << endl;
    }

    else
    {
        for (int i = 0; i < 3; i++)
        {   
            if(elofordulas[i] > 0)
            {
                elofordulas[i]--;
                jelenlegi[melyseg] = i;
                mpq(elofordulas, melyseg+1, max_melyseg, jelenlegi);
                elofordulas[i]++;
            }
        }
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);
    vector<int> elofordulas(3, 0);
    cin >> elofordulas[0];
    cin >> elofordulas[1];
    cin >> elofordulas[2];

    int max_melyseg = elofordulas[0] + elofordulas[1] + elofordulas[2];
    vector<int> jelenlegi(max_melyseg, 0);
    mpq(elofordulas, 0, max_melyseg, jelenlegi);


    return 0;
}