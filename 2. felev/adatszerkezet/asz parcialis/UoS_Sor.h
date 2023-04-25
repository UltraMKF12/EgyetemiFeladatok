#ifndef sor
#define sor

class UoS_Sor
{
    private:
        int size;
        int pointer;
        long long *list;
    
    public:
        UoS_Sor();
        UoS_Sor(int meret);
        ~UoS_Sor();
        void InsertElement(long long PID);
        long long PopElement();
        void PrintList();
};

#endif