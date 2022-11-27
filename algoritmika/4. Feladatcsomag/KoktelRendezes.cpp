// Széri József - sjim2307
//KoktelRendezes
/*
Rendezzünk egy 𝑛 elemű tömböt koktélrendezéssel!
*/

#include <iostream>
#include <vector>
using namespace std;

void adat_beolvasas(vector<long long> &tomb)
{
    long long n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        long long szam;
        cin >> szam;
        tomb.push_back(szam);
    }
}

void tomb_kiiratas(const vector<long long> &tomb)
{
    int hossz = tomb.size();
    for(int i = 0; i < hossz; i++)
    {
        cout << tomb[i] << endl;
    }
}

void koktel_rendezes(vector<long long> &tomb)
{
    int hossz = tomb.size();

    int regibal = 0;
    int regijobb = hossz-1;
    bool rendben = true;
    do
    {
        rendben = true;
        int jobb = 0;
        for (int i = regibal; i < regijobb; i++)
        {
            if(tomb[i] > tomb[i+1])
            {
                swap(tomb[i], tomb[i+1]);
                rendben = false;
                jobb = i;
            }
        }

        if(!rendben)
        {
            regijobb = jobb;
            rendben = true;
            int bal = hossz-1;

            for (int i = regijobb-1; i >= regibal; i--)
            {
                if(tomb[i] > tomb[i+1])
                {
                    swap(tomb[i], tomb[i+1]);
                    rendben = false;
                    bal = i;
                }
            }
            regibal = bal;
        }
        
    } while (!rendben);
}


int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    vector<long long> tomb;

    adat_beolvasas(tomb);
    koktel_rendezes(tomb);
    tomb_kiiratas(tomb);


    return 0;
}