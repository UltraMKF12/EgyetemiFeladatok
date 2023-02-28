// Széri József - sjim2307
// MaganhangzokSzama
// Számoljuk meg egy adott szövegben a magánhangzók számát!

#include <iostream>
using namespace std;

bool maganhangzoE(char karakter)
{
    string maganhanzoLista = "aeiouAEIOU";
    int maganhangzokHossza = 10;
    
    for(int i = 0; i < maganhangzokHossza; i++)
    {
        if(karakter == maganhanzoLista[i])
        {
            return true;
        }
    }

    return false;
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    string szoveg;
    getline(cin, szoveg);

    int maganhangzokSzama = 0;
    int szovegHossza = szoveg.size();

    for (int i = 0; i < szovegHossza; i++)
    {
        if(maganhangzoE(szoveg[i]))
        {
            maganhangzokSzama++;
        }
    }
    
    cout << maganhangzokSzama;
    return 0;
}