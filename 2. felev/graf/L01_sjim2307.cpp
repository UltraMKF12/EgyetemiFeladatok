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

void alakit_szomszedsagi_incidencia(const vector<vector<suly>> &szomszedsagi, vector<vector<suly>> &incidencia)
{

}




void kiir_szomszedsagi_incidencia(const vector<vector<suly>> &matrix)
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

int main()
{
    freopen("graf.in", "r", stdin);
    int n, m;
    cin >> n >> m;

    //Létrehozni egy vektort, majd feltölteni a súlyait 0 / NEM LÉTEZIK-kel.
    vector<vector<suly>> szomszedsagi(n+1, vector<suly>(n+1, {0, false}));vector<vector<suly>> szomszedsagi(n+1, vector<suly>(n+1, {0, false}));
    szomszedsagi_matrix_felepites(szomszedsagi, m);
    kiir_szomszedsagi_incidencia(szomszedsagi);

    vector<vector<suly>> incidencia(n+1, vector<suly>(m+1, {0, false}));
    alakit_szomszedsagi_incidencia(szomszedsagi, incidencia)
    kiir_szomszedsagi_incidencia(incidencia);

    return 0;
}