// Széri József - sjim2307
//TorzstenyezokRek
/*
Írjunk rekurzív algoritmust, amely kiír egy 𝑛 természetes számot törzstényezőkre
bontva! Ne használjunk egyáltalán ismétlő struktúrát!
*/

#include <iostream> 
using namespace std;

void kiir_szam_hatvany(int szam, int hatvany)
{
    if(hatvany == 1)
    {
        cout << szam;
    }
    else if(hatvany > 1)
    {
        cout << szam << "^" << hatvany;
    }
}

void torzstenyezo(int szam, int jelenlegi_szam, int hanyszor, bool elso)
{   
    //bool elso, az elso szam ele ne irassin ki *-ot.
    if(szam <= 1)
    {   
        kiir_szam_hatvany(jelenlegi_szam, hanyszor);
        return;
    }

    if(szam % jelenlegi_szam == 0)
    {
        if(hanyszor == 0 && !elso)
        {
            cout << "*";
        }
        else if(elso)
        {
            elso = false; // Az első szám elé ne legyen * írva.
        }
        torzstenyezo(szam/jelenlegi_szam, jelenlegi_szam, hanyszor+1, elso);
    }
    else
    {
        kiir_szam_hatvany(jelenlegi_szam, hanyszor);
        torzstenyezo(szam, jelenlegi_szam+1, 0, elso);
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    int szam;
    cin >> szam;
    torzstenyezo(szam, 2, 0, true);

    return 0;
}