#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_RANDOM_CSERE 1000
#define PAKLI_MERET 54

bool parameter_check(int argc, const char *argv[])
{
	if(argc != 2)
	{
		return false;
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			int length = strlen(argv[i]);
			for (int j = 0; j < length; j++)
			{
				if(!isdigit(argv[i][j]))
				{
					return false;
				}
			}
		}
	}

	return true;
}



void swap(int *first, int *second)
{
	int temp = *first;
	*first = *second;
	*second = temp;
}



int *pakli_alkotas()
{
	//Megalkotni a kartyapaklit.
	//A fekete es feher joker ugyanannyi erteku kell legyen
	int *kartyak = (int *) calloc(PAKLI_MERET, sizeof(int));
	for (int i = 0; i < PAKLI_MERET - 1; ++i)
	{
		kartyak[i] = i+1;
	}
	kartyak[PAKLI_MERET-1] = 53;

	return kartyak;
}

void joker_valtozas(int *feher_index, int *fekete_index, int elso, int masodik)
{
	if(*feher_index == elso)
	{
		*feher_index = masodik;
	}
	else if(*feher_index == masodik)
	{
		*feher_index = elso;
	}

	if(*fekete_index == elso)
	{
		*fekete_index = masodik;
	}
	else if(*fekete_index == masodik)
	{
		*fekete_index = elso;
	}
}

int *pakli_keveres(int *pakli, int *feher_index, int *fekete_index, int hanyszor)
{
	//úgy folyik a csere, hogy kiválasztunk 2 kártyát, majd felcseréljük őket.
	//Ezt annyiszor végezzük el amennyit a hanyszor változó mond.
	//Igy egy "realisztikus" cserét szimulálunk és pakli tömb-höz nem kell majd segédváltozó.
	srand(time(0));
	for (int i = 0; i < hanyszor; ++i)
	{
		int elso = rand() % PAKLI_MERET;
		int masodik = rand() % PAKLI_MERET;

		swap(&pakli[elso], &pakli[masodik]);

		//Ha véletlenül változott a joker helye, akkor az indexeket is változtatni kell
		joker_valtozas(feher_index, fekete_index, elso, masodik);
	}

	return pakli;
}

void pakli_kiiras(int *pakli)
{
	for (int i = 0; i < PAKLI_MERET; ++i)
	{
		printf("%d ", pakli[i]);
	}

	printf("\n");
}



int *kettes_lepes(int *pakli, int *feher_index, int *fekete_index)
{
	//Ha nem utolsó lap
	if(*feher_index != PAKLI_MERET - 1)
	{
		swap(&pakli[*feher_index], &pakli[*feher_index+1]);
		*feher_index+=1;

		//Ha a két joker egymás mellett van
		if(*fekete_index == *feher_index)
		{
			*fekete_index-=1;
		}
	}

	else
	{
		int temp = pakli[PAKLI_MERET-1];
		memmove(pakli+2, pakli+1, (PAKLI_MERET-2) * sizeof(int));
		*feher_index = 1;
		pakli[1] = temp;

		if(fekete_index != 0)
		{
			*fekete_index += 1;
		}
	}

	return pakli;
}

int *harmas_lepes(int *pakli, int *feher_index, int *fekete_index)
{
	//Ha nem utolsó/előtti lap
	if(*fekete_index < PAKLI_MERET - 2)
	{
		swap(&pakli[*fekete_index], &pakli[*fekete_index+2]);
		*fekete_index+=2;

		//Ha a két joker egymás mellett van
		if(*fekete_index == *feher_index)
		{
			*feher_index-=2;
		}
	}

	else if(*fekete_index == PAKLI_MERET - 2)
	{
		int temp = pakli[PAKLI_MERET-2];
		memmove(pakli+2, pakli+1, (PAKLI_MERET-3) * sizeof(int));
		*fekete_index = 1;
		pakli[1] = temp;

		if(*feher_index != 0 && *feher_index < PAKLI_MERET-1)
		{
			*feher_index += 1;
		}
	}
	else if(*fekete_index == PAKLI_MERET - 1)
	{
		int temp = pakli[PAKLI_MERET-1];
		memmove(pakli+3, pakli+2, (PAKLI_MERET-3) * sizeof(int));
		*fekete_index = 2;
		pakli[2] = temp;

		if(*feher_index > 2)
		{
			*feher_index += 1;
		}
	}

	return pakli;
}

// int *negyes_lepes(int *pakli, int *feher_index, int *fekete_index)
// {
// 	//0 feherindex-1
// 	//fehereindex / feketeindex
// 	//fekeindex+1, paklimeret-1
// 	int also, felso;
// 	if(*feher_index < *fekete_index)
// 	{
// 		also = *feher_index;
// 		felso = *fekete_index;
// 	}
// 	else
// 	{
// 		also = *fekete_index;
// 		felso = *feher_index;
// 	}

// 	int *ujpakli = (int *) calloc(PAKLI_MERET, sizeof(int));
// 	// memcpy(ujpakli, pakli, (PAKLI_MERET)*sizeof(int));

// 	memcpy(ujpakli, pakli+felso+1, (PAKLI_MERET-felso-1)*sizeof(int));
// 	memcpy(ujpakli+felso+1, pakli, (also)*sizeof(int));

// 	return ujpakli;
// }

// void otos_lepes()
// {
// 	return;
// }

void hatos_lepes(int *pakli, int *feher_index, int *fekete_index)
{
	int legfelso = pakli[0];
	if(legfelso == 53)
	{
		return;
	}

	int szam = pakli[legfelso];

	FILE *output = fopen("output.txt", "a");
	if(output == NULL)
	{
		exit(1);
	}

	fprintf(output, "%d\n", szam);
	fclose(output);
}

int main(int argc, const char *argv[])
{

	if(!parameter_check(argc, argv))
	{
		printf("Helytelen parameter!");
		exit(1);
	}

	int generacio_szam = atoi(argv[1]);


	int *kartyak = pakli_alkotas();

	int feher_index = 52;
	int fekete_index = 53;

	kartyak = pakli_keveres(kartyak, &feher_index, &fekete_index, MAX_RANDOM_CSERE);
	// pakli_kiiras(kartyak);
	// printf("%d-%d %d/%d\n\n", feher_index, fekete_index, kartyak[feher_index], kartyak[fekete_index]);


	//Üres vájlt létrehozni / mindig resetálni a tartalmat.
	FILE *output = fopen("output.txt", "w");
	fclose(output);

	for (int i = 0; i < generacio_szam; ++i)
	{
		kartyak = kettes_lepes(kartyak, &feher_index, &fekete_index);
		kartyak = harmas_lepes(kartyak, &feher_index, &fekete_index);
		// kartyak = negyes_lepes(kartyak, &feher_index, &fekete_index);
		// kartyak = otos_lepes();
		hatos_lepes(kartyak, &feher_index, &fekete_index);
	}

	free(kartyak);
	return 0;
}