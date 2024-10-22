Peldaprg_n_osszead/                                                                                 0000775 0001750 0001750 00000000000 13742006770 014273  5                                                                                                    ustar   vlewir                          vlewir                                                                                                                                                                                                                 Peldaprg_n_osszead/teszteredmenyek                                                                  0000644 0001750 0001750 00000017056 13732446315 017451  0                                                                                                    ustar   vlewir                          vlewir                                                                                                                                                                                                                 # megjegyzés: a linux szerveren 8 mag van 

#paraméter nélküli hívás: hibaüzenetet kapunk + leírás a helyes használatról

$./PP_example_sequential
usage ./PP_example_sequential n OR ./PP_example_sequential n u
        2 <= n <= MAX_N (2^32)
        u microseconds in usleep()
		
$./PP_example_parallel_not_optimal
usage ./PP_example_parallel_not_optimal n m OR ./PP_example_parallel_not_optimal n m u
        2 <= n <= MAX_N (2^32)
        1 <= m <= 4
        u microseconds in usleep()
		
$./PP_example_parallel_optimal
usage ./PP_example_parallel_optimal n m OR ./PP_example_parallel_optimal n m u
        2 <= n <= MAX_N (2^32)
        1 <= m <= 4
        u microseconds in usleep()
		
####################################################################################################################
#                        szekvenciális program
# Figyeljük meg a futási időt 100, 1000, 10000, 100000 illetve 1000000 elem összeadása esetén (várakozási idő nincs)
# majd hasonlítsuk össze ugyanennyi szám összeadásakor kapott futási időket a két párhuzamos verzió esetén
####################################################################################################################
$./PP_example_sequential 100
The sum is: 5102, and the elapsed time is 1 us
$./PP_example_sequential 1000
The sum is: 51583, and the elapsed time is 9 us
$./PP_example_sequential 10000
The sum is: 499341, and the elapsed time is 82 us
$./PP_example_sequential 100000
The sum is: 5011889, and the elapsed time is 837 us
$./PP_example_sequential 1000000
The sum is: 50002783, and the elapsed time is 8722 us

######################################################################################################################
#                     párhuzamos összeadás, nem optimalizált változat
######################################################################################################################

$./PP_example_parallel_not_optimal 100 1
The sum is: 5078, and the elapsed time is 2656 us
$./PP_example_parallel_not_optimal 100 2
The sum is: 5138, and the elapsed time is 3823 us
$./PP_example_parallel_not_optimal 100 3
The sum is: 4727, and the elapsed time is 6184 us
$./PP_example_parallel_not_optimal 100 4
The sum is: 5201, and the elapsed time is 10576 us

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
The sum is: 5091, and the elapsed time is 8267 us
# párhuzamos, nem optimalizált változat:
$./PP_example_parallel_not_optimal 100 1 1
The sum is: 4993, and the elapsed time is 6780 us
# máris jobb eredményt kaptunk 2^1=2 folyamatra

$./PP_example_parallel_not_optimal 100 2 1
The sum is: 4998, and the elapsed time is 5905 us
# négy folyamatra még jobb az eredmény (bár nem lényegesen)
$./PP_example_parallel_not_optimal 100 3 1
The sum is: 5363, and the elapsed time is 8307 us
# viszont 2^3=8 folyamat esetén már romlik a helyzet

# az optimalizáltnak nevezett párhuzamos algoritmus ilyen kevés szám összeadása esetén általában rosszabb eredményt ad, mint a
# nem optimalizált társa, bár mindkettő jobb, mint a szekvenciális, ha "hosszú művelet"-ről van szó
$./PP_example_sequential 100 4
The sum is: 4653, and the elapsed time is 8148 us
$./PP_example_parallel_not_optimal 100 1 4
The sum is: 5148, and the elapsed time is 7324 us
$./PP_example_parallel_optimal 100 1 4
The sum is: 5039, and the elapsed time is 7579 us
################################################################################################################################

############### nézzük meg, mi történik, ha egyre több számot adunk össze (késleltetés nélkül) ######################################

#### 10^6 = 1000000 szám:#####################################
$./PP_example_sequential 1000000
The sum is: 49965361, and the elapsed time is 8359 us
$./PP_example_parallel_not_optimal 1000000 1
The sum is: 50054039, and the elapsed time is 14335 us
$./PP_example_parallel_optimal 1000000 1
The sum is: 49994704, and the elapsed time is 14509 us
### ugyanennyi szám összeadása 4 processzoron#####
$./PP_example_parallel_not_optimal 1000000 2
The sum is: 49983602, and the elapsed time is 10983 us
$./PP_example_parallel_optimal 1000000 2
The sum is: 49996567, and the elapsed time is 11330 us

#### 10^8 = 100 000 000 szám:#####################################
$./PP_example_sequential 100000000
The sum is: 4999806639, and the elapsed time is 562989 us
$./PP_example_parallel_not_optimal 100000000 1
The sum is: 705116430, and the elapsed time is 910071 us
$./PP_example_parallel_optimal 100000000 1
The sum is: 705383848, and the elapsed time is 941649 us
# azaz még mindig rosszabb a futási idő két folyamattal, mint szekvenciális esetben  
$./PP_example_parallel_not_optimal 100000000 3
The sum is: 4999890621, and the elapsed time is 246721 us
$./PP_example_parallel_optimal 100000000 3
The sum is: 704968193, and the elapsed time is 238380 us
# 8 folyamattal már jobb futási időket kapunk, sőt, ez az első olyan példa (az eddigiek közül), ahol az optimalizált verzió jobb
$./PP_example_parallel_not_optimal 100000000 4
The sum is: 5000007705, and the elapsed time is 231238 us
$./PP_example_parallel_optimal 100000000 4
The sum is: 704903444, and the elapsed time is 180949 us
# 16 folyamattal még jobb az eredmény (de messze nem kétszer olyan jó, mivel csak 8 mag van a linux szerveren)

####### most hasonlítsuk össze a futási időket "sok szám" összeadása, és hosszú művelet esetén:
# 10^6 = 1000000 szám összeadása 
$./PP_example_sequential 1000000 1
The sum is: 50054949, and the elapsed time is 79771283 us
## több, mint 1 percig futott...
$./PP_example_parallel_not_optimal 1000000 1 1
The sum is: 50007946, and the elapsed time is 40715778 us
$./PP_example_parallel_optimal 1000000 1 1
The sum is: 50049695, and the elapsed time is 40833267 us
#"szinte" fele annyi idő két folyamattal
$./PP_example_parallel_not_optimal 1000000 3 1
The sum is: 49989981, and the elapsed time is 10313419 us
$./PP_example_parallel_optimal 1000000 3 1
The sum is: 50049889, and the elapsed time is 10318015 us
# 8 folyamattal "közel" 8-szor rövidebb idő
$./PP_example_parallel_not_optimal 1000000 4 1
The sum is: 49976192, and the elapsed time is 5484964 us
$./PP_example_parallel_optimal 1000000 4 1
The sum is: 49952518, and the elapsed time is 5340798 us
# 16 folyamat esetén már jobb az optimalizált verzió

# Az optimalizált változat nagy számú processzor esetén adna látványosabban jobb eredményt, de a linux szerveren csak 8 mag van,
# így ezt nem tudjuk demonstrálni, de a tendencia látszik (ti., hogy nagyobb folyamatszám mellett kapunk a nem optimalizáltnál 
# jobb eredményt)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  Peldaprg_n_osszead/PP_example_parallel_not_optimal.c                                                0000644 0001750 0001750 00000007575 13742006455 022766  0                                                                                                    ustar   vlewir                          vlewir                                                                                                                                                                                                                 // n (veletlenszeruen generalt, 0 és 100 kozotti) egesz szam osszeadasa (megj. 2 <= n <= MAX_N) tetszoleges usleep(u) kesleltetessel
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

// p maximalis erteke
#define MAX_P 256

// add fuggveny overloading-ja
#define add(a,b,u) ({if (u == 0) add_wo_u(a,b); else add_w_u(a,b,u);})

// veletlenszam generalasa [lower_limit es upper_limit] kozott, adott seed segitsegevel
short get_random_number(int lower_limit, int upper_limit, unsigned int *seed) {
	return (short) ((double) rand_r(seed) / (RAND_MAX + 1.0) * (upper_limit - lower_limit + 1) + lower_limit);
}

// ket egesz szam, a es b osszeadasa tetszoleges usleep(u) kesleltetessel
void add_w_u(long unsigned int *a, int b, int u) {
	usleep(u);
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
	struct timeval start, stop;
	short *numbers;
	unsigned int seed = time(NULL);
	unsigned long int res;
	unsigned long int tmp_sum;

	int pfd[2];
	pid_t pid[MAX_P];

	// bemeneti parameterek ellenorzese
	if (argc < 3) {
		printf("%s\n", "usage ./PP_example_parallel_not_optimal n m OR ./PP_example_parallel_not_optimal n m u\n\t2 <= n <= MAX_N (2^32)\n\t1 <= m <= 4\n\tu microseconds in usleep()\n");
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
	if ((m < 1) || (m > 4)) {
		printf("%s\n", "1 <= m <= 4\n");
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
	gettimeofday(&start, NULL);

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
	gettimeofday(&stop, NULL);

	// az osszeg es a futasi ido kiirasa
	printf("The sum is: %lu, and the elapsed time is %lu us\n", res, (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

	return 0;
}                                                                                                                                   Peldaprg_n_osszead/PP_example_parallel_optimal.c                                                    0000644 0001750 0001750 00000011302 13742006446 022065  0                                                                                                    ustar   vlewir                          vlewir                                                                                                                                                                                                                 // n (veletlenszeruen generalt, 0 és 100 kozotti) egesz szam osszeadasa (megj. 2 <= n <= MAX_N) tetszoleges usleep(u) kesleltetessel
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

// p maximalis erteke
#define MAX_P 256

// add fuggveny overloading-ja
#define add(a,b,u) ({if (u == 0) add_wo_u(a,b); else add_w_u(a,b,u);})

// veletlenszam generalasa [lower_limit es upper_limit] kozott, adott seed segitsegevel
short get_random_number(int lower_limit, int upper_limit, unsigned int *seed) {
	return (short) ((double) rand_r(seed) / (RAND_MAX + 1.0) * (upper_limit - lower_limit + 1) + lower_limit);
}

// ket egesz szam, a es b osszeadasa tetszoleges usleep(u) kesleltetessel
void add_w_u(long unsigned int *a, int b, int u) {
	usleep(u);
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
	struct timeval start, stop;
	short *numbers;
	unsigned int seed = time(NULL);
	unsigned long int res;
	unsigned long int tmp_sum;

	int pfd[MAX_P][2];
	pid_t pid[MAX_P];

	// bemeneti parameterek ellenorzese
	if (argc < 3) {
		printf("%s\n", "usage ./PP_example_parallel_optimal n m OR ./PP_example_parallel_optimal n m u\n\t2 <= n <= MAX_N (2^32)\n\t1 <= m <= 4\n\tu microseconds in usleep()\n");
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
	if ((m < 1) || (m > 4)) {
		printf("%s\n", "1 <= m <= 4\n");
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
	gettimeofday(&start, NULL);

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
	gettimeofday(&stop, NULL);

	// az osszeg es a futasi ido kiirasa
	printf("The sum is: %lu, and the elapsed time is %lu us\n", res, (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

	return 0;
}                                                                                                                                                                                                                                                                                                                              Peldaprg_n_osszead/PP_example_sequential.c                                                          0000644 0001750 0001750 00000004562 13742006757 020735  0                                                                                                    ustar   vlewir                          vlewir                                                                                                                                                                                                                 // n (veletlenszeruen generalt, 0 és 100 kozotti) egesz szam osszeadasa (megj. 2 <= n <= MAX_N) tetszoleges usleep(u) kesleltetessel
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

// add fuggveny overloading-ja
#define add(a,b,u) ({if (u == 0) add_wo_u(a,b); else add_w_u(a,b,u);})

// veletlenszam generalasa [lower_limit es upper_limit] kozott, adott seed segitsegevel
short get_random_number(int lower_limit, int upper_limit, unsigned int *seed) {
	return (short) ((double) rand_r(seed) / (RAND_MAX + 1.0) * (upper_limit - lower_limit + 1) + lower_limit);
}

// ket egesz szam, a es b osszeadasa tetszoleges usleep(u) kesleltetessel
void add_w_u(long unsigned int *a, int b, int u) {
	usleep(u);
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
	struct timeval start, stop;
	short *numbers;
	unsigned int seed = time(NULL);
	unsigned long int res;

	// bemeneti parameterek ellenorzese
	if (argc < 2) {
		printf("%s\n", "usage ./PP_example_sequential n OR ./PP_example_sequential n u\n\t2 <= n <= MAX_N (2^32)\n\tu microseconds in usleep()\n");
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
		printf("%s\n", "2 <= n <= MAX_N (2^32)\n");
		exit(1);
	}

	// veletlenszamok generalasa es tarolasa
	numbers = malloc(sizeof(short) * n);

	for (i = 0; i < n; i++) {
		numbers[i] = get_random_number(0,100,&seed);
		// printf("%d\n", numbers[i]);
	}
	
	// futasi ido merese, kezdeti ido elmentese
	gettimeofday(&start, NULL);

	// osszeadasok kiszamolasa
	res = 0;

	for (i = 0; i < n; i++) {
		add(&res,numbers[i],u);
	}
	
	// vegzesi ido elmentese
	gettimeofday(&stop, NULL);

	// az osszeg es a futasi ido kiirasa
	printf("The sum is: %lu, and the elapsed time is %lu us\n", res, (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

	return 0;
}                                                                                                                                              Peldaprg_n_osszead/makefile                                                                         0000644 0001750 0001750 00000001035 13732427473 015776  0                                                                                                    ustar   vlewir                          vlewir                                                                                                                                                                                                                 all: sequatial_add paralellel_add_not_optimal paralellel_add_optimal

sequatial_add: PP_example_sequential.c
	gcc -o PP_example_sequential PP_example_sequential.c -Wall

paralellel_add_not_optimal: PP_example_parallel_not_optimal.c
	gcc -o PP_example_parallel_not_optimal PP_example_parallel_not_optimal.c -lm -Wall

paralellel_add_optimal: PP_example_parallel_optimal.c
	gcc -o PP_example_parallel_optimal PP_example_parallel_optimal.c -lm -Wall

clean:
	rm PP_example_sequential PP_example_parallel_not_optimal PP_example_parallel_optimal
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   