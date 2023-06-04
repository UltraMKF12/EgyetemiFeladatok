//Széri József - 514/2
//sjim2307

#pragma once
#include <iostream>
using namespace std;

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

        NagyEgesz operator+(const NagyEgesz &other);
        NagyEgesz operator-(const NagyEgesz &other);
        NagyEgesz operator*(const NagyEgesz &other);
        NagyEgesz operator/(const NagyEgesz &other);
        NagyEgesz& operator++();
        NagyEgesz operator++(int);

        NagyEgesz& operator=(const NagyEgesz &other);
        NagyEgesz& operator+=(const NagyEgesz &other);
        NagyEgesz& operator-=(const NagyEgesz &other);
        NagyEgesz& operator*=(const NagyEgesz &other);
        NagyEgesz& operator/=(const NagyEgesz &other);

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

// +-*/
NagyEgesz NagyEgesz::operator+(const NagyEgesz &other) 
{
    int hossz;

    if(this->hossz > other.hossz)
    {
        hossz = other.hossz;
    }
    else
    {
        hossz = this->hossz;
    }

    if(this->elojel == other.elojel)
    {
        elojel = this->elojel;
    }
    else if(this->elojel >= 0 && other.elojel >= 0)
    {   
        if(this->elojel == 0 && other.elojel == 0)
        {
            elojel = 0;
        }
        else
        {
            elojel = 1; // Lekezelni a 0 + POZITIV eseteket.
        }
    }
    else
    {
        //Pozitiv + Negativ , Negativ + Pozitiv esetek;
    }


    int szamok[1000];
}

NagyEgesz NagyEgesz::operator-(const NagyEgesz &other) 
{

}

NagyEgesz NagyEgesz::operator*(const NagyEgesz &other) 
{

}

NagyEgesz NagyEgesz::operator/(const NagyEgesz &other) 
{

}

// Prefix
NagyEgesz& NagyEgesz::operator++() 
{
    this->operator+(NagyEgesz(1));
    return *this;
}

// Suffix
NagyEgesz NagyEgesz::operator++(int) 
{
    NagyEgesz temp = *this;
    this->operator+(NagyEgesz(1));
    return temp;
}

// =
NagyEgesz& NagyEgesz::operator=(const NagyEgesz &other)
{
    this->hossz = other.hossz;
    this->elojel = other.elojel;
    delete[] this->szam;
    this->szam = new int[other.hossz];
    for (int i = 0; i < other.hossz; i++)
    {
        this->szam[i] = other.szam[i];
    }

    return *this;
}

NagyEgesz& NagyEgesz::operator+=(const NagyEgesz &other)
{
    this->operator=((this->operator+(other)));
    return *this;
}

NagyEgesz& NagyEgesz::operator-=(const NagyEgesz &other)
{
    this->operator=((this->operator-(other)));
    return *this;
}

NagyEgesz& NagyEgesz::operator*=(const NagyEgesz &other)
{
    this->operator=((this->operator*(other)));
    return *this;
}

NagyEgesz& NagyEgesz::operator/=(const NagyEgesz &other)
{
    this->operator=((this->operator/(other)));
    return *this;
}

// <<
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
    int egy[] =   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int ketto[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

    NagyEgesz a(1, 20, egy);
    NagyEgesz b(1, 20, ketto);

    NagyEgesz c((a + b));
    cout << c;

    return 0;
}
