// Széri József - 514
// sjim2307

#include <stdio.h>
#include <stdlib.h>


int **matrix_lefoglalas(int sor, int oszlop)
{
    int **matrix = (int **) calloc(sor, sizeof(int *));
    for (int i = 0; i < sor; i++)
    {
        matrix[i] = (int *) calloc(oszlop, sizeof(int));
    }

    return matrix;
}

void matrix_felszabaditas(int **matrix, int sor)
{
    for(int i = 0; i < sor; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int **matrix_ujrafoglalas_nullazas(int **matrix, int sor, int oszlop, int uj_sor, int uj_oszlop)
{
    matrix = (int **) realloc(matrix, uj_sor * sizeof(int *));
    for (int i = 0; i < sor; i++)
    {
        matrix[i] = (int *) realloc(matrix[i], uj_oszlop * sizeof(int));
    }

    //Nullázni az új foglalással az új sorokat
    for (int i = sor; i < uj_sor; i++)
    {
        matrix[i] = (int *) calloc(uj_oszlop, sizeof(int));
    }

    //Nullázni az új adatokat (a meglévő sorokban új oszlopokat)
    for (int i = 0; i < sor; i++)
    {
        for (int j = oszlop; j < uj_oszlop; j++)
        {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

int *matrix_1D_lefoglalas(int sor, int oszlop)
{
    int *matrix = (int*) calloc(sor*oszlop, sizeof(int));
    return matrix;
}

int *matrix_1D_ujrafoglalas_nullazas(int *matrix, int sor, int oszlop, int uj_sor, int uj_oszlop)
{
    matrix = (int *) realloc(matrix, uj_sor*uj_oszlop * sizeof(int));

    //Nullázni az új adatokat (a meglévő sorokban új oszlopokat)
    for (int i = 0; i < sor; i++)
    {
        for (int j = oszlop; j < uj_oszlop; j++)
        {
            matrix[i*ujszor + j] = 0;
        }
    }

    //Nullázni az új foglalással az új sorokat
    for (int i = sor; i < uj_sor; i++)
    {
        matrix[i] = (int *) calloc(uj_oszlop, sizeof(int));
    }


    return matrix;
}

void matrix_kiiras(int **matrix, int sor, int oszlop)
{
    for (int i = 0; i < sor; i++)
    {
        for (int j = 0; j < oszlop; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int **network_beolvasas(int *n)
{   
    int temp_n = *n;
    int elozo_n = temp_n;
    int **matrix = matrix_lefoglalas(temp_n, temp_n);
    int kiindulasi_pont;
    int veg_pont;
    int suly;

    FILE *network_text;
    network_text = fopen("network.txt", "r");
    while(fscanf(network_text, "%d %d %d", &kiindulasi_pont, &veg_pont, &suly) == 3)
    {
        if(kiindulasi_pont > temp_n || veg_pont > temp_n)
        {
            elozo_n = temp_n;
            temp_n = (kiindulasi_pont >= veg_pont) ? kiindulasi_pont+1 : veg_pont+1;
            matrix = matrix_ujrafoglalas_nullazas(matrix, elozo_n, elozo_n, temp_n, temp_n);
        }

        matrix[kiindulasi_pont][veg_pont] = suly;
        matrix[veg_pont][kiindulasi_pont] = suly;
    }
    

    fclose(network_text);
    *n = temp_n;
    return matrix;
}

int main()
{
    int n = 1;
    int **matrix = network_beolvasas(&n);

    matrix_kiiras(matrix, n, n);
    matrix_felszabaditas(matrix, n);
    return 0;
}