#include "Tabla.h"
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <fstream>
using namespace std;

Tabla::Tabla(int new_n, int new_m, const char *f="")
{
    n = new_n;
    m = new_m;

    tabla = new int*[n];
    for (int i = 0; i < n; i++)
    {
        tabla[i] = new int[m]();
    }

    if(f == "")
    {
        ifstream input(f);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                 input >> tabla[i][j];   
            }
        }
        input.close();
    }
    else
    {
        //Randomizalas
    }
}

Tabla::~Tabla()
{
    for (int i = 0; i < n; i++)
    {
        delete[] tabla[i];
    }
    delete[] tabla;
}

int Tabla::get_value(int x, int y) const
{
    if(x >= 0 && x < n && y >= 0 && y < m)
    {
        return tabla[x][y];
    }
    return -1;
}
void Tabla::set_value(int x, int y, int value)
{
    if(x >= 0 && x < n && y >= 0 && y < m)
    {
        tabla[x][y] = value;
    }
}

int Tabla::get_szelsseg() const
{
    return max(n, m);
}
int Tabla::get_magassag() const
{
    return min(n, m);
}

void Tabla::kiir() const
{
    system("cls");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << tabla[i][j] << " ";
        }
        cout << endl;
    }
}