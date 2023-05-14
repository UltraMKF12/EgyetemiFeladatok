#include <iostream>
#include <math.h>
using namespace std;

class Komplex
{
    private:
        double real;
        double imaginary;
    
    public:
        Komplex(double);
        Komplex(double, double);
        void kiir();
        Komplex &operator *=(const Komplex &i);
        Komplex &operator /=(const Komplex &i);
};

Komplex::Komplex(double real)
{
    this->real = real;
    this->imaginary = 0;
}

Komplex::Komplex(double real, double imaginary)
{
    this->real = real;
    this->imaginary = imaginary;
}

void Komplex::kiir()
{
    cout << real << ", " << imaginary << "i" << endl;
}

Komplex& Komplex::operator *=(const Komplex &i)
{
    double a = this->real;
    double b = this->imaginary;
    double c = i.real;
    double d = i.imaginary;

    double multiplication_real = (a * c) - (b * d);
    double multiplication_img = (a * d + b * c);
    this->real = multiplication_real;
    this->imaginary = multiplication_img;
    return *this;
}

Komplex& Komplex::operator /=(const Komplex &i)
{
    double a = this->real;
    double b = this->imaginary;
    double c = i.real;
    double d = i.imaginary;

    double division_real = (a*c + b*d) / (pow(c, 2) + pow(d, 2));
    double division_img = (b*c - a*d) / (pow(c, 2) + pow(d, 2));
    this->real = division_real;
    this->imaginary = division_img;
    return *this;
}

int main()
{
    Komplex a(1,5);
    a *= 2;      // előbb 2-ről Komplex-re konvertál
    a.kiir();
    a /= 2;      // előbb 2-ről Komplex-re konvertál
    a.kiir();
    Komplex b(5);
    b.kiir();    // Az imaginárius rész 0. Kimenet: 5
}