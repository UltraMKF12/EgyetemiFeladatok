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
    int m = feloszt2(tomb, bal, jobb);
    quicksort(tomb, bal, m-1);
    quicksort(tomb, m+1, jobb);

}


int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high]; // pivot
    int i
        = (low
           - 1); // Index of smaller element and indicates
                 // the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
  
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
  
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    // freopen("bemenet.txt", "r", stdin);
    // freopen("kimenet.txt", "w", stdout);

    vector<int> tomb = {8, 7, 6, 10, 4, 11, 2, 5, 9};
    quickSort(tomb, 0, tomb.size()-1);


    return 0;
}