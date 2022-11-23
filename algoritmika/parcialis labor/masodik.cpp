// sjim2307
// palindrom primek

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<bool> szita_bool(int felso)
{
    vector<bool> szita(felso+1, true);
    szita[0] = false;
    szita[1] = false;
    int gyok = sqrt(felso);
    for (int i = 2; i <= gyok; i++)
    {
        if(szita[i])
        {
            for (int j = i*i; j <= felso; j+=i)
            {
                szita[j] = false;
            }
        }
    }

    return szita;
}

void szita_primek(const vector<bool> &szita, int also, int felso, vector<int> &primek)
{
    for(int i = 100; i <= felso; i++)
    {
        if(szita[i])
        primek.push_back(i);
    }
}

bool palindrom_e(int szam)
{
    int temp_szam = szam;
    int seged_szam = 0;
    while(temp_szam > 0)
    {
        int szamjegy = temp_szam % 10;
        temp_szam /= 10;
        seged_szam = (seged_szam * 10) + szamjegy;
    }

    return (szam == seged_szam);
}

int main()
{
    int also, felso;
    cin >> also >> felso;
    vector<bool> szita = szita_bool(felso);
    vector<int> primek;
    szita_primek(szita, also, felso, primek);

    for(int i = 0; i < primek.size(); i++)
    {
        if(palindrom_e(primek[i]))
        {
            cout << primek[i] << endl;
        }
    }

    return 0;
}