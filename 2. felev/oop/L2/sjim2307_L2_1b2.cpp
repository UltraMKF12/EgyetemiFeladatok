// Széri József - 514/2
#include <iostream>
using namespace std;

class intervallum_class
{   
    private:
        double* intervallum; //2 elemű tömb

    public:
        intervallum_class(double, double);
        ~intervallum_class()
        {
            delete intervallum;
        }
        void duplaz();
        void kiir();
};

intervallum_class::intervallum_class(double elso, double masodik)
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

// intervallum_class::~intervallum_class()
// {
//     delete intervallum;
// }

void intervallum_class::duplaz()
{
    int hatar = intervallum[1] - intervallum[0];
    intervallum[0] -= hatar/2;
    intervallum[1] += hatar/2;
}

void intervallum_class::kiir()
{
    std::cout << "[" << intervallum[0] << "," << intervallum[1] << "]" << std::endl;
}

int main()
{
    intervallum_class a(6, 10);
    a.kiir();
    a.duplaz();
    a.kiir();
    // a.intervallum = new double[2]{0, 1};
    return 0;
}