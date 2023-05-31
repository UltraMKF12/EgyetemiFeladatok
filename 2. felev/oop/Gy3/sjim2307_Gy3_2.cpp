//Széri József - 514
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{   
    freopen("vocab.txt", "r", stdin);

    unordered_map<string, int> szotar;

    string szo;
    while(cin >> szo)
    {
        szotar[szo] = 1;
    }

    for (auto pair1 : szotar)
    {
        for(auto pair2 : szotar)
        {
            if(pair1.first != pair2.first)
            {
                if(szotar.count(pair1.first + pair2.first) > 0)
                {
                    cout << pair1.first << " + " << pair2.first << " = " << pair1.first + pair2.first << endl;
                }
            }
        }
    }
}