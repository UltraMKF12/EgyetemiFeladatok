#include <iostream>
using namespace std;

int tesss(int asd)
{
    asd += 10;
    return asd;
}

int main()
{
    int k = 0;

    for (int i = 0; i < 10; i++)
    {
        cout << i << endl;
        k += i;
        k = tesss(k);
    }

    return 0;
}