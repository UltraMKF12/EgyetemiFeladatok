//sjim2307
//rekurziv hatvany

#include <iostream>
using namespace std;

double hatvany_szamitas(double alap, int hatvany)
{
    if(hatvany == 0)
    {
        return 1;
    }

    if(hatvany % 2 == 1)
    {
        return alap * hatvany_szamitas(alap * alap, hatvany/2);
    }
    else if(hatvany % 2 == -1)
    {
        return 1/alap * hatvany_szamitas(alap * alap, hatvany/2);
    }
    else
    {
        return hatvany_szamitas(alap*alap, hatvany/2);
    }
}

int main()
{
    int x, hatvany;
    cin >> x >> hatvany;
    cout << hatvany_szamitas(x, hatvany);
    return 0;
}