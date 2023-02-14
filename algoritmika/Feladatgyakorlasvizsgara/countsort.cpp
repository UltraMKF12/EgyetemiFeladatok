#include <iostream>
#include <vector>
using namespace std;

void print_tomb(const vector<int> &t)
{
    for (int i = 0; i < t.size(); i++)
    {
        cout << t[i] << " ";
    }

    cout << endl;
}

void count_sort(vector<int> &t)
{

}

int main()
{
    vector<int> tomb = {5, 2, 1, 6, 2};
    print_tomb(tomb);
    count_sort(tomb);
    print_tomb(tomb);

    return 0;
}