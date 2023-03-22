// Széri József - 514/2
#include <iostream>
#include <math.h>
using namespace std;

class Pont
{   
    private:
        double x,y;

    public:
        Pont()
        {
            x = 0;
            y = 0;
        }
        Pont(double uj_x, double uj_y)
        {
            x = uj_x;
            y = uj_y;
        }
        void kiir() const
        {
            cout << x << ", " << y << endl;
        }
        double get_x() const
        {
            return x;
        }
        double get_y() const
        {
            return y;
        }
};

class Vektor
{
    private:
        Pont kezdopont, vegpont;
    
    public:
        Vektor(): kezdopont(), vegpont() {}
        Vektor(const Pont &kezdo, const Pont &veg): kezdopont(kezdo), vegpont(veg) {}
        Pont get_kezdopont() const
        {
            return kezdopont;
        }
        Pont get_vegpont() const
        {
            return vegpont;
        }
        double eukledeszi_norma() const
        {
            return sqrt(pow((vegpont.get_x() - kezdopont.get_x()),2) + 
                        pow((vegpont.get_y() - kezdopont.get_y()),2));
        }

        double ox_tengly_bezart() const
        {
            return atan2(abs(vegpont.get_y()-kezdopont.get_y()), abs(vegpont.get_x() - kezdopont.get_x()));
        }
};


int main()
{
    Vektor alma(Pont(1, 1), Pont(2, 2));

    cout << "Eukledeszi norma: " << alma.eukledeszi_norma() << endl;
    cout << "OX tengellyel bezart szog: " << alma.ox_tengly_bezart();
    return 0;
}