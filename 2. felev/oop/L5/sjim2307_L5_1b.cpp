// Széri József - 514/2
#include <iostream>

template<typename T>
void rendez(T *pointer, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if(pointer[i] > pointer[j])
            {
                T temp;
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    }
}

int main()
{
    int tomb[] = {1, 6, 3, 1, 6};
    float tomb2[] = {4.2, 2.2, 5.12, 1};
    rendez(tomb, 5);
    rendez(tomb2, 4);
    return 0;
}