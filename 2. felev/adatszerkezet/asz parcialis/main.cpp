#include <iostream>
#include <time.h>
#include "UoS_Utemezo.h"
#include "UoS_Sor.h"
using namespace std;

int main()
{
    srand(time(0));

    UoS_Utemezo gep(2, 3);
    gep.PrintProcesses();

    gep.InsertProcess(0, 123123);
    gep.InsertProcess(1, 23);

    gep.PrintProcesses();

    return 0;
}