#ifndef TABLA
#define TABLA

class Tabla
{
    private:
        int **tabla;
        int n, m;
    private:
        Tabla(int uj_n, int uj_m, const char *f);
        ~Tabla();
        int get_value(int x, int y) const;
        void set_value(int x, int y, int value);
        int get_szelsseg() const;
        int get_magassag() const;
        void kiir() const;
};

#endif