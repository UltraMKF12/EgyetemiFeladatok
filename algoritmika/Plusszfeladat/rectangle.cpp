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

    int squareCount = 0;
    vector<int> x_hosszok(w+1, 0);
    vector<int> y_hosszok(h+1, 0);

    vector<int> x_hosszok_indexek;
    vector<int> y_hosszok_indexek;

    for (int x1 = 0; x1 <= countX+1; x1++)
    {
        for (int x2 = x1+1; x2 <= countX+1; x2++)
        {
            int x_hossz = arr_x[x2] - arr_x[x1];
            if(x_hosszok[x_hossz] == 0)
            {
                x_hosszok_indexek.push_back(x_hossz);
            }  
            x_hosszok[x_hossz]++;
        }
    }
    
    for (int y1 = 0; y1 <= countY+1; y1++)
    {
        for (int y2 = y1+1; y2 <= countY+1; y2++)
        {
            int y_hossz = arr_y[y2] - arr_y[y1];
            if(y_hosszok[y_hossz] == 0)
            {
                y_hosszok_indexek.push_back(y_hossz);
            }
            y_hosszok[y_hossz]++;
        }   
    }

    for (int i = 0; i < x_hosszok_indexek.size(); i++)
    {
        if(y_hosszok[x_hosszok_indexek[i]] > 0 && x_hosszok_indexek[i] <= y_hosszok.size())
        {
            squareCount += (x_hosszok[x_hosszok_indexek[i]] * y_hosszok[x_hosszok_indexek[i]]);
            // cout << x_hosszok_indexek[i] << "= " << x_hosszok[x_hosszok_indexek[i]] << " * " << y_hosszok[x_hosszok_indexek[i]] << endl;
        }
    }
    
    cout << squareCount;
    return 0;
}