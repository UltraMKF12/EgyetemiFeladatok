#include <iostream>
#include <vector>

using namespace std;

int div_max(int left, int right, vector<int> &list)
{
    if (left == right) {
        return list[left];
    }

    int mid = (left + right) / 2;

    int leftMax = div_max(left, mid, list);
    int rightMax = div_max(mid + 1, right, list);

    return max(leftMax, rightMax);
}

int main()
{
    vector<int> test = {1,2,3,4, 8 ,5,6,7, 12};
    cout << div_max(0, test.size()-1, test);
}