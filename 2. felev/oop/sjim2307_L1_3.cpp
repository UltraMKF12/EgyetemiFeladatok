// Széri József - 514/2
#include <iostream>
using namespace std;

int a(int b)
{
    cout << "b=" << b << endl;
}

int a(int b, int c=0)
{
    cout << "b=" << b  << ", c=" << c << endl;
}

int main()
{
    a(12);
    a(21, 32);
    return 0;
}