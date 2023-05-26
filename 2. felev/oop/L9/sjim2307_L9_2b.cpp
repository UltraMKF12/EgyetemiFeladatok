#include <iostream>
using namespace std;

class Alakzat
{
    public:
        virtual int terulet() = 0;
        virtual int kerulet() = 0;
        virtual void nagyit(double s) = 0;
};

class Teglalap : public Alakzat
{
    protected:
        double hosszusag, szelesseg;
    
    public:
        Teglalap()
        {
            hosszusag = 0;
            szelesseg = 0;
        }
        Teglalap(int hosszusag, int szelesseg)
        {
            this->hosszusag = hosszusag;
            this->szelesseg = szelesseg;
        }
        int terulet() override
        {
            return hosszusag * szelesseg;
        }
        int kerulet() override
        {
            return (2 * hosszusag + 2 * szelesseg);
        }
        void nagyit(double s) override
        {
            hosszusag *= s;
            szelesseg *= s;
        }
};

class Negyzet : public Teglalap
{
    public:
        Negyzet() : Teglalap()
        {

        }
        Negyzet(double hosszusag, double szelesseg) : Teglalap(hosszusag, szelesseg)
        {
            if(hosszusag != szelesseg)
            {
                throw("!!Az alakzat nem negyzet!!");
            }
        }
};

class Kor : public Alakzat
{
    protected:
        double radius;
    
    public:
        Kor()
        {
            radius = 0;
        }
        Kor(double radius)
        {
            this->radius = radius;
        }
        int terulet() override
        {
            return 3.14 * radius * radius;
        }
        int kerulet() override
        {
            return 2 * 3.14 * radius;
        }
        void nagyit(double s) override
        {
            radius *= s;
        }
};


int main()
{   
    try
    {
        Alakzat *a[] = {new Kor(3), new Teglalap, new Negyzet(2,3)};
        cout << a[0]->kerulet() << ", " << a[0]->terulet() << endl;
        cout << a[1]->kerulet() << ", " << a[1]->terulet() << endl;
        cout << a[2]->kerulet() << ", " << a[2]->terulet() << endl;
    }
    catch(const char* e)
    {
        cout << e;
    }
    return 0;
}