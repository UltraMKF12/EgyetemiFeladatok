// Széri József - 514/2
#include <iostream>
using namespace std;

void init(double, double);
void felsz();
void duplaz();
void kiir();

// extern double* intervallum;
int main()
{
    init(6, 10);
    // cout << intervallum[0];
    kiir();
    duplaz();
    kiir();
    felsz();
    // intervallum = new double[2]{0, 1};
    kiir();
    return 0;
}