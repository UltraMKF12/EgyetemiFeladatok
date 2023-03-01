// Széri József - 514/2
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int& huzas(int &fekete, int &feher)
{
    return (rand() % 2) ? fekete : feher;
}

int main()
{
    srand(time(0));
    int n;
    cin >> n;
    int feher = 0;
    int fekete = 0;
    for (int i = 0; i < n; i++)
    {
        huzas(fekete, feher)++;
    }

    cout << "feher: " << feher << ", fekete: " << fekete;
    
    return 0;
}