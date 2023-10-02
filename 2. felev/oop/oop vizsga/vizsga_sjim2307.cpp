//Széri József - 514
//sjim2307

#include <iostream>
#include <cstring>
using namespace std;

class Szemely
{   
    protected:
        char *nev;
        int eletkor;

    public:
        Szemely();
        Szemely(const char* nev, int eletkor);
        Szemely(const Szemely& masik);
        ~Szemely();

        Szemely& operator=(const Szemely& masik);
        void kiir();
        virtual void dolgozik() = 0;
};

Szemely::Szemely()
{
    this->nev = new char[1];
    this->nev[0] = ' ';
    this->eletkor = 0;
}

Szemely::Szemely(const char* nev, int eletkor)
{
    this->nev = new char[strlen(nev)];
    strcpy(this->nev, nev);
    this->eletkor = eletkor;
}

Szemely::Szemely(const Szemely& masik)
{
    this->nev = new char[strlen(masik.nev)];
    strcpy(this->nev, masik.nev);
    this->eletkor = masik.eletkor;
}

Szemely::~Szemely()
{
    if(this->nev != nullptr)
    {
        delete[] this->nev;
    }
}

Szemely& Szemely::operator=(const Szemely& masik)
{
    if(this->nev != nullptr)
    {
        delete[] this->nev;
    }
    this->nev = new char[strlen(masik.nev)];
    strcpy(this->nev, masik.nev);
    this->eletkor = masik.eletkor;

    return *this;
}

void Szemely::kiir()
{
    cout << "Nev: " << this->nev << ", Eletkor: " << this->eletkor;
}


class Diak : public Szemely 
{
    protected:
        double atlag;

    public:
        Diak(); 
        Diak(const char* nev, int eletkor, double atlag);
        class ErvenytelenAtlag{};

        Diak(const Diak& masik);

        Diak& operator++();
        Diak operator++(int);

        void dolgozik() override;
        void kiir();
};

Diak::Diak() : Szemely()
{
    atlag = 0;
}

Diak::Diak(const char* nev, int eletkor, double atlag) : Szemely(nev, eletkor)
{
    if(atlag < 0 || atlag > 10)
    {
        throw ErvenytelenAtlag();
    }
    this->atlag = atlag;
}

Diak::Diak(const Diak& masik) : Szemely(masik)
{
    this->atlag = masik.atlag;
}

Diak& Diak::operator++()
{
    atlag += 1;
    if(atlag > 10)
    {
        atlag = 10;
    }

    return *this;
}

Diak Diak::operator++(int)
{
    Diak temp(*this);
    atlag += 1;
    if(atlag > 10)
    {
        atlag = 10;
    }

    return temp;
}

void Diak::dolgozik()
{
    cout << "A diak dolgozik.";
}

void Diak::kiir()
{
    cout << "Nev: " << this->nev << ", Eletkor: " << this->eletkor << ", Atlag: " << this->atlag;
}


class Iskola
{
    private:
        Diak* diakok;
        int max_diakok;
        int jelenlegi_diakok;
    
    public:
        Iskola();
        Iskola(int max_diakok);
        ~Iskola();

        void iratkozik(const Diak& diak);
        void kiir();

        Iskola& operator=(const Iskola& masik);
        Iskola operator+(const Iskola& masik);
        Iskola& operator+=(const Iskola& masik);
};

Iskola::Iskola()
{
    diakok = nullptr;
    max_diakok = 0;
    jelenlegi_diakok = 0;
}

Iskola::Iskola(int max_diakok)
{
    this->max_diakok = max_diakok;
    this->diakok = new Diak[max_diakok];
    this->jelenlegi_diakok = 0;
}

Iskola::~Iskola()
{
    if(this->diakok != nullptr)
    {
        delete[] this->diakok;
    }
}

void Iskola::iratkozik(const Diak& diak)
{
    if(jelenlegi_diakok >= max_diakok)
    {
        throw "Az iskola tele van!";
    }
    else
    {
        diakok[jelenlegi_diakok] = diak;
        jelenlegi_diakok++;
    }
}

void Iskola::kiir()
{
    for (int i = 0; i < jelenlegi_diakok; i++)
    {
        diakok[i].kiir(); cout << endl;
    };   
}

Iskola& Iskola::operator=(const Iskola& masik)
{
    if(this->diakok != nullptr)
    {
        delete[] this->diakok;
    }

    this->max_diakok = masik.max_diakok;
    this->jelenlegi_diakok = masik.jelenlegi_diakok;

    this->diakok = new Diak[this->max_diakok];
    for (int i = 0; i < this->max_diakok; i++)
    {
        this->diakok[i] = masik.diakok[i];
    }
    
    return *this;
}

Iskola Iskola::operator+(const Iskola& masik)
{
    int uj_max = this->max_diakok + masik.max_diakok;
    Iskola uj(uj_max);
    for (int i = 0; i < this->jelenlegi_diakok; i++)
    {
        uj.iratkozik(this->diakok[i]);
    }

    for (int i = 0; i < masik.jelenlegi_diakok; i++)
    {
        uj.iratkozik(masik.diakok[i]);
    }
    
    return uj;
}

Iskola& Iskola::operator+=(const Iskola& masik)
{
    *this = (*this + masik);

    return *this;
}

int main()
{
    try
    {
        Diak a("Janos", 18, 7);
        Diak b("Pista", 17, 5);
        Diak c("Geza", 19, 10);

        a.kiir(); cout << endl;
        a.dolgozik(); cout << endl;
        a++.kiir(); cout << endl << endl;

        cout << "///// SULIK /////" << endl;
        Iskola suli1(2);
        suli1.iratkozik(a);
        suli1.iratkozik(b);
        // suli.iratkozik(c);
        suli1.kiir(); cout << endl;

        Iskola suli2(1);
        suli2.iratkozik(c);
        suli2.kiir(); cout << endl;

        (suli1 + suli2).kiir(); cout << endl;
        suli1 += suli2;
        suli1.kiir(); cout << endl;
    }
    catch(Diak::ErvenytelenAtlag)
    {
        cout << "Ervenytelen atlag!" << endl;
    }
    catch(const char* s)
    {
        cout << s << endl;
    }
    
    return 0;
}