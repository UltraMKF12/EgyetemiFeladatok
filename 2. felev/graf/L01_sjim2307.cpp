//sjim2307 - Széri József
//Lab 1
#include <iostream>
#include <vector>
using namespace std;


struct suly
{
    int suly;
    bool letezik;
};

struct el
{
    int kezdet;
    int veg;
    suly suly;
};

void szomszedsagi_matrix_felepites(vector<vector<suly>> &matrix, int m)
{   
    int pont1, pont2, suly;
    for(int i = 0; i < m; i++)
    {
        cin >> pont1 >> pont2 >> suly;
        matrix[pont1][pont2] = {suly, true};
        matrix[pont2][pont1] = {suly, true};
    }
}

void alakit_szomszedsagi_incidencia(const vector<vector<suly>> &szomszedsagi, vector<vector<el>> &incidencia)
{
    int jelenlegi_el = 1;
    for (int sor = 1; sor < szomszedsagi.size(); sor++)
    {
        for (int oszlop = sor; oszlop < szomszedsagi.size(); oszlop++)
        {
            if(szomszedsagi[sor][oszlop].letezik)
            {
                incidencia[sor][jelenlegi_el] = {sor, oszlop, szomszedsagi[sor][oszlop]};
                incidencia[oszlop][jelenlegi_el] = {oszlop, sor, szomszedsagi[sor][oszlop]};
                jelenlegi_el++;
            }
        }
    }
}

void alakit_incidencia_szomszedsagi_lista(const vector<vector<el>> &incidencia, vector<vector<el>> &szomszedsagi_lista)
{
    int sorok_szama = incidencia.size();
    int oszlopok_szama = incidencia[0].size();
    for (int oszlop = 1; oszlop < oszlopok_szama; oszlop++)
    {
        for (int sor = 1; sor < sorok_szama; sor++)
        {
            if(incidencia[sor][oszlop].suly.letezik)
            {
                szomszedsagi_lista[sor].push_back(incidencia[sor][oszlop]);
            }
        }
    }
}

void alakit_szomszedsagi_lista_el_lista(const vector<vector<el>> &szomszedsagi_lista, vector<el> &el_lista)
{
    for (int i = 1; i < szomszedsagi_lista.size(); i++)
    {
        for (int j = 0; j < szomszedsagi_lista[i].size(); j++)
        {
            int kezdet = szomszedsagi_lista[i][j].kezdet;
            int veg = szomszedsagi_lista[i][j].veg;

            if(kezdet <= veg)
            {
                el_lista.push_back(szomszedsagi_lista[i][j]);
            }
        }
    }
}



void kiir_szomszedsagi(const vector<vector<suly>> &matrix)
{    
    int csucsok_szama = matrix.size();
    int elek_szama = matrix[0].size();
    for (int i = 1; i < csucsok_szama; i++)
    {
        for (int j = 1; j < elek_szama; j++)
        {
            if(matrix[i][j].letezik)
            {
                cout << matrix[i][j].suly << " ";
            }
            else
            {
                cout << "-" << " ";
            }
        }
        cout << endl;
    }
}

void kiir_incidencia(const vector<vector<el>> &matrix)
{    
    int csucsok_szama = matrix.size();
    int elek_szama = matrix[0].size();
    for (int i = 1; i < csucsok_szama; i++)
    {
        for (int j = 1; j < elek_szama; j++)
        {
            if(matrix[i][j].suly.letezik)
            {
                cout << matrix[i][j].suly.suly << " ";
            }
            else
            {
                cout << "-" << " ";
            }
        }
        cout << endl;
    }
}

void kiir_szomszedsagi_lista(const vector<vector<el>> &szomszedsagi_lista)
{
    for (int i = 1; i < szomszedsagi_lista.size(); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < szomszedsagi_lista[i].size(); j++)
        {
            cout << "{" << szomszedsagi_lista[i][j].veg << " (" << szomszedsagi_lista[i][j].suly.suly << ")}, ";
        }
        cout << endl;
    }
}

void kiir_el_lista(const vector<el> &el_lista)
{
    for (int i = 0; i < el_lista.size(); i++)
    {
        cout << el_lista[i].kezdet << " " << el_lista[i].veg << " (" << el_lista[i].suly.suly << ")" << endl;
    }
}

int main()
{
    freopen("graf.in", "r", stdin);
    int n, m;
    cin >> n >> m;

    //Létrehozni egy vektort, majd feltölteni a súlyait 0 / NEM LÉTEZIK-kel.
    cout << endl << "Szomszedsagi Matrix" << endl;
    vector<vector<suly>> szomszedsagi_matrix(n+1, vector<suly>(n+1, {0, false}));
    szomszedsagi_matrix_felepites(szomszedsagi_matrix, m);
    kiir_szomszedsagi(szomszedsagi_matrix);

    cout << endl << "Incidencia Matrix" << endl;
    vector<vector<el>> incidencia(n+1, vector<el>(m+1, {0, 0, {0, false}}));
    alakit_szomszedsagi_incidencia(szomszedsagi_matrix, incidencia);
    kiir_incidencia(incidencia);

    cout << endl << "Szomszedsagi Lista" << endl;
    vector<vector<el>> szomszedsagi_lista(n+1);
    alakit_incidencia_szomszedsagi_lista(incidencia, szomszedsagi_lista);
    kiir_szomszedsagi_lista(szomszedsagi_lista);

    cout << endl << "El Lista" << endl;
    vector<el> el_lista;
    alakit_szomszedsagi_lista_el_lista(szomszedsagi_lista, el_lista);
    kiir_el_lista(el_lista);
    return 0;
}