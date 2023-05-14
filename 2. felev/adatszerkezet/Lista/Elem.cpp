#include <iostream>
#include "Elem.h"

using namespace std;

Elem::Elem(string neve, double atlaga)
{
    nev = neve;
    atlag = atlaga;
    kov = NULL;
}

Elem::~Elem()
{
    if(kov != NULL)
    {
        delete kov;
    }
}

void Elem::Kiir()
{
    cout << nev << " - " << atlag;
}

void Elem::SetKov(Elem* uj_elem)
{
    kov = uj_elem;
}

Elem* Elem::GetKov()
{
    return kov;
}

string Elem::GetNev()
{
    return nev;
}

double Elem::GetAtlag()
{
    return atlag;
}