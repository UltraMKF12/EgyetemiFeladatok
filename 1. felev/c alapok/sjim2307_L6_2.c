// Széri József - 514
// sjim2307

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int x;
    int y;
    bool el;

    int el_uj;
} cella;


bool parameter_check(int argc, const char *argv[])
{
    //3 parameterrel kell rendelkeznie
    if(argc != 4)
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

// 2D dynamic memory stuff
cella **struct_2D_malloc(int sor, int oszlop)
{
    cella **struct_matrix = (cella **) malloc(sor * sizeof(cella *));
    for (int i = 0; i < sor; i++)
    {
        struct_matrix[i] = (cella *) malloc(oszlop * sizeof(cella));
    }

    for (int i = 0; i < sor; i++)
    {
        for (int j = 0; j < oszlop; j++)
        {
            cella temp;
            temp.x = i;
            temp.y = j;
            temp.el = false;
            struct_matrix[i][j] = temp;
        }
        
    }
    
    return struct_matrix;
}

void struct_2D_free(cella **struct_matrix, int sor)
{
    for(int i = 0; i < sor; i++)
    {
        free(struct_matrix[i]);
    }
    free(struct_matrix);
}


void read_input(cella **struct_matrix)
{
    FILE *input = fopen("input.txt", "r");
    if(input == NULL)
    {
        exit(1);
    }

    int number1, number2;
    while(fscanf(input, "%d %d", &number1, &number2) == 2)
    {
        
        struct_matrix[number1][number2].el = true;
    }
}

void print_jatekter(cella **struct_matrix, int sor, int oszlop)
{
    for (int i = 0; i <= sor; i++)
    {
        for (int j = 0; j <= oszlop; j++)
        {
            if(struct_matrix[i][j].el == true)
            {
                printf("%c", 219);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int szomszed_szamlalas(cella **jatekter, int sor, int oszlop, int x, int y)
{
    int szomszedok = 0;
    //Bal felülről clockwise
    int iranyok_x[8] = {-1,  0,  1,  1,  1,  0, -1, -1};
    int iranyok_y[8] = {-1, -1, -1,  0,  1,  1,  1,  0};
    for (int i = 0; i < 8; i++)
    {
        int uj_x = x + iranyok_x[i];
        int uj_y = y + iranyok_y[i];

        if(uj_x < 0 || uj_y < 0 || uj_x >= sor || uj_y >= oszlop)
        {
            continue;
        }

        if(jatekter[uj_x][uj_y].el == true)
        {
            // printf("(%d ,%d) %d, %d\n", x, y, uj_x, uj_y);
            szomszedok++;
        }
    }

    return szomszedok;
}

void szimulalas(cella **jatekter, int sor, int oszlop)
{
    //Kör szimulálása.
    for (int i = 0; i <= sor; i++)
    {
        for (int j = 0; j <= oszlop; j++)
        {
            int szomszed_szam = szomszed_szamlalas(jatekter, sor, oszlop, i, j);
            // printf("//x=%d y=%d --- %d\n", i, j, szomszed_szam);
            if(jatekter[i][j].el == true)
            {
                if(szomszed_szam < 2 || szomszed_szam > 3)
                {
                    jatekter[i][j].el_uj = false;
                }
                else
                {
                    jatekter[i][j].el_uj = true;
                }
            }
            else
            {
                if(szomszed_szam == 3)
                {
                    jatekter[i][j].el_uj = true;
                }
                else
                {
                    jatekter[i][j].el_uj = false;
                }
            }
        }
    }
    
    //új Élők betevése
    for (int i = 0; i < sor; i++)
    {
        for (int j = 0; j < oszlop; j++)
        {
            jatekter[i][j].el = jatekter[i][j].el_uj;
        }
        
    }
    
}

int main(int argc, const char *argv[])
{
    //Ha helytelenek a parameterek, akkor ki kell irni, hogy "hiba"
    if(!parameter_check(argc, argv))
    {
        printf("hiba");
        exit(1);
    }

    int sorok = atoi(argv[1]);
    int oszlopok = atoi(argv[2]);
    int iteraciok = atoi(argv[3]);

    cella **jatekter = struct_2D_malloc(sorok+1, oszlopok+1);
    read_input(jatekter);

    for (int i = 0; i <= iteraciok; i++)
    {
        printf("Jelenlegi iteracio = %d\n", i);
        print_jatekter(jatekter, sorok, oszlopok);
        szimulalas(jatekter, sorok, oszlopok);
    }
    

    struct_2D_free(jatekter, sorok);
    return 0;
}