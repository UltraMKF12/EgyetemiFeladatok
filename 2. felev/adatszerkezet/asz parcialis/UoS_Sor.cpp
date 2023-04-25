#include <iostream>
#include "UoS_Sor.h"
using namespace std;

UoS_Sor::UoS_Sor()
{
    list = new long long[1];
}

UoS_Sor::UoS_Sor(int meret)
{
    list = new long long[meret];
    size = meret;
    pointer = 0;
}

UoS_Sor::~UoS_Sor()
{
    delete[] list;
}

void UoS_Sor::InsertElement(long long PID)
{
    if(pointer < size)
    {
        list[pointer] = PID;
        pointer++;
    }
}

long long UoS_Sor::PopElement()
{
    if(pointer > 0)
    {
        pointer--;
        return list[pointer];
    }

    return 0;
}

void UoS_Sor::PrintList()
{
    for (int i = pointer - 1; i >= 0; i--)
    {
        cout << list[i] << " ";
    }
}