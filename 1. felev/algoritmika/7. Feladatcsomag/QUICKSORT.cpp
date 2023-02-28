// Széri József - sjim2307
//Quickselect
/*
*/

#include <iostream>
#include <vector>
using namespace std;

int feloszt(vector<int> &tomb, int bal, int jobb)
{
    int pivot = tomb[bal];
    int i = bal - 1;
    int j = jobb + 1;

    do
    {
        do
        {
            j--;
        } while (tomb[j] <= pivot);
        
        do
        {
            i++;
        } while (tomb[i] >= pivot);
        
        if(i < j)
        {
            swap(tomb[i], tomb[j]);
        }
    } while (i >= j);

    return j;
}

int feloszt2(vector<int> &tomb, int bal, int jobb)
{
    int pivot = tomb[jobb];
    int i = bal - 1;
    
    for (int j = bal; j <= jobb - 1; j++)
    {
        if(tomb[j] < pivot)
        {
            i++;
            swap(tomb[i], tomb[j]);
        }
    }

    swap(tomb[i+1], tomb[jobb]);
    return i+1;
    
}

void quicksort(vector<int> &tomb, int bal, int jobb)
{
    if(bal < jobb)
    {
        int m = feloszt2(tomb, bal, jobb);
        quicksort(tomb, bal, m-1);
        quicksort(tomb, m+1, jobb);
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    vector<int> tomb = {8, 7, 6, 10, 4, 11, 2, 5, 9};
    quicksort(tomb, 0, tomb.size()-1);


    return 0;
}