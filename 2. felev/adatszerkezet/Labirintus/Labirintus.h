#ifndef LABIRINTUS
#define LABIRINTUS

#include "Tabla.h"
class Labirintus
{
    private:
        Tabla *tabla;
        int n, m;
        int x, y;
    private:
        Labirintus(int uj_n, int uj_m, const char *f);
        
};

#endif