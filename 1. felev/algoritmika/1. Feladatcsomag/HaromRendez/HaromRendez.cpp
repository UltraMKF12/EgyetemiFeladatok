// Széri József - sjim2307
// HaromRendez
// Olvassunk be a billenty˝uzetr˝ol h´arom 64-bites el˝ojeles eg´esz sz´amot. ´Irjuk ki ˝oket n¨ovekv˝o sorrendben!
#include <iostream>
using namespace std;

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    long long elso, masodik, harmadik;

    cin >> elso >> masodik >> harmadik;

    if(elso <= masodik && elso <= harmadik)
    {
        if(masodik <= harmadik)
        {
            cout << elso << " " << masodik << " " << harmadik;
        }
        else
        {
            cout << elso << " " << harmadik << " " << masodik;
        }
    }

    else if(masodik <= elso && masodik <= harmadik)
    {
        if(elso <= harmadik)
        {
            cout << masodik << " " << elso << " " << harmadik;
        }
        else
        {
            cout << masodik << " " << harmadik << " " << elso;
        }
    }

    else if(harmadik <= elso && harmadik <= masodik)
    {
        if(elso <= masodik)
        {
            cout << harmadik << " " << elso << " " << masodik;
        }
        else
        {
            cout << harmadik << " " << masodik << " " << elso;
        }
    }
    
    return 0;
}