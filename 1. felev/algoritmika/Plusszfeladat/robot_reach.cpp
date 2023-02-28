#include <iostream>
#include <vector>
using namespace std;

int sum_of_digits(int number)
{
    int sum = 0;
    while(number > 0)
    {
        int digit = number % 10;
        sum += digit;
        number /= 10;
    }

    return sum;
}

void robot_backtracking(int current_x, int current_y, int treshold, vector<vector<int>> &grid, int row, int col, int &count)
{   
    if(grid[current_x][current_y] <= treshold && grid[current_x][current_y] != -1)
    {
        count++;
        grid[current_x][current_y] = -1;

        //LEFT
        if(current_x-1 >= 0)
        {
            robot_backtracking(current_x-1, current_y, treshold, grid, row, col, count);
        }

        //RIGHT
        if(current_x+1 < row)
        {
            robot_backtracking(current_x+1, current_y, treshold, grid, row, col, count);
        }

        //UP
        if(current_y-1 >= 0)
        {
            robot_backtracking(current_x, current_y-1, treshold, grid, row, col, count);
        }

        //DOWN
        if(current_y+1 < col)
        {
            robot_backtracking(current_x, current_y+1, treshold, grid, row, col, count);
        }
    }
}

int main()
{
    int row, col, treshold;
    cin >> row >> col >> treshold;

    vector<vector<int>> grid(row, vector<int>(col, 0));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            grid[i][j] = sum_of_digits(i) + sum_of_digits(j);
        }
    }

    int count = 0;
    robot_backtracking(0, 0, treshold, grid, row, col, count);
    cout << count;
    
    return 0;
}