#include "Labirintus.h"
#include <iostream>
using namespace std;

Labirintus::Labirintus(int uj_n, int uj_m, const char *f)
{
    tabla = new Tabla(n, m, f);
}