// Széri József - sjim2307
//ArabbolRomaiba
/*
Adott egy 𝑛 arab szám, írjuk ki római számjegyekkel!
*/

#include <iostream> 
#include <vector>
using namespace std;

string arab_romai_tabla(int szam)
{
    switch (szam)
    {
    case 1000:
        return "M";
    case 900:
        return "CM";
    case 500:
        return "D";
    case 400:
        return "CD";
    case 100:
        return "C";
    case 90:
        return "XC";
    case 50:
        return "L";
    case 40:
        return "XL";
    case 10:
        return "X";
    case 9:
        return "IX";
    case 5:
        return "V";
    case 4:
        return "IV";
    case 1:
        return "I";
    
    default:
        return ""; // ha rossz számot kapnánk
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int arab_szam;
    cin >> arab_szam;

    //Végig kell menni az összes lehetséges karakter kombináción
    vector<int> lehetseges_szamok = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string eredmeny = "";

    int arab_szam_masolat = arab_szam;
    for (int i = 0; i < lehetseges_szamok.size(); i++)
    {
        int jelenlegi_szam = lehetseges_szamok[i];
        while (jelenlegi_szam <= arab_szam_masolat)
        {
            arab_szam_masolat -= jelenlegi_szam;
            eredmeny += arab_romai_tabla(jelenlegi_szam);
        }
    }
    
    cout << eredmeny;
    return 0;
}