//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
using namespace std;


void szomszedsagi_matrix_felepites(vector<vector<int>> &matrix, int m)
{   
    int pont1, pont2, suly;
    for(int i = 0; i < m; i++)
    {
        cin >> pont1 >> pont2 >> suly;
        matrix[pont1][pont2] = suly;
        matrix[pont1][pont1] = 0;
    }
}

void roy_floyd_warshall(vector<vector<int>> &matrix, int n, vector<vector<int>>& elozo_csomopont)
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if(matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX &&
                   matrix[i][j] > matrix[i][k] + matrix[k][j])
                {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    elozo_csomopont[i][j] = elozo_csomopont[k][j];
                }
            }
        }
    }
}

void ut_kiir(vector<vector<int>>& elozo_csomopont, int csucs1, int csucs2)
{
    cout << csucs2 << ", ";
    int kovetkezo = elozo_csomopont[csucs1][csucs2];
    while(kovetkezo != 0 && kovetkezo != csucs1)
    {
        cout << kovetkezo << ", ";
        kovetkezo = elozo_csomopont[csucs1][kovetkezo];
    }
    if(kovetkezo != 0)
    {
        cout << csucs1;
    }
}

void kiir(vector<vector<int>>& elozo_csomopont, int csucs1, int csucs2)
{    
    int csucsok_szama = elozo_csomopont.size();
    int elek_szama = elozo_csomopont[0].size();
    for (int i = 1; i < csucsok_szama; i++)
    {
        for (int j = 1; j < elek_szama; j++)
        {   
            if(elozo_csomopont[i][j] == INT_MAX)
            {
                cout << ". ";
            }
            else
            {
                cout << elozo_csomopont[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
    cout << csucs1 << "-" << csucs2 << ": ";
    ut_kiir(elozo_csomopont, csucs1, csucs2);
}

int main()
{
    freopen("graf.in", "r", stdin);
    int n, m, csucs1, csucs2;
    cin >> n >> m >> csucs1 >> csucs2;

    vector<vector<int>> szomszedsagi_matrix(n+1, vector<int>(n+1, INT_MAX));
    szomszedsagi_matrix_felepites(szomszedsagi_matrix, m);

    vector<vector<int>> elozo_csomopont(n+1, vector<int>(n+1, INT_MAX));
    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= n; j++)
        {
            if(szomszedsagi_matrix[i][j] != INT_MAX && i != j)
            {
                elozo_csomopont[i][j] = i;
            }
            else
            {
                elozo_csomopont[i][j] = 0;
            }
        }
    }

    roy_floyd_warshall(szomszedsagi_matrix, n, elozo_csomopont);
    kiir(elozo_csomopont, csucs1, csucs2);

    return 0;
}