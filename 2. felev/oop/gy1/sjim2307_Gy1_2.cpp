// Széri József - 514/2
#include <iostream>
#include <math.h>
using namespace std;

double negyzetgyok(double szam)
{
    return sqrt(szam);
}

double negyzet(double szam)
{
    return szam*szam;
}

double reciprok(double szam)
{
    return 1/szam;
}

double vegrehajt(double szam, double(*function)(double))
{
    return function(szam);
}

int main()
{
    cout << vegrehajt(5, &negyzetgyok) << endl;
    cout << vegrehajt(5, &negyzet) << endl;
    cout << vegrehajt(5, &reciprok) << endl;
    return 0;
}