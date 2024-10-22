Peldaprg_n_osszead-nanoszekundumok/                                                                 0000755 �   =�33�   =�_(00000000000 14512202540 020442  5                                                                                                    ustar   lauraruff                       cadre                                                                                                                                                                                                                  Peldaprg_n_osszead-nanoszekundumok/PP_example_sequential.c                                          0000644 �   =�33�   =�_(00000005115 14512160024 025074  0                                                                                                    ustar   lauraruff                       cadre                                                                                                                                                                                                                  // n (veletlenszeruen generalt, 0 és 100 kozotti) egesz szam osszeadasa (megj. 2 <= n <= MAX_N) tetszoleges usleep(u) kesleltetessel
// valamint az osszeadas idejenek merese gettimeofday segitsegevel

// szekvencialis verzio

// compile: gcc -o PP_example_sequential PP_example_sequential.c -Wall

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>

// n maximalis erteke
#define MAX_N 4294967295

// a késleletés u*ARANY (üres) iteráció, ahol u paraméterként van megadva
#define ARANY 100000

// add fuggveny overloading-ja
#define add(a,b,u) ({if (u == 0) add_wo_u(a,b); else add_w_u(a,b,u);})

// veletlenszam generalasa [lower_limit es upper_limit] kozott, adott seed segitsegevel
short get_random_number(int lower_limit, int upper_limit, unsigned int *seed) {
	return (short) ((double) rand_r(seed) / (RAND_MAX + 1.0) * (upper_limit - lower_limit + 1) + lower_limit);
}

// ket egesz szam, a es b osszeadasa tetszoleges u-val arányos kesleltetessel
void add_w_u(long unsigned int *a, int b, int u) {
  for(long unsigned int i=0;i<u*ARANY;i++){}
	*a += b;
}

// ket egesz szam, a es b osszeadasa
void add_wo_u(long unsigned int *a, int b) {
	*a += b;
}

int main(int argc, char *argv[]) {

	unsigned long int n;
	unsigned long int i;
	int u = 0;
	struct timespec start, stop;
	short *numbers;
	unsigned int seed = time(NULL);
	unsigned long int res;

	// bemeneti parameterek ellenorzese
	if (argc < 2) {
		printf("usage ./PP_example_sequential n OR ./PP_example_sequential n u\n\t2 <= n <= MAX_N (2^32)\n\tu * %d cycles delay\n", ARANY);
		exit(1);
	}
	else if (argc < 3) {
		n = atoi(argv[1]);
	} else {
		n = atoi(argv[1]);
		u = atoi(argv[2]);
	}

	// n ertekenek ellenorzese
	if ((n < 2) || (n > MAX_N)) {
		printf("2 <= n <= MAX_N (2^32)\n");
		exit(1);
	}

	// veletlenszamok generalasa es tarolasa
	numbers = malloc(sizeof(short) * n);

	for (i = 0; i < n; i++) {
		numbers[i] = get_random_number(0,100,&seed);
		// printf("%d\n", numbers[i]);
	}
	
	// futasi ido merese, kezdeti ido elmentese
	clock_gettime(CLOCK_REALTIME,&start);

	// osszeadasok kiszamolasa
	res = 0;

	for (i = 0; i < n; i++) {
		add(&res,numbers[i],u);
	}
	
	// vegzesi ido elmentese
	clock_gettime(CLOCK_REALTIME,&stop);

	// az osszeg es a futasi ido kiirasa
	long unsigned int e_time=(stop.tv_sec - start.tv_sec) * 1000000000 + stop.tv_nsec - start.tv_nsec;

	printf("The sum is: %lu, and the elapsed time is %lu ns (%lf s)\n",res,e_time,e_time*1.0/1000000000); 

	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                   Peldaprg_n_osszead-nanoszekundumok/PP_example_parallel_optimal.c                                    0000644 �   =�33�   =�_(00000012055 14512160046 026250  0                                                                                                    ustar   lauraruff                       cadre                                                                                                                                                                                                                  // n (veletlenszeruen generalt, 0 és 100 kozotti) egesz szam osszeadasa (megj. 2 <= n <= MAX_N) tetszoleges usleep(u) kesleltetessel
// p = 2^m parhuzamos folyamattal
// valamint az osszeadas idejenek merese gettimeofday segitsegevel

// parhuzamos verzio - optimalizalt valtozat

// compile: gcc -o PP_example_parallel_optimal PP_example_parallel_optimal.c -lm -Wall

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>

// n maximalis erteke
#define MAX_N 4294967295

// a késleletés u*ARANY (üres) iteráció, ahol u paraméterként van megadva
#define ARANY 100000

// p maximalis erteke
#define MAX_P 256

// 2^m folyamatot hozunk létre, MAXHATVANY az m maximális elfogadott értéke
#define MAXHATVANY 5


// add fuggveny overloading-ja
#define add(a,b,u) ({if (u == 0) add_wo_u(a,b); else add_w_u(a,b,u);})

// veletlenszam generalasa [lower_limit es upper_limit] kozott, adott seed segitsegevel
short get_random_number(int lower_limit, int upper_limit, unsigned int *seed) {
	return (short) ((double) rand_r(seed) / (RAND_MAX + 1.0) * (upper_limit - lower_limit + 1) + lower_limit);
}

// ket egesz szam, a es b osszeadasa tetszoleges, u-val arányos kesleltetessel
void add_w_u(long unsigned int *a, int b, int u) {
	for(long unsigned int i=0;i<u*ARANY;i++){}
	*a += b;
}

// ket egesz szam, a es b osszeadasa
void add_wo_u(long unsigned int *a, int b) {
	*a += b;
}

int main(int argc, char *argv[]) {

	unsigned long int n;
	unsigned long int i;
	int u = 0;
	int m;
	int p;
	struct timespec start, stop;
	short *numbers;
	unsigned int seed = time(NULL);
	unsigned long int res;
	unsigned long int tmp_sum;

	int pfd[MAX_P][2];
	pid_t pid[MAX_P];

	// bemeneti parameterek ellenorzese
	if (argc < 3) {
		printf("usage ./PP_example_parallel_optimal n m OR ./PP_example_parallel_optimal n m u\n\t2 <= n <= MAX_N (2^32)\n\t1 <= m <= %d\n\tu * %d cycles delay\n",MAXHATVANY,ARANY);
		exit(1);
	}
	else if (argc < 4) {
		n = atoi(argv[1]);
		m = atoi(argv[2]);
	} else {
		n = atoi(argv[1]);
		m = atoi(argv[2]);
		u = atoi(argv[3]);
	}

	// n ertekenek ellenorzese
	if ((n < 2) || (n > MAX_N)) {
		printf("\n 2 <= n <= MAX_N (2^32)\n");
		exit(1);
	}

	// m ertekenek ellenorzese
	if ((m < 1) || (m > MAXHATVANY)) {
		printf("\n 1 <= m <= %d\n", MAXHATVANY);
		exit(1);
	}

	// parhuzamos folyamatok szama
	p = (int) pow(2,m);

	// veletlenszamok generalasa es tarolasa
	numbers = malloc(sizeof(short) * n);

	for (i = 0; i < n; i++) {
		numbers[i] = get_random_number(0,100,&seed);
		// printf("%d\n", numbers[i]);
	}

	// pipe-ok letrehozasa
	for (i = 0; i < p/2; i++) {
		if (pipe(pfd[i]) < 0) {
			printf("%s\n", "Pipe error\n");
		}
	}

	// futasi ido merese, kezdeti ido elmentese
	clock_gettime(CLOCK_REALTIME,&start);

	// p-1 gyerekfolyamat letrehozasa, amelyek kiszamoljak a nekik kiosztott reszosszeget es beleirjak a megfelelo pipe-ba
	// majd a megfelelo  gyerekfolyamatok kiolvassak a hozzajsuk erkezo reszosszeget es ujabb osszegzest vegeznek
	for (i = 1; i < p; i++) {
		pid[i] = fork ();
		if (pid[i] < 0) {
			printf("%s\n", "Fork error\n");
		}

		if (pid[i] == 0) {
			unsigned long int res = 0;
			unsigned long int j;
			unsigned long int tmp_sum;

			unsigned long int from = i*n/p;
			unsigned long int to = (unsigned long int) fmin(n,(i+1)*n/p);

			for (j = from; j < to; j++) {
				add(&res,numbers[j],u);
			}

			// eldontjuk, hogy az adott gyerekfolyamat kell meg tovabbi reszosszeget szamoljon vagy csak beleirja
			// az altala eddig szamolt osszeget a megfelelo pipe-ba es utana befejezodik
			int counter = 2;
			while (counter <= p) {
				if ((i % counter) != 0) {
					close(pfd[i/counter][0]);
					write(pfd[i/counter][1], &res, sizeof(res));
					// printf("pipe: %lu <<<<< process: %lu value: %lu\n", i/counter, i, res);
					exit(0);
				} else {
					close(pfd[i/counter][1]);
					read(pfd[i/counter][0], &tmp_sum, sizeof(unsigned long int));
					// printf("pipe: %lu >>>>> process: %lu value 1: %lu value 2: %lu\n", i/counter, i, res, tmp_sum);
					add(&res,tmp_sum,u);
				}

				counter *= 2;
			}

			exit(0); 
		}
	}

	// a szulofolyamat kiszamolja az elso n/p szam reszosszeget
	res = 0;

	for (i = 0; i < (unsigned long int) fmin(n,n/p); i++) {
		add(&res,numbers[i],u);
	}

	// m darab reszosszeg bevarasa es kiolvasasa a pipe-bol es ezek osszegzese
	close(pfd[0][1]);
	for(i = 0; i < m; i++) {
		read(pfd[0][0], &tmp_sum, sizeof(unsigned long int));
		// printf("pipe: 0 >>>>> process: 0 value 1: %lu value 2: %lu\n", res, tmp_sum);
		add(&res,tmp_sum,u);
	}
	
	// vegzesi ido elmentese
	clock_gettime(CLOCK_REALTIME,&stop);

	// az osszeg es a futasi ido kiirasa
long unsigned int e_time=(stop.tv_sec - start.tv_sec) * 1000000000 + stop.    tv_nsec - start.tv_nsec;

	printf("The sum is: %lu, and the elapsed time is %lu ns (%lf s)\n", res, e_time, e_time*1.0/1000000000);

	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   Peldaprg_n_osszead-nanoszekundumok/teszteredmenyek                                                  0000644 �   =�33�   =�_(00000022310 14512202510 023602  0                                                                                                    ustar   lauraruff                       cadre                                                                                                                                                                                                                  # megjegyzés: a linux szerveren 16 mag van 

#paraméter nélküli hívás: hibaüzenetet kapunk + leírás a helyes használatról

$./PP_example_sequential
usage ./PP_example_sequential n OR ./PP_example_sequential n u
        2 <= n <= MAX_N (2^32)
        u * 1000000 cycles delay
		
$./PP_example_parallel_not_optimal
usage ./PP_example_parallel_not_optimal n m OR ./PP_example_parallel_not_optimal n m u
        2 <= n <= MAX_N (2^32)
        1 <= m <= 5
        u * 1000000 cycles delay
		
$./PP_example_parallel_optimal
usage ./PP_example_parallel_optimal n m OR ./PP_example_parallel_optimal n m u
        2 <= n <= MAX_N (2^32)
        1 <= m <= 5
        u * 1000000 cycles delay
		
####################################################################################################################
#                        szekvenciális program
# Figyeljük meg a futási időt 100, 1000, 10000, 100000 illetve 1000000 elem összeadása esetén (várakozási idő nincs)
# majd hasonlítsuk össze ugyanennyi szám összeadásakor kapott futási időket a két párhuzamos verzió esetén
####################################################################################################################
$./PP_example_sequential 100
The sum is: 5354, and the elapsed time is 3390 ns (0.000003 s)
$./PP_example_sequential 1000
The sum is: 49929, and the elapsed time is 7998 ns (0.000008 s)
$./PP_example_sequential 10000
The sum is: 499805, and the elapsed time is 54275 ns (0.000054 s)
$./PP_example_sequential 100000
The sum is: 5005933, and the elapsed time is 532744 ns (0.000533 s)
$./PP_example_sequential 1000000


######################################################################################################################
#                     párhuzamos összeadás, nem optimalizált változat
######################################################################################################################

$./PP_example_parallel_not_optimal 100 1
The sum is: 5028, and the elapsed time is 345497 ns (0.000345 s)
$./PP_example_parallel_not_optimal 100 2
The sum is: 5455, and the elapsed time is 627631 ns (0.000628 s)
$./PP_example_parallel_not_optimal 100 3
The sum is: 5307, and the elapsed time is 1181079 ns (0.001181 s)
$./PP_example_parallel_not_optimal 100 4
The sum is: 4653, and the elapsed time is 2241970 ns (0.002242 s)

######################################## kevés szám összeadása #########################################################
# megfigyelhetjük, hogy a futási idő egyrészt lényegesen rosszabb, mint szekvenciális esetben, másrészt, ahogy a folyamatok
# számát növeljük (2^1=2, 2^2=4, 8 majd 16 folyamat), egyre romlik a helyet
# Ennek a magyarázata az, hogy 100 szám összeadása esetén egy-egy folyamatnak viszonylag rövid időbe telik 100/2, 100/4, 100/8,
# vagy 100/16 szám összeadása, ehhez képest jóval nagyobb az az idő-többletráfordítás, amibe a folyamatok létrehozása, illetve 
# a kommunikáció kerül

# Nézzük meg, hogy mi történik, ha ugyanennyi számot adunk össze, de a "késleltetett összeadást" használjuk, azaz valamilyen
# hosszabb időt igénybe vevő műveletet kéne elvégezni.

#  szekvenciális összeadás:
$./PP_example_sequential 100 1
The sum is: 4798, and the elapsed time is 24530017 ns (0.024530 s)
# párhuzamos, nem optimalizált változat:
$./PP_example_parallel_not_optimal 100 1 1
The sum is: 4862, and the elapsed time is 12800900 ns (0.012801 s)
# máris jobb eredményt kaptunk 2^1=2 folyamatra

$./PP_example_parallel_not_optimal 100 2 1
The sum is: 4948, and the elapsed time is 7435076 ns (0.007435 s)
# négy folyamatra még jobb az eredmény 
$./PP_example_parallel_not_optimal 100 3 1
The sum is: 4742, and the elapsed time is 5733758 ns (0.005734 s)
# 2^3=8 folyamat esetén még jobb, bár itt már nem lényegesen
$./PP_example_parallel_not_optimal 100 4 1
The sum is: 5217, and the elapsed time is 7248275 ns (0.007248 s)
# 2^4=16 folyamat esetén már rosszabb időt kapunk


# az optimalizáltnak nevezett párhuzamos algoritmus ilyen kevés szám összeadása esetén általában valamivel rosszabb eredményt ad, mint a
# nem optimalizált társa, bár mindkettő jobb, mint a szekvenciális, ha "hosszú művelet"-ről van szó
$./PP_example_sequential 100 4
The sum is: 5060, and the elapsed time is 98050468 ns (0.098050 s)
$./PP_example_parallel_not_optimal 100 1 4
The sum is: 5365, and the elapsed time is 50268825 ns (0.050269 s)
$./PP_example_parallel_optimal 100 1 4
The sum is: 4827, and the elapsed time is 50284022 ns (0.050284 s)

################################################################################################################################

############### nézzük meg, mi történik, ha egyre több számot adunk össze (késleltetés nélkül) ######################################

#### 10^6 = 1000000 szám:#####################################
$./PP_example_sequential 1000000
The sum is: 49979369, and the elapsed time is 5256915 ns (0.005257 s)
$./PP_example_parallel_not_optimal 1000000 1
The sum is: 49978472, and the elapsed time is 9461545 ns (0.009462 s)
$./PP_example_parallel_optimal 1000000 1
The sum is: 49994247, and the elapsed time is 9285753 ns (0.009286 s)
### ugyanennyi szám összeadása 4 processzoron#####
$./PP_example_parallel_not_optimal 1000000 2
The sum is: 50035481, and the elapsed time is 5319208 ns (0.005319 s)
$./PP_example_parallel_optimal 1000000 2
The sum is: 49980441, and the elapsed time is 5118426 ns (0.005118 s)
### itt kb. ugyanolyan futási időt kaptunk, mint a szekvenciális esetben

#### 10^8 = 100 000 000 azaz még több szám:#####################################
$./PP_example_sequential 100000000
The sum is: 5000024801, and the elapsed time is 538975550 ns (0.538976 s)
$./PP_example_parallel_not_optimal 100000000 1
The sum is: 704800004, and the elapsed time is 918595621 ns (0.918596 s)
$./PP_example_parallel_optimal 100000000 1
The sum is: 704969806, and the elapsed time is 916718749 ns (0.916719 s)
# azaz még mindig rosszabb a futási idő két folyamattal, mint szekvenciális esetben  
$./PP_example_parallel_not_optimal 100000000 2
The sum is: 4999984862, and the elapsed time is 458432999 ns (0.458433 s)
$./PP_example_parallel_optimal 100000000 2
The sum is: 704887203, and the elapsed time is 459385590 ns (0.459386 s)
# 4 folyamattal kicsit jobb a futási idő
$./PP_example_parallel_not_optimal 100000000 3
The sum is: 4999995378, and the elapsed time is 230678808 ns (0.230679 s)
$./PP_example_parallel_optimal 100000000 3
The sum is: 704894035, and the elapsed time is 231505817 ns (0.231506 s)
# 8 folyamattal még jobb futási időket kapunk
$./PP_example_parallel_not_optimal 100000000 4
The sum is: 5000123043, and the elapsed time is 119071242 ns (0.119071 s)
$./PP_example_parallel_optimal 100000000 4
The sum is: 705041385, and the elapsed time is 120513258 ns (0.120513 s)
# 16 folyamattal még jobb az eredmény 
$./PP_example_parallel_not_optimal 100000000 5
The sum is: 4999857617, and the elapsed time is 67639931 ns (0.067640 s)
$./PP_example_parallel_optimal 100000000 5
The sum is: 704973350, and the elapsed time is 80012028 ns (0.080012 s)
# érdekes módon 32 folyamattal még jobb időt kapunk (pedig ezekből csak 16 futhat párhuzamosan, mivel a linux szerver 16 magos)

####### most hasonlítsuk össze a futási időket "sok szám" összeadása, és hosszú művelet esetén:
# 10^6 = 1000000 szám összeadása 
$./PP_example_sequential 1000000 1
The sum is: 49971631, and the elapsed time is 244910001153 ns (244.910001 s)
## több, mint 4 percig futott...
$./PP_example_parallel_not_optimal 1000000 1 1
The sum is: 50005367, and the elapsed time is 122629261820 ns (122.629262 s)
$./PP_example_parallel_optimal 1000000 1 1
The sum is: 49963925, and the elapsed time is 122296370505 ns (122.296371 s	
#"szinte" fele annyi idő két folyamattal
$./PP_example_parallel_not_optimal 1000000 3 1
The sum is: 49948352, and the elapsed time is 31076133302 ns (31.076133 s)
$./PP_example_parallel_optimal 1000000 3 1
The sum is: 49997525, and the elapsed time is 30924588397 ns (30.924588 s)
# 8 folyamattal "közel" 8-szor rövidebb idő
$./PP_example_parallel_not_optimal 1000000 4 1
The sum is: 49977009, and the elapsed time is 16506195727 ns (16.506196 s)
$./PP_example_parallel_optimal 1000000 4 1
The sum is: 49958679, and the elapsed time is 15605258505 ns (15.605259 s)

# az optimalizált verzió általában valamivel jobb volt, de igazából nagy számú processzor esetén adna látványosabban jobb eredményt, a linux szerveren viszont csak 16 mag van,
# így ezt nem tudjuk demonstrálni, de a tendencia látszik (ti., hogy nagyobb folyamatszám mellett kapunk a nem optimalizáltnál 
# jobb eredményt)
#
# +1 megjegyzés: a mért futási idő függhet az ütemezéstől, így attól is, hogy éppen 
# milyen más folyamatok futnak a rendszerben. Ha pontosabb eredményt szeretnénk, akkor 
# több futási idő átlagát lenne érdemes számításba venni. Itt (inkább időtakarékosságból...) 
# egy-egy futtatás eredménye van feltűntetve, tehát kevésbő pontos érték, de a futási idő
# nagyságrendjét azért tükrözi.
                                                                                                                                                                                                                                                                                                                        Peldaprg_n_osszead-nanoszekundumok/PP_example_parallel_not_optimal.c                                0000644 �   =�33�   =�_(00000010355 14512172066 027136  0                                                                                                    ustar   lauraruff                       cadre                                                                                                                                                                                                                  // n (veletlenszeruen generalt, 0 és 100 kozotti) egesz szam osszeadasa (megj. 2 <= n <= MAX_N) tetszoleges usleep(u) kesleltetessel
// p = 2^m parhuzamos folyamattal
// valamint az osszeadas idejenek merese gettimeofday segitsegevel

// parhuzamos verzio - nem optimalizalt valtozat

// compile: gcc -o PP_example_parallel_not_optimal PP_example_parallel_not_optimal.c -lm -Wall

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>

// n maximalis erteke
#define MAX_N 4294967295

// a késleletés u*ARANY (üres) iteráció, ahol u paraméterként van megadva
#define ARANY 100000

// p maximalis erteke
#define MAX_P 256

// 2^m folyamatot hozunk létre, MAXHATVANY az m maximális elfogadott értéke
#define MAXHATVANY 5


// add fuggveny overloading-ja
#define add(a,b,u) ({if (u == 0) add_wo_u(a,b); else add_w_u(a,b,u);})

// veletlenszam generalasa [lower_limit es upper_limit] kozott, adott seed segitsegevel
short get_random_number(int lower_limit, int upper_limit, unsigned int *seed) {
	return (short) ((double) rand_r(seed) / (RAND_MAX + 1.0) * (upper_limit - lower_limit + 1) + lower_limit);
}

// ket egesz szam, a es b osszeadasa tetszoleges, u-val arányos kesleltetessel
void add_w_u(long unsigned int *a, int b, int u) {
	for(long unsigned int i=0;i<u*ARANY;i++){}
  *a += b;
}

// ket egesz szam, a es b osszeadasa
void add_wo_u(long unsigned int *a, int b) {
	*a += b;
}

int main(int argc, char *argv[]) {

	unsigned long int n;
	unsigned long int i;
	int u = 0;
	int m;
	int p;
	struct timespec start, stop;
	short *numbers;
	unsigned int seed = time(NULL);
	unsigned long int res;
	unsigned long int tmp_sum;

	int pfd[2];
	pid_t pid[MAX_P];

	// bemeneti parameterek ellenorzese
	if (argc < 3) {
		printf("usage ./PP_example_parallel_not_optimal n m OR ./PP_example_parallel_not_optimal n m u\n\t2 <= n <= MAX_N (2^32)\n\t1 <= m <= %d\n\tu * %d cycles delay\n",MAXHATVANY, ARANY);
		exit(1);
	}
	else if (argc < 4) {
		n = atoi(argv[1]);
		m = atoi(argv[2]);
	} else {
		n = atoi(argv[1]);
		m = atoi(argv[2]);
		u = atoi(argv[3]);
	}

	// n ertekenek ellenorzese
	if ((n < 2) || (n > MAX_N)) {
		printf("%s\n", "2 <= n <= MAX_N (2^32)\n");
		exit(1);
	}

	// m ertekenek ellenorzese
	if ((m < 1) || (m > MAXHATVANY)) {
		printf("\n 1 <= m <= %d\n", MAXHATVANY);
		exit(1);
	}

	// parhuzamos folyamatok szama
	p = (int) pow(2,m);

	// veletlenszamok generalasa es tarolasa
	numbers = malloc(sizeof(short) * n);

	for (i = 0; i < n; i++) {
		numbers[i] = get_random_number(0,100,&seed);
		// printf("%d\n", numbers[i]);
	}

	// pipe letrehozasa
	if (pipe(pfd) < 0) {
		printf("%s\n", "Pipe error\n");
	}

	// futasi ido merese, kezdeti ido elmentese
	clock_gettime(CLOCK_REALTIME,&start);

	// p-1 gyerekfolyamat letrehozasa, amelyek kiszamoljak a nekik kiosztott reszosszeget es beleirjak a pipe-ba
	for (i = 1; i < p; i++) {
		pid[i] = fork ();
		if (pid[i] < 0) {
			printf("%s\n", "Fork error\n");
		}

		if (pid[i] == 0) {
			unsigned long int res = 0;
			unsigned long int j;

			unsigned long int from = i*n/p;
			unsigned long int to = (unsigned long int) fmin(n,(i+1)*n/p);

			for (j = from; j < to; j++) {
				add(&res,numbers[j],u);
			}

			close(pfd[0]);
			write(pfd[1], &res, sizeof(res));

			// printf("child: %lu, res: %lu [son] pid %d from [parent] pid %d\n", i, res, getpid(), getppid());
			exit(0); 
		}
	}

	// a szulofolyamat kiszamolja az elso n/p szam reszosszeget
	res = 0;

	for (i = 0; i < (unsigned long int) fmin(n,n/p); i++) {
		add(&res,numbers[i],u);
	}


	// p-1 gyerekfolyamat bevarasa es a reszosszeg kiolvasasa a pipe-bol
	close(pfd[1]);

	for(i = 0; i < p-1; i++) {
		read(pfd[0], &tmp_sum, sizeof(unsigned long int));
		add(&res,tmp_sum,u);
	}
	
	// vegzesi ido elmentese
	clock_gettime(CLOCK_REALTIME,&stop);

	// az osszeg es a futasi ido kiirasa
long unsigned int e_time=(stop.tv_sec - start.tv_sec) * 1000000000 + stop.    tv_nsec - start.tv_nsec;
	
printf("The sum is: %lu, and the elapsed time is %lu ns (%lf s)\n", res,e_time,e_time*1.0/1000000000);

	return 0;
}
                                                                                                                                                                                                                                                                                   Peldaprg_n_osszead-nanoszekundumok/makefile                                                         0000644 �   =�33�   =�_(00000001035 13732427473 022162  0                                                                                                    ustar   lauraruff                       cadre                                                                                                                                                                                                                  all: sequatial_add paralellel_add_not_optimal paralellel_add_optimal

sequatial_add: PP_example_sequential.c
	gcc -o PP_example_sequential PP_example_sequential.c -Wall

paralellel_add_not_optimal: PP_example_parallel_not_optimal.c
	gcc -o PP_example_parallel_not_optimal PP_example_parallel_not_optimal.c -lm -Wall

paralellel_add_optimal: PP_example_parallel_optimal.c
	gcc -o PP_example_parallel_optimal PP_example_parallel_optimal.c -lm -Wall

clean:
	rm PP_example_sequential PP_example_parallel_not_optimal PP_example_parallel_optimal
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   