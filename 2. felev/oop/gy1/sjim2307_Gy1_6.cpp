// Széri József - 514/2
#include <iostream>
using namespace std;

inline int minimalis(int x, int y)
{
    return (x < y) ? x : y;
}

inline int maximalis(int x, int y)
{
    return (x > y) ? x : y;
}

int main()
{
    int x = 6;
    int y = 7;
    cout << minimalis(x, y) << endl;
    cout << maximalis(x, y) << endl;
    return 0;
}