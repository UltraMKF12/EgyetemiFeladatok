// sjim2307
// prim tombszakasz

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

bool prim_e(unsigned long szam)
{
    if(szam <= 1)
    {
        return false;
    }
    if(szam % 2 == 0)
    {
        return (szam == 2);
    }
    if(szam < 5)
    {
        return true;
    }
    if(((szam - 1) % 6 != 0) && ((szam + 1) % 6 != 0))
    {
        return false;
    }
    else
    {
        unsigned long gyok = sqrt(szam);
        for (int i = 3; i < gyok; i+=2)
        {
            if(szam % i == 0)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    int n;
    cin >> n;
    vector<unsigned long> tomb;
    for (int i = 0; i < n; i++)
    {
        unsigned long szam;
        cin >> szam;
        tomb.push_back(szam);
    }
    
    int hossz = 0;
    int kezdo_index = 0;

    int temp_hossz = 0;
    int temp_kezdoindex = 0;

    for (int i = 0; i < tomb.size(); i++)
    {
        if(prim_e(tomb[i]))
        {
            if(temp_hossz == 0)
            {
                temp_kezdoindex = i;
            }
            temp_hossz++;

            if(hossz < temp_hossz)
            {
                hossz = temp_hossz;
                kezdo_index = temp_kezdoindex;
            }
        }
        else
        {
            temp_hossz = 0;
        }
    }

    kezdo_index++; // A peldaban a tomb elso indexe 1, ezert hozza kell adni 1-et.

    cout << hossz << " " << kezdo_index;
    return 0;
}