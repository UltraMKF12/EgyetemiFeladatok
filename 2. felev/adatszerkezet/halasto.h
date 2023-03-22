#ifndef HALASTO_H_INCLUDED
#define HALASTO_H_INCLUDED

/***********************************************************************************
Egy ismeros halastavakat szeretne menedzselni. Mi kell a hatter-adatkezelest biztositsuk, 
o intezi majd a menedzsmenti feluletet. Ez a header-allomany tartalmazza a specifikacioknak
megfeleloen az implementalando muveleteket.  
***********************************************************************************/

///FONTOS: a tipus (struct) kibovitheto/atalakithato ha valakinek jo otlete van!
typedef struct Halasto {
    int n,m;    /// a to meretei, 1<=n,m,<=1000
    int ** to;  /// a to, az elem 0, ha nincs hal, kulonben a fajta szama (max 100 fajta lehetseges
    int db;     ///halak szama a toban
	int fajtak_db;    ///fajtak szama a toban
	int fajtak[101];  ///fajtak eloszlasa a toban
} Halasto;

/// A modul hasznalatahoz a foprogrambol meg kell hivni egyszer a veletlenszam-generator inicializalojat
void Init();

///Letrehozas
Halasto* Create(int, int);  		   ///ures to
Halasto* CreateFromFile(const char *); ///Az allomany szerkezete: n m <to>, a halak mar benne vannak 
Halasto* CreateWild(int, int); 		   ///vad-tavat keszit: a ket parameter a to merete legyen, 
									   ///a halak veletlenszeruen helyezkednek el benne
//Felszabditas
void Destroy(Halasto*);

///Muveletek
void PutHal(Halasto*, int, int, int);  ///Halat telepitunk a toba adott helyre
                                       ///parameterek: sor, oszlop, fajta
int GetHal(Halasto*, int, int);        ///Nem horgaszmuvelet, a hal benne marad a toban
int GetSzelesseg(Halasto*);
int GetHosszusag(Halasto*);
int FajtakSzama(Halasto*);
void FajtaElofordulasa(Halasto*);      ///kiirja azon elofordulasi szamokat, amelyek 0-nal nagyobbak
Halasto* Atont(Halasto*, Halasto*);    ///Atont egy tavat a masikba, mit mibe, ha nem fernek at a halak,
                                       ///akkor a fennmarado halakat eltunteti,
                                       ///a befero halak a masodik to szabad helyeire kerulnek
									   ///visszateritesi ertek: B
int SzabadAHely(Halasto*, int, int);   ///szabad-e a jelzett hely

///Horgaszmuveletek - a kifogott halak nem maradnak a toban
int GetHalKezdo(Halasto*);  ///Kezdo horgasz, veletlenszeruen horgaszik az egesz toban
int GetHalAdvanced(Halasto*, int, int, int, int); ///Halado horgasz, celzottan horgaszik adott teglalap alaku teruletem
                                                  ///parameterek: kezdosor, vegsosor, kezdooszlop, vegsooszlop
///Kiirasok
void StatKezdo(Halasto*); ///Hal-elofordulasi statisztika fajtak szerint, a teljes toban, csak a letezo halfajtak jelenjenek meg
void StatHalado(Halasto*,int,int,int,int); ///Hal-elofordulasi statisztika fajtak szerint, csak a letezo halfajtak jelenjenek meg
                                           ///parameterek: kezdosor, vegsosor, kezdooszlop, vegsooszlop
void PrintH(Halasto*);

#endif // HALASTO_H_INCLUDED
