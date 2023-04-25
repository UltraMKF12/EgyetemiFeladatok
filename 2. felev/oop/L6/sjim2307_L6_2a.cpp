// Széri József - 514/2
#include <iostream>
using namespace std;

class Matr2
{
private:
    double a11, a12, a21, a22;

public:
    Matr2();
    Matr2(double, double, double, double);
    Matr2 operator+(const Matr2 &);
    Matr2 &operator+=(const Matr2 &);
    Matr2 operator*(const Matr2 &);
    Matr2 &operator*=(const Matr2 &);
    double operator~();
};

Matr2::Matr2()
{
    a11 = 0;
    a12 = 0;
    a21 = 0;
    a22 = 0;
}

Matr2::Matr2(double b11, double b12, double b21, double b22)
{
    a11 = b11;
    a12 = b12;
    a21 = b21;
    a22 = b22;
}

Matr2 Matr2::operator+(const Matr2 &other)
{
    Matr2 temp;
    temp.a11 = a11 + other.a11;
    temp.a12 = a12 + other.a12;
    temp.a21 = a21 + other.a21;
    temp.a22 = a22 + other.a22;

    return temp;
}

Matr2& Matr2::operator+=(const Matr2 &other)
{
    a11 += other.a11;
    a12 += other.a12;
    a21 += other.a21;
    a22 += other.a22;

    return *this;
}

Matr2 Matr2::operator*(const Matr2 &other)
{
    Matr2 temp;
    temp.a11 = a11 * other.a11;
    temp.a12 = a12 * other.a12;
    temp.a21 = a21 * other.a21;
    temp.a22 = a22 * other.a22;

    return temp;
}

Matr2& Matr2::operator*=(const Matr2 &other)
{
    a11 *= other.a11;
    a12 *= other.a12;
    a21 *= other.a21;
    a22 *= other.a22;

    return *this;
}

double Matr2::operator~()
{
    return a11*a22 - a12*a21;
}

int main()
{
    Matr2 egy(1, 1, 2, 2);
    Matr2 ketto(1, 0, 0, 1);

    Matr2 harom = egy + ketto;

    harom += egy;

    Matr2 negy = egy * harom;

    negy *= ketto;

    cout << ~negy;
}