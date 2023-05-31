#pragma once
#include <iostream>
using namespace std;

//[ELOJEL: -1, 0, 1][1][2][3][7][6][9]
class NagyEgesz
{
    private:
        int* szam;
        int hossz;
        int elojel;

    public:
        NagyEgesz();
        NagyEgesz(int elojel, int n, const int* szamjegyek);
        NagyEgesz(const NagyEgesz&);
        NagyEgesz(int szam);
        NagyEgesz(long long szam);
        ~NagyEgesz();

        class NullavalValoOsztas{};

        ostream& print(ostream &s);
};

NagyEgesz::NagyEgesz()
{
    this->szam = new int[1];
    this->szam[0] = 0;
    this->elojel = 0;
}

NagyEgesz::NagyEgesz(int elojel, int n, const int* szamjegyek)
{
    this->hossz = n;
    this->elojel = elojel;
    this->szam = new int[n];
    for (int i = 0; i < n; i++)
    {
        this->szam[i] = szamjegyek[i];
    }
}

NagyEgesz::NagyEgesz(const NagyEgesz& other)
{
    this->hossz = other.hossz;
    this->elojel = other.elojel;
    this->szam = new int[other.hossz];
    for (int i = 0; i < other.hossz; i++)
    {
        this->szam[i] = other.szam[i];
    }
}

NagyEgesz::NagyEgesz(int szam) : NagyEgesz(static_cast<long long>(szam))
{
    
}

NagyEgesz::NagyEgesz(long long szam)
{
    if(szam == 0)
    {
        NagyEgesz();
    }

    else
    {
        //Előjel ellenörzés + csak pozitiv szamokkal dolgozunk
        if(szam > 0)
        {
            elojel = 1;
        }
        else
        {
            elojel = -1;
            szam *= -1;
        }

        //Megszerezni a szám számjegyeinek számát.
        int hossz = 0;
        long long temp = szam;
        while(temp > 0)
        {
            temp /= 10;
            hossz++;
        }

        this->hossz = hossz;
        this->szam = new int[hossz];

        //Újra átmenni a számon és visszafele feltölteni a NagyEgesz szám tömböt.
        int szamlalo = hossz-1;
        int szamjegy;
        temp = szam;
        while(temp > 0)
        {
            szamjegy = temp%10;
            temp /= 10;
            this->szam[szamlalo] = szamjegy;
            szamlalo--;
        }
    }
}


NagyEgesz::~NagyEgesz()
{
    delete[] szam;
}

ostream& NagyEgesz::print(ostream &s)
{
    if(this->elojel < 0)
    {
        s << "-";
    }

    for (int i = 0; i < this->hossz; i++)
    {
        s << this->szam[i];
    }
    return s;
}


ostream& operator <<(ostream &s, NagyEgesz &o){
	return o.print(s);
}

int main()
{
    int alma[] = {1,2,3, 4, 5, 6, 3, 2, 2,4, 6, 6, 7, 7,7 , 7, 7,7 ,7 ,7 ,4,1 , 2,2 , 1,1 ,3 , 5, 2,6,5 ,3};

    NagyEgesz a(0, 32, alma);
    cout << a;

    return 0;
}
