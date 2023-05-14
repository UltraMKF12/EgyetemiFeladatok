#include <iostream>
using namespace std;

class Hossz_f;

class Hossz_m
{
    private:
        int m, dam, hm, km;
        double maradek;
    
    public:
        Hossz_m(int, int, int, int, double maradek=0);
        Hossz_m(const Hossz_f&); // Implicit konverzio
        void kiir();
};

class Hossz_f
{
    private:
        int fathom, pole, furlong, statute_mile;
    
    public:
        Hossz_f(int, int, int, int);
        operator Hossz_m(); // Explicit konverzio //return Hossz_m();
        void kiir();
        int get_fathom() const;
};

Hossz_m::Hossz_m(int m, int dam, int hm, int km, double maradek)
{
    this->m = m;
    this->dam = dam;
    this->hm = hm;
    this->km = km;
    this->maradek = maradek;
}

Hossz_m::Hossz_m(const Hossz_f &masik)
{
    double hossz = masik.get_fathom() * 1.83;
    m = hossz;
    dam = hossz/10;
    hm = hossz/100;
    km = hossz/1000;
    maradek = hossz - (int)hossz;
}

void Hossz_m::kiir()
{
    cout << "M = " << m << endl 
        << "Dam = " << dam << endl 
        << "Hm = " << hm << endl 
        << "Km = " << km << endl
        << "Maradek = " << maradek << endl << endl;
}


Hossz_f::Hossz_f(int fathom, int pole, int furlong, int statute_mile)
{
    this->fathom = fathom;
    this->pole = pole;
    this->furlong = furlong;
    this->statute_mile = statute_mile;
}

Hossz_f::operator Hossz_m()
{
    double hossz = fathom * 1.83;
    return Hossz_m(hossz, hossz/10, hossz/100, hossz/1000, hossz - (int)hossz);
}


void Hossz_f::kiir()
{
    cout << "Fathom= " << fathom << endl 
        << "Pole = " << pole << endl 
        << "Furlong = " << furlong << endl 
        << "Statute_mile = " << statute_mile << endl << endl;
}

int Hossz_f::get_fathom() const
{
    return fathom;
}


int main()
{
    int a, b, c, d;
    cout << "Fathom >> "; cin >> a;
    cout << "Pole >> "; cin >> b;
    cout << "Furlong >> "; cin >> c;
    cout << "Fathom = "; cin >> d;
    cout << endl;
    Hossz_f f(a, b, c, d);
    Hossz_m(f).kiir();
    Hossz_m m(1, 8, 5, 2);
    m.kiir();
    m = f;
    m.kiir();

    return 0;   
}