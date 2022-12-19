// Széri József - 514
// sjim2307

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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


int *matrix_1D_lefoglalas(int oszlop)
{
    int *matrix = (int *) calloc(oszlop, sizeof(int));
}

int *matrix_1D_ujrafoglalas_nullazas(int *matrix, int oszlop, int uj_oszlop)
{
    matrix = (int*) realloc(matrix, uj_oszlop * sizeof(int));
    for (int i = oszlop; i < uj_oszlop; i++)
    {
        matrix[i] = 0;
    }

    return matrix;
}

void matrix_1D_felszabaditas(int *matrix)
{
    free(matrix);
}

void matrix_1D_kiiras(int *matrix, int oszlop)
{
    for (int i = 0; i < oszlop; i++)
    {
        printf("%d ", matrix[i]);
    }
    printf("\n");
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
        if(kiindulasi_pont+1 > temp_n || veg_pont+1 > temp_n)
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


int minden_kivan_szallitva(int *hazak, int n)
{
    for (int i = 0; i < n; i++)
    {
        if(hazak[i] == 0)
        {
            return 0;
        }
    }
    
    return 1;
}

void szimulalas(int n, int jelenlegi, int **hazak, int *db_latogatas, int *sikeres_e, int *megtett_km)
{
    // Szimulál egy évet mikulás kalandjaiból
    int latogatas_darab = 0;
    int *haz_statisztika = matrix_1D_lefoglalas(n);
    int bool_sikeres = 0;
    int megtett_kilometer = 0;
    int uj_haz = jelenlegi;

    while(latogatas_darab < 1000 && !minden_kivan_szallitva(haz_statisztika, n))
    {
        latogatas_darab++;
        haz_statisztika[jelenlegi]++;

        uj_haz = rand() % n;
        if(jelenlegi == uj_haz) continue;
        while(hazak[jelenlegi][uj_haz] == 0)
        {
            uj_haz = rand() % n;
        }

        megtett_kilometer += hazak[jelenlegi][uj_haz];
        jelenlegi = uj_haz;
    }

    bool_sikeres = minden_kivan_szallitva(haz_statisztika, n);
    *db_latogatas = latogatas_darab;
    *sikeres_e = bool_sikeres;
    *megtett_km = megtett_kilometer;

    matrix_1D_felszabaditas(haz_statisztika);
}

int main()
{
    int n = 1;
    int **matrix = network_beolvasas(&n);
    int kezdo_pont;
    FILE *input = fopen("input.txt", "r");
    fscanf(input, "%d", &kezdo_pont);
    fclose(input);


    srand(time(0));

    //Feladat megoldasa
    int sikerek_szama = 0;
    int kilometerek_osszessege = 0;
    int sikeres_lepesek_szama = 0;

    int legkevesebb_lepes = 1001;
    int legkevesebb_lepes_km = 0;

    for (int i = 0; i < 100; i++)
    {
        int latogatas_darab = 0;
        int sikeres_e = 0;
        int megtett_km = 0;
        szimulalas(n, kezdo_pont, matrix, &latogatas_darab, &sikeres_e, &megtett_km);

        if(sikeres_e)
        {
            sikerek_szama++;
            sikeres_lepesek_szama += latogatas_darab;

            if(latogatas_darab < legkevesebb_lepes)
            {
                legkevesebb_lepes = latogatas_darab;
                legkevesebb_lepes_km = megtett_km;
            }
        }

        kilometerek_osszessege += megtett_km;
    }

    matrix_felszabaditas(matrix, n);

    //Kiiratas
    FILE *output = fopen("output.txt", "w");
    fprintf(output, "%d\n", sikerek_szama);
    fprintf(output, "%d\n", kilometerek_osszessege/100);
    fprintf(output, "%d\n", sikeres_lepesek_szama/sikerek_szama);
    fprintf(output, "%d %d", legkevesebb_lepes, legkevesebb_lepes_km);
    fclose(output);

    return 0;
}