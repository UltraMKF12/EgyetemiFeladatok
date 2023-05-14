//Széri József - 514/2 - sjim2307
#include <iostream>
#include <vector>
using namespace std;


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


int main()
{

    return 0;
}