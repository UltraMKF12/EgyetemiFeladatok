#include <iostream>
using namespace std;

class rac
{
    protected:
        int szamlalo;
        int nevezo;
    
    public:
        rac(int=0, int=1);
        virtual rac operator/(const rac&) const;
        rac& operator/=(const rac&);
        void kiir() const;
        int getSzamlalo() const;
        int getNevezo() const;
};

rac::rac(int szamlalo, int nevezo)
{
    this->szamlalo = szamlalo;
    this->nevezo = nevezo;
}

rac rac::operator/(const rac& other) const
{
    int uj_szamlalo = szamlalo * other.nevezo;
    int uj_nevezo = nevezo * other.szamlalo;
    return rac(uj_szamlalo, uj_nevezo);
}

rac& rac::operator/=(const rac& other)
{
    *this = *this / other;
    return *this;
}

void rac::kiir() const
{
    cout << szamlalo << " / " << nevezo << endl;
}

int rac::getNevezo() const
{
    return nevezo;
}

int rac::getSzamlalo() const
{
    return szamlalo;
}


class rackiir : public rac
{
    public:
        rackiir(int=0, int=1);
        rac operator/(const rac&) const;
};

rackiir::rackiir(int szamlalo, int nevezo) : rac(szamlalo, nevezo)
{
}

rac rackiir::operator/(const rac& other) const
{
    rac eredmeny = this->rac::operator/(other);
    // (3 / 4) / (5 / 2) = 6 / 20 )
    cout << "(" << this->nevezo << " / " << this->szamlalo << ")";
    cout << " / ";
    cout << "(" << other.getNevezo() << " / " << other.getSzamlalo() << ")";
    cout << " = ";
    eredmeny.kiir();

    return eredmeny;
}

int main()
{
    rac p(3,4), q(5,2), r;

    r = p /= q;

    p.kiir();

    r.kiir();

    rackiir p1(3,4), q1(5,2);

    rac r1, r2;

    r1 = p1 / q1;

    r2 = p1 /= q1;

    p1.kiir();

    r1.kiir();

    r2.kiir();

    return 0;
}