// Széri József - 514/2
#include <iostream>
#include <math.h>

using namespace std;

int hatvanyozas(int szam, int hatvany)
{
    return pow(szam, hatvany);
}

int hatvanyozas(int szam)
{
    return pow(szam, szam);
}

int main()
{
    cout << hatvanyozas(5) << endl;
    cout << hatvanyozas(5, 2);
    return 0;
}