// Széri József - 514/2
#include <iostream>
#define minimalis(a, b) (((a) < (b)) ? (a) : (b))
#define maximalis(a, b) (((a) > (b)) ? (a) : (b))
using namespace std;

int main()
{
    int x = 6;
    int y = 7;
    cout << minimalis(x, y) << endl;
    cout << maximalis(x, y) << endl;
    return 0;
}