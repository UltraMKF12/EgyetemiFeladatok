#include <iostream>
using namespace std;

class E
{
    protected:
        int e;
    
    public:
        E(string& szoveg)
        {
            e = 5;
            szoveg += "E";
        }
};

class F
{
    protected:
        int f;
    
    public:
        F(string& szoveg)
        {
            f = 6;
            szoveg += "F";
        }
};

class A : public virtual E
{
    protected:
        int a;
    
    public:
        A(string& szoveg) : E(szoveg)
        {
            a = 1;
            szoveg += "A";
        }
};

class B : public virtual E
{
    protected:
        int b;
    
    public:
        B(string& szoveg) : E(szoveg)
        {
            b = 2;
            szoveg += "B";
        }
};

class C : public virtual E
{
    protected:
        int c;
    
    public:
        C(string& szoveg) : E(szoveg)
        {
            c = 3;
            szoveg += "C";
        }
};

class D : public F
{
    protected:
        int d;
    
    public:
        D(string& szoveg) :F(szoveg)
        {
            d = 4;
            szoveg += "D";
        }
};



class G : public F
{
    protected:
        int g;
    
    public:
        G(string& szoveg) : F(szoveg)
        {
            g = 7;
            szoveg += "G";
        }
};

class H : public F
{
    protected:
        int h;
    
    public:
        H(string& szoveg) : F(szoveg)
        {
            h = 8;
            szoveg += "H";
        }
};

class I
{
    protected:
        int i;
    
    public:
        I(string& szoveg)
        {
            i = 9;
            szoveg += "I";
        }
};

class J : public A, public B, public C, public D, public G, public H, public virtual I
{
    protected:
        int j;
    
    public:
        J(string& szoveg) : A::E(szoveg), A(szoveg), B(szoveg), C(szoveg), D(szoveg), G(szoveg), H(szoveg), I(szoveg)
        {
            j = 10;
            szoveg += "J";
        }
        void kiir()
        {
            cout << a << b << c << d << e << D::f << g << h << i << j;
        }
};

int main()
{
    string s = "";
    J j(s);
    j.kiir();

    cout << endl << endl << s;
    return 0;
}