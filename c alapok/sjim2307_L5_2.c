// Széri József - 514
// sjim2307

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1000

// 1D dynamic memory stuff
char *string_1D_malloc(int length)
{
    char *char_string = (char *) malloc(length * sizeof(char));
    return char_string;
}

char *string_1D_realloc(char *char_string, int length)
{
    char_string = (char *) realloc(char_string, length * sizeof(char));
    return char_string;
}

void string_1D_free(int *char_string)
{
    free(char_string);
}


// 2D dynamic memory stuff
char **string_2D_malloc(int row)
{
    char **char_string = (char **) malloc(row * sizeof(char *));
    for (int i = 0; i < row; i++)
    {
        char_string[i] = string_1D_malloc(1);
    }
    return char_string;
}

char **string_2D_realloc(char **char_string, int row, int new_row)
{
    char_string = (char **) realloc(char_string, new_row * sizeof(int *));
    for (int i = row; i < new_row; i++)
    {
        char_string[i] = string_1D_malloc(1);
    }
    return char_string;
}

void string_2D_free(char **char_string, int length)
{
    for(int i = 0; i < length; i++)
    {
        free(char_string[i]);
    }
    free(char_string);
}



bool parameter_check(int argc, const char *argv[])
{
    //2 parameterrel kell rendelkeznie
    if(argc <= 2 || argc > 3)
    {
        return false;
    }

    for (int i = 1; i < argc; i++)
    {
        int length = strlen(argv[i]);
        for (int j = 0; j < length; j++)
        {
            //Ha barmilyen nem szamjegyet talalunk, akkor helytelen input
            if(!isdigit(argv[i][j]))
            {
                return false;
            }
        }
    }
    
    return true;
}

char **read_input(int position_start, int position_end)
{
    FILE *input = fopen("input.txt", "r");
    if(input == NULL)
    {
        exit(1);
    }

    // Fel veszek egy 1000 hosszsagu stringet beolvasott soroknak. Beolvasas elott nem lehet tudni, hogy milyen egy sor hossza,
    // viszont mivel dinamikusan mindig ujrafoglalni helyet minden karakter utan nem a legjobb megoldas ezert marad a 1000 as sorhossz.
    char s[MAX_INPUT_LENGTH];

    int position_current = 1;
    int size = 0;
    char **char_string = string_2D_malloc(1);
    while(fgets(s, MAX_INPUT_LENGTH, input) != NULL)
    {
        if(position_current >= position_start && position_current <= position_end)
        {
            char_string = string_2D_realloc(char_string, size, size+1);

            int string_length = strlen(s);
            char_string[size] = string_1D_realloc(char_string[size], string_length);
            strcpy(char_string[size], s);

            size++;
        }
        position_current++;

        if(position_current > position_end)
        {
            break;
        }
    }
    
    fclose(input);
    return char_string;
}

int main(int argc, const char *argv[])
{
    //Ha helytelenek a parameterek, akkor ki kell irni, hogy "hiba"
    if(!parameter_check(argc, argv))
    {
        FILE *output = fopen("output.txt", "w");
        fprintf(output, "hiba");
        fclose(output);
        exit(1);
    }

    int position_start = atoi(argv[1]);
    int position_end = atoi(argv[2]);
    int lenght = position_end - position_start;
    char **morse_code_lines = read_input(position_start, position_end);


    string_2D_free(morse_code_lines, lenght);
    return 0;
}