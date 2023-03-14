// Széri József - 514/2
#include <iostream>
using namespace std;

int a(int b)
{
    cout << "b=" << b << endl;
}

int a(int b, int c=0)
{
    cout << "b=" << b  << ", c=" << c << endl;
}

int main()
{
    //sjim2307_Gy1_3.cpp:18:9: error: call of overloaded 'a(int)' is ambiguous
    //Itt az történik, hogy a compiler nem tud dönteni, hogy melyik fügvény hívja meg egy darab paraméterre, 
    //mert mind a kettő függvénynek egyetlen egy kötelező paramétere van (A c-nek 0 lesz az értéke ha nincs megadva)
    a(12);
    a(21, 32);
    return 0;
}