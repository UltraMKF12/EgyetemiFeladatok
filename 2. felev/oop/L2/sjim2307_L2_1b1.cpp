// Széri József - 514/2
#include <iostream>
using namespace std;

namespace intervallum_name
{
    double* intervallum; //2 elemű tömb

    void init(double, double);
    void felsz();
    void duplaz();
    void kiir();
}

void intervallum_name::init(double elso, double masodik)
{
    intervallum = new double[2];
    if(elso > masodik)
    {
        intervallum[0] = masodik;
        intervallum[1] = elso;
    }
    else
    {
        intervallum[0] = elso;
        intervallum[1] = masodik;
    }
}

void intervallum_name::felsz()
{
    delete intervallum;
}

void intervallum_name::duplaz()
{
    int hatar = intervallum[1] - intervallum[0];
    intervallum[0] -= hatar/2;
    intervallum[1] += hatar/2;
}

void intervallum_name::kiir()
{
    std::cout << "[" << intervallum[0] << "," << intervallum[1] << "]" << std::endl;
}

int main()
{
    using namespace intervallum_name;
    init(6, 10);
    kiir();
    duplaz();
    kiir();
    felsz();
    // intervallum = new double[2]{0, 1};
    kiir();
    return 0;
}