// Széri József - 514
// sjim2307

#include <stdio.h>
#include <stdlib.h>

void nullazos_realloc(int **matrix, int regi_meret, int uj_meret)
{
    int **temp = (int **)realloc(matrix, uj_meret * sizeof(int *));
    if(temp == NULL)
    {
        printf("HIBA!");
    }
    for (int i = regi_meret; i < uj_meret; i++)
    {
        temp[i] = (int *)realloc(temp[i], uj_meret * sizeof(int));
    }
    matrix = temp;

    //Lenullazni az uj elemeket.
    for (int i = regi_meret; i < uj_meret; i++)
    {
        for (int j = regi_meret; j < uj_meret; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void network_beolvasas(int **network, int *n)
{   
    //Kezdetleges lefoglalos networknek (calloc lenullazza)
    network = (int **)calloc(*n, sizeof(int *));
    for (int i = 0; i < *n; i++)
    {
        network[i] = (int *)calloc(*n, sizeof(int));
    }
    
    int elozo_n;
    int kiindulasi_pont;
    int veg_pont;
    int suly;
    FILE *network_text;
    network_text = fopen("network.txt", "r");
    while(fscanf(network_text, "%d %d %d", &kiindulasi_pont, &veg_pont, &suly) != EOF)
    {
        printf("%d %d %d\n", kiindulasi_pont, veg_pont, suly);
        //Ha barmelyik pont nagyobb mint n, akkor ujra kell foglalni.
        if(kiindulasi_pont > *n || veg_pont > *n)
        {   
            elozo_n = *n;
            *n = (kiindulasi_pont > veg_pont) ? kiindulasi_pont : veg_pont;
            printf("Elozo n = %d ||| jelenlegi n = %d\n", elozo_n, *n);
            // nullazos_realloc(network, elozo_n, *n);
        }
    }
    
    fclose(network_text);
}

void kiindulo_csomopont()
{
    FILE *input = fopen("input.txt", "r");
    int alma;
    int pista;
    int kecske;
    fscanf(input, "%d %d %d", &alma, &pista, &kecske);
    printf("%d %d %d", alma, pista, kecske);
    fscanf(input, "%d %d %d", &alma, &pista, &kecske);
    printf("%d %d %d", alma, pista, kecske);
}

int main()
{

    int **network;
    int n = 1;

    // kiindulo_csomopont();
    network_beolvasas(network, &n);

    printf("%d", n);


    //Felszabaditas
    for(int i = 0; i < n; i++)
    {
        free(network[i]);
    }
    free(network);

    return 0;
}