// Széri József - 514
// sjim2307

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sjim2307_mode.h"

#if MODE == 1
    #include "sjim2307_normal.h"
#elif MODE == 2
    #include "sjim2307_inline.h"
#elif MODE == 3
    #include "sjim2307_macro.h"
#endif

int lucas(int n)
{
    if(n == 0)
    {
        return 2;
    }
    if(n == 1)
    {
        return 1;
    }

    return add(lucas(n-1), lucas(n-2));
}

int main()
{
    int n;
    FILE *input = fopen("input.txt", "r");
    fscanf(input, "%d", &n);
    int result = lucas(n);

    FILE *output = fopen("output.txt", "a");
    fprintf(output, "lucas(%d) = %d\n", n, result);
    fprintf(output, STR);
    fprintf(output, "\n");
    double average = 0;

    for (int i = 1; i <= 5; i++)
    {
        clock_t start, end;
        start = clock();
        lucas(n);
        end = clock();
        double time = (double) (end - start) / CLOCKS_PER_SEC;
        average += time;
        fprintf(output, "#%d run: %f\n", i, time);
    }
    average /= 5;

    fprintf(output, "average: %f\n\n", average);

    fclose(input);
    fclose(output);
}