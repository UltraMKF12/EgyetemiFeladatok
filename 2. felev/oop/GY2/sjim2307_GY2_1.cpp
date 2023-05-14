//Széri József - 514
#include <iostream>
#include <vector>
using namespace std;

class BuvosNegyzet
{
    private:
        int size;
        int max_length;
        int correct_count;
        int **tabla;
    
    public:
        BuvosNegyzet();
        BuvosNegyzet(int);
        ~BuvosNegyzet();
        void Generalas(int);
        bool isOk();
        int getCount();
};

BuvosNegyzet::BuvosNegyzet()
{
    this->size = 0;
    this->max_length = 0;
    this->correct_count = 0;
}

BuvosNegyzet::BuvosNegyzet(int size)
{
    this->size = size;
    this->max_length = size*(size*size + 1) / 2;
    this->correct_count = 0;

    tabla = new int*[size];
    for (int i = 0; i < size; i++)
    {
        tabla[i] = new int[size];
    }
}

BuvosNegyzet::~BuvosNegyzet()
{
    if(tabla != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            delete[] tabla[i];
        }
        delete[] tabla;
    }
}

void BuvosNegyzet::Generalas(int melyseg)
{
    if(melyseg >= (size*size) - 1)
    {
        if(isOk())
        {
            correct_count++;
        }
    }
    else
    {
        for (int i = 1; i <= (size*size); i++)
        {
            tabla[melyseg/size][melyseg%size] = i;
            cout << melyseg << " ";
            Generalas(melyseg+1);
        }
    }
}

bool BuvosNegyzet::isOk()
{
    //Sorosszeg
    for (int i = 0; i < size; i++)
    {
        int osszeg = 0;
        for (int j = 0; j < size; j++)
        {
            osszeg += tabla[i][j];
        } 

        if(osszeg != max_length)
        {
            return false;
        }
    }
    
    //Oszloposszeg
    for (int i = 0; i < size; i++)
    {
        int osszeg = 0;
        for (int j = 0; j < size; j++)
        {
            osszeg += tabla[j][i];
        } 

        if(osszeg != max_length)
        {
            return false;
        }
    }

    return true;
}

int BuvosNegyzet::getCount()
{
    return correct_count;
}

int main()
{
    BuvosNegyzet a(3);
    a.Generalas(0);
    cout << a.getCount();
}