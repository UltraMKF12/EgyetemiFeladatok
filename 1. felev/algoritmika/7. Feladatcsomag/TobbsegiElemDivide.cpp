// Széri József - sjim2307
//TobbsegiElemDivide
/*
Határozzuk meg oszd meg és uralkodj módszerrel egy 𝑛 elemű sorozat többségi
elemét, ha létezik ilyen, anélkül, hogy rendeznénk azt!
*/

#include <iostream> 
#include <vector>
using namespace std;

int tobbsegi_elem_div(int index_elso, int index_masodik, const vector<int> &tomb)
{
    if(index_elso == index_masodik)
    {
        return tomb[index_elso];
    }

    int kozep = (index_elso + index_masodik) / 2;
    int tobbsegi_elso = tobbsegi_elem_div(index_elso, kozep, tomb);
    int tobbsegi_masodik = tobbsegi_elem_div(kozep+1, index_masodik, tomb);

    if (tobbsegi_elso == tobbsegi_masodik)
    {
        return tobbsegi_elso;
    }

    else
    {
        int darab_elso = 0;
        int darab_masodik = 0;
        for (int i = 0; i < tomb.size(); i++)
        {
            if(tomb[i] == tobbsegi_elso)
            {
                darab_elso++;
            }
            else if(tomb[i] == tobbsegi_masodik)
            {
                darab_masodik++;
            }
        }

        if(darab_elso == darab_masodik)
        {
            return -1;
        }

        else if(darab_elso > darab_masodik)
        {
            return tobbsegi_elso;
        }

        else
        {
            return tobbsegi_masodik;
        }
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    //Beolvasas
    int n;
    cin >> n;
    vector<int> tomb(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tomb[i];
    }
    
    cout << tobbsegi_elem_div(0, n-1, tomb);

    return 0;
}