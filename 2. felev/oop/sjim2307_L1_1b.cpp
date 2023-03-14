// Széri József - 514/2
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// 1 2 3 4 5 6 7 8 9
// 1 2 3 6 9 8 7 4 5


// 1 2
// 3 4 = 1 2 4 3

void spiralSorrend(const int* matrix, int n, int* spiral)
{
    int sor = 0;
    int oszlop = 0;

    int jobb = n-1;
    int bal = 0;
    int fel = 1;
    int le = n-1;

    spiral[0] = matrix[0];
    int sprital_elem = 1;

    while(true)
    {
        int valtozas = 0;
        while(oszlop < jobb)
        {
            oszlop++;
            int pozicio = (sor * n) + oszlop;
            spiral[sprital_elem] = matrix[pozicio];
            sprital_elem++;
            valtozas++;
        }
        jobb--;


        while(sor < le)
        {
            sor++;
            int pozicio = (sor * n) + oszlop;
            spiral[sprital_elem] = matrix[pozicio];
            sprital_elem++;
            valtozas++;
        }
        le--;

        while(oszlop > bal)
        {
            oszlop--;
            int pozicio = (sor * n) + oszlop;
            spiral[sprital_elem] = matrix[pozicio];
            sprital_elem++;
            valtozas++;
        }
        bal++;

        while(sor > fel)
        {
            sor--;
            int pozicio = (sor * n) + oszlop;
            spiral[sprital_elem] = matrix[pozicio];
            sprital_elem++;
            valtozas++;
        }
        fel++;

        if(valtozas == 0) break;
    }
}

//1  2 3 4
//5  6 7  8
//9 10 11 12  
//13 14 15 16

int main()
{
    int meret = 4;
    int matrix[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int spiral[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,  0, 0,   0, 0, 0};
    // int matrix[] = {1, 2, 3, 4};
    // int spiral[] = {0, 0, 0, 0};
    spiralSorrend(matrix, meret, spiral);

    for (int i = 0; i < 16; i++)
    {
        cout << spiral[i] << " ";
    }
    
    return 0;
}