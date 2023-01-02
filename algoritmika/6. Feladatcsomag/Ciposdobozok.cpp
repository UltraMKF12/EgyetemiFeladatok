// Széri József - sjim2307
//Ciposdobozok
/*
Adva van 𝑛+ 1 cipősdoboz és 𝑛 pár cipő, amelyek meg vannak számozva 1-től
𝑛-ig. Az 𝑛 pár cipő 𝑛 + 1 dobozban található, a dobozok közül az egyik üres. El
kell rendezni a cipőket úgy, hogy minden cipő a saját dobozába kerüljön és az üres
doboz a sor végére. Munka közben csak egy pár cipőt szabad kivenni a dobozból,
amelyben található, és azonnal be kell tenni az üres dobozba. Állapítsuk meg a
költöztetések sorozatát minimális számú művelettel.
*/

#include <iostream> 
#include <vector>
using namespace std;

int main()
{
    freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);
    int n;
    cin >> n;

    vector<int> poziciok(n+1);
    for (int i = 1; i <= n; i++)
    {
        cin >> poziciok[i];
    }

    // Az tömb elején lesz a 0-s helye, az index miatt
    cin >> poziciok[0];
    
    

    int rossz = 0;
    for (int i = 1; i <= n; i++)
    {
        if(i != poziciok[i])
        {
            rossz++;
        }
    }
    
    if(poziciok[0] == 0)
    {
        rossz = (rossz / 2) * 3;
    }
    else
    {
        rossz = (rossz / 2) * 3 - 1;
    }

    cout << rossz;

    return 0;
}