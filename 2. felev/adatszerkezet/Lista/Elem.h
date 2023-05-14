#ifndef ELEM
#define ELEM
#include <iostream>
using namespace std;

class Elem
{
    private:
        string nev;
        double atlag;
        Elem* kov;
    
    public:
        Elem(string, double);
        ~Elem();
        void Kiir();
        void SetKov(Elem*);
        Elem* GetKov();
        string GetNev();
        double GetAtlag();
};

#endif