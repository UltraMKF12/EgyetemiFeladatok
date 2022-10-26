#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isTreasure(int index_x, int index_y, vector<vector<int>> &treasure_map, int index_x_max, int index_y_max)
{
    bool treasure = true;
    if(treasure_map[index_x][index_y]) // If value is one, then it's not treasure location
    {
        return false;
    }

    //Fent
    if(index_y != 0 && treasure_map[index_x][index_y-1] == 0) return false;

    //Lent
    if(index_y != index_y_max && treasure_map[index_x][index_y+1] == 0) return false;

    //Balra
    if(index_x != 0 && treasure_map[index_x-1][index_y] == 0) return false;

    //Jobbra
    if(index_x != index_x_max && treasure_map[index_x+1][index_y] == 0) return false;


    //Bal fent
    if(index_y != 0 && index_x != 0 && treasure_map[index_x-1][index_y-1] == 0) return false;

    //Bal lent
    if(index_y != index_y_max && index_x != 0 && treasure_map[index_x-1][index_y+1] == 0) return false;

    //Jobb lent
    if(index_y != index_y_max && index_x != index_x_max && treasure_map[index_x+1][index_y+1] == 0) return false;

    //Jobb fent
    if(index_y != 0 && index_x != index_x_max && treasure_map[index_x+1][index_y-1] == 0) return false;

    return true;
}

int main()
{
    freopen("bemenet.txt", "r", stdin);

    int width, height;
    cin >> width >> height;
    vector<vector<int>> treasure_map(width, vector<int>(height));
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            cin >> treasure_map[i][j];
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if(isTreasure(i, j, treasure_map, width-1, height-1))
            {
                cout << "Treasure location: " << i << " " << j << endl;
                break;
            }
        }
    }

    return 0;
}