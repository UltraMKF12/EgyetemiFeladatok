// Széri József - sjim2307
//KettoHatvanyok
/*
Bontsunk fel egy adott számot 2 hatványainak összegére!
*/

#include <iostream> 
#include <vector>
using namespace std;

void szam_lebontas_bitekre(unsigned long long szam, vector<bool> &bitek)
{
    int bit_index = 0;
    unsigned long long szam_masolat = szam;
    while(szam_masolat > 0)
    {
        bool bit = szam_masolat % 2; // Ez 0-t vagy 1-et térít vissza, azaz false vagy true;
        bitek[bit_index] = bit;

        bit_index++;
        szam_masolat /= 2;
    }
}

void bitek_kiirasa(const vector<bool> &bitek)
{
    int bitek_szama = 0;
    for (int i = 0; i < 64; i++)
    {
        if(bitek[i])
        {
            bitek_szama++;
        }
    }
    
    for (int i = 63; i >= 0; i--)
    {
        if (bitek[i])
        {
            cout << "2^" << i;
            if (bitek_szama > 1)
            {
                cout << "+";
                bitek_szama--;
            }       
        }
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    unsigned long long szam;
    cin >> szam;

    vector<bool> bitek(64, false); //64 bit van, ezért egy 64 elemű tömbben tárolom, hogy milyen bitek vannak "bekapcsolva"
    szam_lebontas_bitekre(szam, bitek);
    bitek_kiirasa(bitek);

    return 0;
}