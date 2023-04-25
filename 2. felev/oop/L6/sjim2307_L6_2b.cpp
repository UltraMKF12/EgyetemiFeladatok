// Széri József - 514/2
#include <iostream>
using namespace std;

class Intervallum
{
    private:
        int kezdopont, vegpont;

    public:
        Intervallum();
        Intervallum(int, int);

        Intervallum& operator--();
        Intervallum operator--(int);

        void kiir();

};

Intervallum::Intervallum()
{
    kezdopont = 0;
    vegpont = 0;
}

Intervallum::Intervallum(int elso, int masodik)
{
    if(elso > masodik)
    {
        throw("Masodik parameter nagyobb mint az elso!");
    }

    kezdopont = elso;
    vegpont = masodik;
}

Intervallum& Intervallum::operator--()
{
    kezdopont++;
    vegpont--;
    return *this;
}

Intervallum Intervallum::operator--(int szam)
{
    Intervallum temp(*this);
    kezdopont++;
    vegpont--;
    return temp;
}

void Intervallum::kiir()
{
    cout << "[" << kezdopont << "-" << vegpont << "]" << endl;
}

int main()
{
    try
    {
        Intervallum a(6, 5);
        a.kiir();
        (a--).kiir();
        a.kiir();
    }    
    catch(const char *e)
    {
        cout << e << endl;
    }
}