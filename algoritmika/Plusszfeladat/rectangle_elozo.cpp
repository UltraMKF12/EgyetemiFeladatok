#include <iostream>
#include <vector>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    int w, h, countX, countY;
    cin >> w >> h >> countX >> countY;

    vector<int> arr_x(countX+2);
    arr_x[0] = 0;
    arr_x[countX+1] = w;
    for (int i = 1; i <= countX; i++)
    {
        cin >> arr_x[i];
    }
    
    vector<int> arr_y(countY+2);
    arr_y[0] = 0;
    arr_y[countY+1] = h;
    for (int i = 1; i <= countY; i++)
    {
        cin >> arr_y[i];
    }

    vector<int> x_hosszok;
    vector<int> y_hosszok;

    for (int x1 = 0; x1 <= countX+1; x1++)
    {
        for (int x2 = x1+1; x2 <= countX+1; x2++)
        {
            int x_hossz = arr_x[x2] - arr_x[x1];
            x_hosszok.push_back(x_hossz);            
        }
    }
    
    for (int y1 = 0; y1 <= countY+1; y1++)
    {
        for (int y2 = y1+1; y2 <= countY+1; y2++)
        {
            int y_hossz = arr_y[y2] - arr_y[y1];
            y_hosszok.push_back(y_hossz);
        }   
    }


    int squareCount = 0;
    for (int i = 0; i < x_hosszok.size(); i++)
    {
        for (int j = 0; j < y_hosszok.size(); j++)
        {
            if(x_hosszok[i] == y_hosszok[j])
            {
                squareCount++;
            }
        }
        
    }
    cout << squareCount;
    return 0;
}