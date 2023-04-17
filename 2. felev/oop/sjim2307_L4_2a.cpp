// Széri József - 514/2
#include <iostream>
#include <stdexcept>
using namespace std;

class Vektor
{
    private:
        double *koord;
        int dim;
    
    public:
        class KulonDim {};
        class HibasIndex {};
        Vektor(int d, double *k)
        {
            koord = new double[d];
            dim = d;
            for (int i = 0; i < dim; i++)
            {
                koord[i] = k[i];
            }
        }
        Vektor(const Vektor& v)
        {
            koord = new double[v.dim];
            dim = v.dim;
            for (int i = 0; i < dim; i++)
            {
                koord[i] = v.koord[i];
            }
        }
        ~Vektor()
        {
            delete[] koord;
        }
        Vektor osszead(const Vektor& v) const
        {
            if(dim != v.dim)
            {
                throw KulonDim();
            }
            Vektor uj(dim, koord);
            for (int i = 0; i < dim; i++)
            {
                uj.koord[i] += v.koord[i];
            }
            return uj;
        }
        Vektor kivon(const Vektor& v) const
        {
            if(dim != v.dim)
            {
                throw KulonDim();
            }
            Vektor uj(dim, koord);
            for (int i = 0; i < dim; i++)
            {
                uj.koord[i] -= v.koord[i];
            }
            return uj;
        }
        double skalarSzorzat(const Vektor& v) const
        {
            if(dim != v.dim)
            {
                throw KulonDim();
            }

            double skalar = 0;

            for (int i = 0; i < dim; i++)
            {
                skalar += koord[i] * v.koord[i];
            }
            return skalar;
        }
        double lekerdez(int n) const
        {
            if(n < 0 || n >= dim)
            {
                throw HibasIndex();
            }
            return koord[n];
        }
        void beallit(int n, double k)
        {
            if(n < 0 || n >= dim)
            {
                throw HibasIndex();
            }
            koord[n] = k;
        }
};

int main()
{
    try
    {
        double szamok[] =  {1,   2,   3.1,   4};
        double szamok2[] = {1.1, 2.1, 3.4, 4.2};
        double szamok3[] = {6.5 ,4};
        Vektor vektor1(4, szamok);
        Vektor vektor2(4, szamok2);
        Vektor vektor3(2, szamok3);

        Vektor uj = vektor1.osszead(vektor3);
        cout << vektor3.lekerdez(1);
    }
    catch(Vektor::KulonDim)
    {
        cout << "Kulon dim";
    }
    catch(Vektor::HibasIndex)
    {
        cout << "Hibas Index";
    }
    

    return 0;
}