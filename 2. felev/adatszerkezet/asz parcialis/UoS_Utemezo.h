#ifndef utemezo
#define utemezo
#include "UoS_Sor.h"

class UoS_Utemezo
{
    private:
        int sor_count;
        int max_sor_length;
        UoS_Sor *sorok;
    
    public:
        UoS_Utemezo(int sorok_szama, int sor_max_hossz);
        ~UoS_Utemezo();
        void InsertProcess(int sorszam, long long PID);
        long long PickProcess();
        void PrintProcesses();
};

#endif