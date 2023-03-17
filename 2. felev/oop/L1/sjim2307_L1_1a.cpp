// Széri József - 514/2
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int veletlenSzam(int a, int b)
{
    return (rand() % (b-a+1) +a);
}

void jatek(int generaltSzam)
{
    int jatekos_tipp = -1;
    while (true)
    {
        cout << "Tipp = ";
        cin >> jatekos_tipp;
        if(jatekos_tipp == generaltSzam)
        {
            cout << "gratula!\n";
            break;
        }
        if(jatekos_tipp > generaltSzam)
        {
            cout << "kisebb\n";
        }
        else if(jatekos_tipp < generaltSzam)
        {
            cout << "nagyobb\n";
        }
    }
}

int main()
{
    srand(time(0));
    jatek(veletlenSzam(1, 100));
    return 0;
}