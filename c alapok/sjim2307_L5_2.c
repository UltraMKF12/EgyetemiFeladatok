// Széri József - 514
// sjim2307

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, const char *argv[])
{
    FILE *input = fopen("input.txt", "r");
    fclose(input);
    FILE *output = fopen("output.txt", "w");
    fclose(output);
    return 0;
}