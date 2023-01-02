// Széri József - sjim2307
//SzamjegySzorzat
/*
Adott egy 𝑛 egész szám. Határozzuk meg a legkisebb olyan 𝑚 > 0 természetes
számot, amelyre 𝑚 számjegyeinek szorzata egyenlő 𝑛-el!*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int szam;
    cin >> szam;

    vector<int> szamjegyek(10, 0);

    int szam_copy = szam;
    for (int i = 2; i < 10; i++)
    {
        while(szam_copy > 0 && szam_copy % i == 0)
        {
            szam_copy /= i;
            szamjegyek[i]++;
        }
    }

    //Kulonleges esetek
    if(szam == 0)
    {
        cout << 10;
    }
    else if(szam == 1)
    {
        cout << 1;
    }
    else
    {

        string vegeredmeny = "";

        // -1-et kell kiirni ha a szám prím.
        if(szam_copy == szam)
        {
            cout << -1;
        }
        else
        {
            // Ha primet talalunk az osztók között akkor be kell tenni a tömbbe.
            if(szam_copy > 1)
            {
                szamjegyek[0] = szam_copy;
            }

            // Át kell alakíteni a következőket 2->4, 2->8, 3->9
            while(szamjegyek[2] > 2)
            {
                szamjegyek[2] -= 3;
                szamjegyek[8]++;
            }
            if(szamjegyek[2] == 2)
            {
                szamjegyek[2] -= 2;
                szamjegyek[4]++;
            }
            while(szamjegyek[3] > 1)
            {
                szamjegyek[3] -= 2;
                szamjegyek[9]++;
            }

            vector<int> szamok;
            for (int i = 2; i < 10; i++)
            {
                while(szamjegyek[i] > 0)
                {
                    szamjegyek[i]--;
                    szamok.push_back(i);
                }
            }
            if(szamjegyek[0] > 0)
            {
                szamok.push_back(szamjegyek[0]);
            }

            for (int i = 0; i < szamok.size(); i++)
            {
               vegeredmeny += to_string(szamok[i]);
            }
        }

        if (vegeredmeny.length() <= 7)
        {
            cout << vegeredmeny;
        }
        else if (vegeredmeny == "10000000")
        {
            cout << vegeredmeny;
        }
        else
        {
            cout << vegeredmeny;
        }
    }

    return 0;
}