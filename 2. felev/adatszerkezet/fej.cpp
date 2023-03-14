#include "fej.h"
#include <iostream>

IntArray* Create(int n)
{
    IntArray* a = new IntArray;
    a->t = new int[n];
    a->meret = n;
    return a;
}

void Destroy(IntArray*)
{

}

int GetValue(IntArray*, int)
{

}

void SetValue(IntArray*, int, int)
{
    
}