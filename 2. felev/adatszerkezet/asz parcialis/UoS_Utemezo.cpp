#include <iostream>
#include "UoS_Utemezo.h"
#include "UoS_Sor.h"
using namespace std;

UoS_Utemezo::UoS_Utemezo(int sorok_szama, int sor_max_hossz)
{
    sor_count = sorok_szama;
    max_sor_length = sor_max_hossz;

    sorok = new UoS_Sor[sor_count];
    for (int i = 0; i < sor_count; i++)
    {
        sorok[i] = UoS_Sor(sor_max_hossz);
    }
}

UoS_Utemezo::~UoS_Utemezo()
{
    delete[] sorok;
}

void UoS_Utemezo::InsertProcess(int sorszam, long long PID)
{
    if(sorszam >= 0 && sorszam < sor_count)
    {
        sorok[sorszam].InsertElement(PID);
    }
}

long long UoS_Utemezo::PickProcess()
{
    int valasztott_sor = rand() % sor_count;
    return sorok[valasztott_sor].PopElement();
}

void UoS_Utemezo::PrintProcesses()
{
    for (int i = 0; i < sor_count; i++)
    {
        cout << i << ": ";
        sorok[i].PrintList();
        cout << endl;
    }
}