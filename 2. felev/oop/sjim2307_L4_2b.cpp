#include <iostream>
using namespace std;

double ox_metszes(double x1, double y1, double x2, double y2)
{
    if((y1 * y2 > 0))
    {
        throw("Nem metszik");
    }

    double m = (y2 - y1) / (x2 - x1); // szakasz meredeksége
    double b = y1 - m * x1; // szakasz tengelymetszete
    double x = -b / m; // Ox tengely metszéspontja
    
    return x;

}

int main()
{
    try
    {
        double pont = ox_metszes(0, -1, 2, -1);
        cout << "Metszespont: " << pont << ", 0";
    }
    catch(const char* e)
    {
        cout << e;
    }
    
    return 0;
}