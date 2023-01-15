// Széri József - 514
// sjim2307

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1001

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

            //Ki kell törölni a new linet a végéről
            if(s[string_length-1] == '\n')
            {
                s[string_length-1] = '\0';
                string_length--;
            }

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

char convert_table(char *morse)
{
    if(strcmp(morse, ".-") == 0)
    {
        return 'a';
    }

    if(strcmp(morse, "-...") == 0)
    {
        return 'b';
    }

    if(strcmp(morse, "-.-.") == 0)
    {
        return 'c';
    }

    if(strcmp(morse, "-..") == 0)
    {
        return 'd';
    }

    if(strcmp(morse, ".") == 0)
    {
        return 'e';
    }

    if(strcmp(morse, "..-.") == 0)
    {
        return 'f';
    }

    if(strcmp(morse, "--.") == 0)
    {
        return 'g';
    }

    if(strcmp(morse, "....") == 0)
    {
        return 'h';
    }

    if(strcmp(morse, "..") == 0)
    {
        return 'i';
    }

    if(strcmp(morse, ".---") == 0)
    {
        return 'j';
    }

    if(strcmp(morse, "-.-") == 0)
    {
        return 'k';
    }

    if(strcmp(morse, ".-..") == 0)
    {
        return 'l';
    }

    if(strcmp(morse, "--") == 0)
    {
        return 'm';
    }

    if(strcmp(morse, "-.") == 0)
    {
        return 'n';
    }

    if(strcmp(morse, "---") == 0)
    {
        return 'o';
    }

    if(strcmp(morse, ".--.") == 0)
    {
        return 'p';
    }

    if(strcmp(morse, "--.-") == 0)
    {
        return 'q';
    }

    if(strcmp(morse, ".-.") == 0)
    {
        return 'r';
    }

    if(strcmp(morse, "...") == 0)
    {
        return 's';
    }

    if(strcmp(morse, "-") == 0)
    {
        return 't';
    }

    if(strcmp(morse, "..-") == 0)
    {
        return 'u';
    }

    if(strcmp(morse, "...-") == 0)
    {
        return 'v';
    }

    if(strcmp(morse, ".--") == 0)
    {
        return 'w';
    }

    if(strcmp(morse, "-..-") == 0)
    {
        return 'x';
    }

    if(strcmp(morse, "-.--") == 0)
    {
        return 'y';
    }

    if(strcmp(morse, "--..") == 0)
    {
        return 'z';
    }



    if(strcmp(morse, "-----") == 0)
    {
        return '0';
    }
    if(strcmp(morse, ".----") == 0)
    {
        return '1';
    }
    if(strcmp(morse, "..---") == 0)
    {
        return '2';
    }
    if(strcmp(morse, "...--") == 0)
    {
        return '3';
    }
    if(strcmp(morse, "....-") == 0)
    {
        return '4';
    }
    if(strcmp(morse, ".....") == 0)
    {
        return '5';
    }
    if(strcmp(morse, "-....") == 0)
    {
        return '6';
    }
    if(strcmp(morse, "--....") == 0)
    {
        return '7';
    }
    if(strcmp(morse, "---..") == 0)
    {
        return '8';
    }
    if(strcmp(morse, "----.") == 0)
    {
        return '9';
    }



    if(strcmp(morse, ".-.-.-") == 0)
    {
        return '.';
    }
    if(strcmp(morse, "--..--") == 0)
    {
        return ',';
    }
    if(strcmp(morse, "..--..") == 0)
    {
        return '?';
    }
    if(strcmp(morse, ".----.") == 0)
    {
        return '\'';
    }
    if(strcmp(morse, "-.-.--") == 0)
    {
        return '!';
    }
    if(strcmp(morse, "-..-.") == 0)
    {
        return '/';
    }
    if(strcmp(morse, "-.--.") == 0)
    {
        return '(';
    }
    if(strcmp(morse, "-.--.-") == 0)
    {
        return ')';
    }
    if(strcmp(morse, ".-...") == 0)
    {
        return '&';
    }
    if(strcmp(morse, "---...") == 0)
    {
        return ':';
    }
    if(strcmp(morse, "-.-.-.") == 0)
    {
        return ';';
    }
    if(strcmp(morse, "-...-") == 0)
    {
        return '=';
    }
    if(strcmp(morse, ".-.-.") == 0)
    {
        return '+';
    }
    if(strcmp(morse, "-....-") == 0)
    {
        return '-';
    }
    if(strcmp(morse, "..--.-") == 0)
    {
        return '_';
    }
    if(strcmp(morse, ".-..-.") == 0)
    {
        return '"';
    }
    if(strcmp(morse, "...-..-") == 0)
    {
        return '$';
    }
    if(strcmp(morse, ".--.-.") == 0)
    {
        return '@';
    }

    return ' ';
}

void convert_morse(char **morse_code_lines, int length)
{
    for (int i = 0; i <= length; i++)
    {
        int letters_decoded = 0;
        while(letters_decoded < strlen(morse_code_lines[i]))
        {
            char morse[10]; // Nem lehet ettol hosszab morse kod
            int morse_count = 0;
            int position = letters_decoded;
            while(morse_code_lines[i][position] != ' ' && morse_code_lines[i][position] != '\0')
            {
                morse[morse_count] = morse_code_lines[i][position];
                morse_count++;
                position++;
            }

            if(morse_count > 0)
            {
                //Behelyettesíteni a karaktert
                morse[morse_count] = '\0';
                char character = convert_table(morse);
                morse_code_lines[i][letters_decoded] = character;

                letters_decoded++;

                //Memmove-al eltolni az egeszet
                if(morse_code_lines[i][position] == '\0')
                {
                    memmove(morse_code_lines[i] + letters_decoded, morse_code_lines[i] + position, 1);
                    morse_code_lines[i] = string_1D_realloc(morse_code_lines[i], strlen(morse_code_lines[i]) + 1 - (position - letters_decoded + 1));
                }
                else
                {
                    memmove(morse_code_lines[i] + letters_decoded, morse_code_lines[i] + position+1, (strlen(morse_code_lines[i]) - position));
                    morse_code_lines[i] = string_1D_realloc(morse_code_lines[i], strlen(morse_code_lines[i]) + 1 - (position - letters_decoded));
                }
                // printf("%s\n", morse_code_lines[i]);
            }
            else
            {
                //Különleges eset, Space
                letters_decoded++;
                memmove(morse_code_lines[i] + letters_decoded, morse_code_lines[i] + letters_decoded+5, (strlen(morse_code_lines[i]) - (letters_decoded+4)));
                morse_code_lines[i] = string_1D_realloc(morse_code_lines[i], strlen(morse_code_lines[i]) - 5);
                // printf("%s\n", morse_code_lines[i]);
            }
        }
    }
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
    int length = position_end - position_start;
    char **morse_code_lines = read_input(position_start, position_end);

    // int length = 1;
    // char **morse_code_lines = string_2D_malloc(2);
    // morse_code_lines[0] = string_1D_realloc(morse_code_lines[0], strlen("-- --- .-. ... .       -.-. --- -.. ."));
    // strcpy(morse_code_lines[0], "-- --- .-. ... .       -.-. --- -.. .");

    convert_morse(morse_code_lines, length);

    FILE *output = fopen("output.txt", "w");
    for (int i = 0; i <= length; i++)
    {
        fprintf(output, "%s\n", morse_code_lines[i]);
    }
    fclose(output);

    string_2D_free(morse_code_lines, length);
    return 0;
}