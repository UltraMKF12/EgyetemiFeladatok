#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include "halastoM.h"
using namespace std;

/// A modul hasznalatahoz a foprogrambol meg kell hivni egyszer a veletlenszam-generator inicializalojat
void Init()
{
    srand(time(0));
}

///Letrehozas
Halasto* Create(int n, int m)
{
    Halasto *uj = new Halasto;
    uj->n = n;
    uj->m = m;
    uj->to = new int*[n];
    for(int i = 0; i < n; i++) 
    {
        uj->to[i] = new int[m]();
    }
    uj->db = 0;
    uj->fajtak_db = 0;
    for (int i = 0; i < 101; i++)
    {
        uj->fajtak[i] = 0;
    }

    return uj;
}
Halasto* CreateFromFile(const char *name)
{
    ifstream input(name);
    int n, m;
    input >> n >> m;

    Halasto *uj = Create(n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int hal;
            input >> hal;
            PutHal(uj, i, j, hal);
        }
    }
    input.close();
    return uj;
}
Halasto* CreateWild(int n, int m)
{
    Halasto *uj = Create(n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {   
            int hal = 0;

            int ures = rand()%5;
            if(ures == 0)
            {
                hal = rand()%101;
            }

            PutHal(uj, i, j, hal);
        }
    }
    return uj;
}

//Felszabditas
void Destroy(Halasto* tavacska)
{
    for(int i = 0; i < tavacska->n; i++) 
    {
        delete[] tavacska->to[i];
    }
    delete[] tavacska->to;

    delete tavacska;
}

///Muveletek
void PutHal(Halasto* tavacska, int i, int j , int faj)
{
    //Kivenni az elozo halat.
    if(tavacska->to[i][j] != 0)
    {
        tavacska->db--;
        tavacska->fajtak[tavacska->to[i][j]]--;
        if(tavacska->to[i][j] == 0)
        {
            tavacska->fajtak_db--;
        }
    }

    //Betenni az uj halat.
    tavacska->to[i][j] = faj;
    if(faj > 0)
    {
        tavacska->db++;
        if(tavacska->fajtak[faj] == 0)
        {
            tavacska->fajtak_db++;
        }
        tavacska->fajtak[faj]++;
    }
}
int GetHal(Halasto* tavacska, int i, int j)
{
    if (i > tavacska->n || j > tavacska->m)
    {
        return -1;
    }
    return tavacska->to[i][j];
}
int GetSzelesseg(Halasto* tavacska)
{
    return (tavacska->n > tavacska->m) ? tavacska->m : tavacska->n;
}
int GetHosszusag(Halasto* tavacska)
{
    return (tavacska->n < tavacska->m) ? tavacska->m : tavacska->n;
}
int FajtakSzama(Halasto* tavacska)
{
    return tavacska->fajtak_db;
}
int SzabadAHely(Halasto* tavacska, int i, int j)
{
    if (i > tavacska->n || j > tavacska->m)
    {
        return 0;
    }
    return (tavacska->to[i][j] == 0) ? 1 : 0;
}
Halasto* Tornado(Halasto* tavacska)
{
    int uj_n = rand() % 10 + 1;
    int uj_m = rand() % 10 + 1;

    Halasto *uj = Create(uj_n, uj_m);

    //Keveres
    for (int i = 0; i < 1000; i++)
    {
        int elso_x = rand() % tavacska->n;
        int elso_y = rand() % tavacska->m;
    
        int masodik_x = rand() % tavacska->n;
        int masodik_y = rand() % tavacska->m;

        int temp_elso = tavacska->to[elso_x][elso_y];
        int temp_masodik = tavacska->to[masodik_x][masodik_y];

        tavacska->to[elso_x][elso_y] = temp_masodik;
        tavacska->to[masodik_x][masodik_y] = temp_elso;
    }
    

    //Masolas
    int kisebb_n = min(tavacska->n, uj_n);
    int kisebb_m = min(tavacska->m, uj_m);
    for (int i = 0; i < kisebb_n; i++)
    {
        for (int j = 0; j < kisebb_m; j++)
        {
            PutHal(uj, i, j, tavacska->to[i][j]);
        }
    }

    //Ujrakeveres
    for (int i = 0; i < 1000; i++)
    {
        int elso_x = rand() % uj->n;
        int elso_y = rand() % uj->m;
    
        int masodik_x = rand() % uj->n;
        int masodik_y = rand() % uj->m;

        int temp_elso = uj->to[elso_x][elso_y];
        int temp_masodik = uj->to[masodik_x][masodik_y];

        uj->to[elso_x][elso_y] = temp_masodik;
        uj->to[masodik_x][masodik_y] = temp_elso;
    }


    Destroy(tavacska);
    return uj;
}

///Horgaszmuveletek - a kifogott halak nem maradnak a toban
int GetHalKezdo(Halasto* tavacska)
{
    int i = rand() % tavacska->n;
    int j = rand() % tavacska->m;

    int fogas = tavacska->to[i][j];
    PutHal(tavacska, i, j, 0);
    return fogas;
}
int GetHalAdvanced(Halasto* tavacska, int i1 ,int i2, int j1, int j2)
{   
    int i = rand() % (rand() % (i2-i1+1) + i2);
    int j = rand() % (rand() % (j2-j1+1) + j2);

    int fogas = tavacska->to[i][j];
    PutHal(tavacska, i, j, 0);
    return fogas;
}

///Kiirasok
void StatKezdo(Halasto* tavacska)
{
    for (int i = 0; i < 101; i++)
    {
        if(tavacska->fajtak[i] > 0)
        {
            cout << i << ": " << tavacska->fajtak[i] << " db" << endl;
        }
    }
    cout << endl;
}
void StatHalado(Halasto* tavacska, int i1 ,int i2, int j1, int j2)
{
    int statisztika[101] = {0};
    for (int i = i1; i <= i2; i++)
    {
        for (int j = j1; j <= j2; j++)
        {
            statisztika[tavacska->to[i][j]]++;
        }
    }

    for (int i = 1; i < 101; i++)
    {
        if(statisztika[i] > 0)
        {
            cout << i << ": " << statisztika[i] << " db" << endl;
        }
    }
    cout << endl;
}
void PrintH(Halasto* tavacska)
{
    if(tavacska == NULL)
    {
        cout << "NEM LETEZIK!";
        return;
    }

    for (int i = 0; i < tavacska->n; i++)
    {
        for (int j = 0; j < tavacska->m; j++)
        {
            cout << tavacska->to[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Halak szama: " << tavacska->db;
    cout << endl << endl;
}

int main()
{
    Init();

    Halasto *ketto = CreateFromFile("halasto.txt");

    PrintH(ketto);
    StatKezdo(ketto);

    ketto = Tornado(ketto);

    PrintH(ketto);
    StatKezdo(ketto);
    Destroy(ketto);

    return 0;
}