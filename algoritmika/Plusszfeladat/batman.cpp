#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

void next_direction(string text, int &x, int &y)
{
    if (text =="U")
    {
        x = 0;
        y = -1;
        return;
    }
    if (text =="UR")
    {
        x = 1;
        y = -1;
        return;
    }
    if (text =="R")
    {
        x = 1;
        y = 0;
        return;
    }
    if (text =="DR")
    {
        x = 1;
        y = 1;
        return;
    }
    if (text =="D")
    {
        x = 0;
        y = 1;
        return;
    }
    if (text =="DL")
    {
        x = -1;
        y = 1;
        return;
    }
    if (text =="L")
    {
        x = -1;
        y = 0;
        return;
    }
    if (text =="UL")
    {
        x = -1;
        y = -1;
        return;
    }
}

int main()
{
    int w; // width of the building.
    int h; // height of the building.
    cin >> w >> h; cin.ignore();
    int n; // maximum number of turns before game over.
    cin >> n; cin.ignore();
    int x0;
    int y0;
    cin >> x0 >> y0; cin.ignore();

    int y_max = h;
    int y_min = 0;

    int x_max = w;
    int x_min = 0;

    int dir_x = -1, dir_y = -1;
    int next_x; int next_y = 0;
    int current_x = x0; 
    int current_y = y0;
    // game loop
    while (1) {
        string bomb_dir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bomb_dir; cin.ignore();
        next_direction(bomb_dir, dir_x, dir_y);
        //X
        if(dir_x < 0)
        {
            x_max = current_x-1;
        }
        else if(dir_x > 0)
        {
            x_min = current_x+1;
        }
        else if (dir_x == 0)
        {
            x_min = current_x;
            x_max = current_x;
        }

        // next_x = (dir_x < 0) ? current_x - (current_x - x_min)/2 : current_x + (x_max - current_x)/2;
        next_x = (x_max + x_min) / 2;

        //Y
        if(dir_y < 0)
        {
            y_max = current_y-1;
        }
        else if(dir_y > 0)
        {
            y_min = current_y+1;
        }
        else if (dir_y == 0)
        {
            y_min = current_y;
            y_max = current_y;
        }

        // next_y = (dir_y < 0) ? current_y - (current_y - y_min)/2 : current_y + (y_max - current_y)/2;
        next_y = (y_max + y_min) / 2;
        // the location of the next window Batman should jump to.
        current_x = next_x;
        current_y = next_y;
        cout << next_x << " " << next_y << endl;
    }
}