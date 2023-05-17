//Széri József - 514
#include <iostream>
#include <vector>
#include <limits.h>
#include <fstream>
#include <math.h>
using namespace std;



vector<vector<int>> graf_beolvasas()
{
    ifstream input("tronok_harca.txt");
    int n;
    input >> n;
    vector<vector<int>> szomszedsagi_matrix(n+1, vector<int>(n+1, INT_MAX));

    int elso, masodik, ertek;
    while(input >> elso >> masodik >> ertek)
    {
        szomszedsagi_matrix[elso][masodik] = ertek;
        szomszedsagi_matrix[masodik][elso] = ertek;
    }
    
    for (int i = 0; i < szomszedsagi_matrix.size(); i++)
    {
        szomszedsagi_matrix[i][i] = 0;
    }

    input.close();
    return szomszedsagi_matrix;
}

void szomszedsagi_kiir(const vector<vector<int>>& szomszedsagi_matrix)
{
    for (int i = 1; i < szomszedsagi_matrix.size(); i++)
    {
        for (int j = 1; j < szomszedsagi_matrix.size(); j++)
        {
            if(szomszedsagi_matrix[i][j] == INT_MAX)
            {
                cout << ". ";
            }
            else
            {
                cout << szomszedsagi_matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}


void atlag_barat(const vector<vector<int>>& szomszedsagi_matrix)
{
    //Ki kell szamloni az atlagot.
    // fokszam = barat szam

    double atlag = 0;
    vector<int> fokszamok(szomszedsagi_matrix.size(), 0);
    for (int i = 1; i < szomszedsagi_matrix.size(); i++)
    {
        for (int j = 1; j < szomszedsagi_matrix.size(); j++)
        {
            if(szomszedsagi_matrix[i][j] != INT_MAX && i != j)
            {
                fokszamok[i]++;
            }
        }
        atlag += fokszamok[i];
    }

    atlag = atlag / (szomszedsagi_matrix.size()-1);

    cout << "Baratszamok atlaga = " << atlag << endl;
    int kerekitett_atlag = round(atlag);
    cout << "Atlaghoz legkozelebb eso baratszam(ok): ";
    for (int i = 1; i < fokszamok.size(); i++)
    {
        if(fokszamok[i] == kerekitett_atlag)
        {
            cout << i << " ";
        }
    }

    cout << endl;
}


void cpm(vector<vector<int>>& szomszedsagi_matrix, vector<vector<int>>& utvonal_matrix)
{
    for (int k = 1; k < szomszedsagi_matrix.size(); k++)
    {
        for (int i = 1; i < szomszedsagi_matrix.size(); i++)
        {
            for (int j = 1; j < szomszedsagi_matrix.size(); j++)
            {
                if(szomszedsagi_matrix[i][k] != INT_MAX && szomszedsagi_matrix[k][j] != INT_MAX &&
                   szomszedsagi_matrix[i][j] > szomszedsagi_matrix[i][k] + szomszedsagi_matrix[k][j])
                {
                    szomszedsagi_matrix[i][j] = szomszedsagi_matrix[i][k] + szomszedsagi_matrix[k][j];
                    utvonal_matrix[i][j] = utvonal_matrix[k][j];
                }
            }
        }
    }
}

void cpm_kiir(const vector<vector<int>>& szomszedsagi_matrix, const vector<vector<int>>& utvonal_matrix, int kezd)
{
    for (int veg = 1; veg < utvonal_matrix.size(); veg++)
    {
        if(veg == kezd) continue;

        cout << "---[" << veg << "]---" << endl;
        cout << "Legrovidebb ut hossza: ";
        if(szomszedsagi_matrix[kezd][veg] == INT_MAX)
        {
            cout << "NEM LETEZIK" << endl << "Legrovidebb ut csomopontok: NEM LETEZIK" << endl << endl;
            continue;;
        }

        cout << szomszedsagi_matrix[kezd][veg] << endl;

        cout << "Legrovidebb ut csomopontok: ";
        cout << veg << " ";
        int kovetkezo = utvonal_matrix[kezd][veg];
        while(kovetkezo != 0 && kezd != veg)
        {
            cout << kovetkezo << " ";
            kovetkezo = utvonal_matrix[kezd][kovetkezo];
        }
        if(kovetkezo != 0)
        {
            cout << kezd;
        }
        cout << endl << endl;
    }
}

bool osszefuggo_e(const vector<vector<int>>& utvonal_matrix)
{
    for (int i = 1; i < utvonal_matrix.size(); i++)
    {
        for (int j = 1; j < utvonal_matrix.size(); j++)
        {
            if(utvonal_matrix[i][j] == 0 && i != j)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    cout << endl << "---------------[A]---------------" << endl;
    vector<vector<int>> szomszedsagi_matrix = graf_beolvasas();
    szomszedsagi_kiir(szomszedsagi_matrix);


    cout << endl << "---------------[D]---------------" << endl;
    atlag_barat(szomszedsagi_matrix);


    cout << endl << "---------------[E]---------------" << endl;
    vector<vector<int>> utvonal_matrix(szomszedsagi_matrix.size(), vector<int>(szomszedsagi_matrix.size(), INT_MAX));
    for (int i = 1; i < utvonal_matrix.size(); i++)
    {
        for (int j = 0; j < utvonal_matrix.size(); j++)
        {
            if(szomszedsagi_matrix[i][j] != INT_MAX && i != j)
            {
                utvonal_matrix[i][j] = i;
            }
            else
            {
                utvonal_matrix[i][j] = 0;
            }
        }
    }
    cpm(szomszedsagi_matrix, utvonal_matrix);
    int szemely;
    cout << "Szemely >> ";
    cin >> szemely;
    cout << endl;
    cpm_kiir(szomszedsagi_matrix, utvonal_matrix, szemely);

    cout << endl << "---------------[C]---------------" << endl;
    cout << "A graf: " << (osszefuggo_e(utvonal_matrix) ? "Osszefuggo" : "NEM Osszefuggo") << endl;
    

    return 0;
}