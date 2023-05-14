#include "Elem.h"
#include "Lista.h"
#include <iostream>
using namespace std;


int main()
{
    Lista alma = Lista();
    alma.Kiir();
    alma.Beszuras_sor("Jani", 34);
    alma.Beszuras_sor("Feri", 74);
    alma.Beszuras_verem("Pista", 64);
    alma.Kiir();
    cout << endl;
    alma.Rendezes(1);
    alma.Kiir();

    return 0;
}