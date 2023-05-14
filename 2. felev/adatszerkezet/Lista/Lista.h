#ifndef LISTA
#define LISTA

#include "Elem.h"
#include <iostream>
using namespace std;

class Lista 
{
    private:
        Elem* eleje;
        Elem* vege;
        int rendezett;

    public:
        Lista();
        ~Lista();
        void Kiir();
        void Beszuras_sor(string, double);
        void Beszuras_verem(string, double);
        void Beszuras_rendezett(string, double);
        void Rendezes(int);
};

#endif