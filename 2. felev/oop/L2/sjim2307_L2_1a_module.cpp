#include <iostream>

static double* intervallum; //2 elemű tömb

void init(double elso, double masodik)
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

void felsz()
{
    delete intervallum;
}

void duplaz()
{
    int hatar = intervallum[1] - intervallum[0];
    intervallum[0] -= hatar/2;
    intervallum[1] += hatar/2;
}

void kiir()
{
    std::cout << "[" << intervallum[0] << "," << intervallum[1] << "]" << std::endl;
}