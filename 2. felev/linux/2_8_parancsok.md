# 2.8 laborfeladat - 2023

- név: Széri József:
- azonosító: sjim2307

## Feladatok

### A)

- Hozza létre a következő katalógusszerkezetet, majd listázza azt.

```text
zoldseg
      |
      |- mas
      |
      |- nyari
      |      |- burgonya
      |      |- kaposzta
      |
      |- oszi
            |- banan
            |- cukorrepa
            |- paprika
            |- retek

```

```bash
[sjim2307@linux labor2]$ mkdir -p zoldseg/mas zoldseg/nyari/burgonya zoldseg/nyari/kaposzta
zoldseg/oszi/banan zoldseg/oszi/cukorrepa zoldseg/oszi/paprika zoldseg/oszi/retek
[sjim2307@linux labor2]$ tree
.
├── 2_8_parancsok.md
└── zoldseg
    ├── mas
    ├── nyari
    │   ├── burgonya
    │   └── kaposzta
    └── oszi
        ├── banan
        ├── cukorrepa
        ├── paprika
        └── retek
```

- Hozza létre a következő szöveges állományokat: _zoldseg/nyari/burgonya/etelek_, _zoldseg/mas/peldak_.

```bash
[sjim2307@linux labor2]$ cat > zoldseg/nyari/burgonya/etelek
[sjim2307@linux labor2]$ cat > zoldseg/mas/peldak
```

- Az _etelek_ file-ba írjon külön sorokba 5 olyan ételt, amely burgonya felhasználásával készül.   
A _peldak_ file-ba írjon külön sorokba legalább 3 más zöldségnevet.   

```bash
[sjim2307@linux labor2]$ cat > zoldseg/nyari/burgonya/etelek
Szalmakrumpli
Krumplileves
Törtkrumpli
Krumplikenyér
Rakottkrumpli
Rakottpaprika
[sjim2307@linux labor2]$ cat > zoldseg/mas/peldak
Saláta
Paradicsom
Hagyma
```

- Törölje a _banan_ katalógust. 

```bash
[sjim2307@linux labor2]$ rmdir zoldseg/oszi/banan/
```

- Készítsen másolatot
   - a _zoldseg/oszi/retek_ katalógusról a _zoldseg/nyari_ katalógusba
   - a _zoldseg/oszi/paprika_ katalógusról a _zoldseg/nyari_ katalógusba

```bash
[sjim2307@linux labor2]$ cp -r zoldseg/oszi/retek/ zoldseg/nyari/
[sjim2307@linux labor2]$ cp -r zoldseg/oszi/retek/ zoldseg/nyari/
```

- Helyezze át a _zoldseg/nyari/burgonya_ katalógust a _zoldseg/oszi_ katalógusba.

```bash
[sjim2307@linux labor2]$ mv zoldseg/nyari/burgonya/ zoldseg/oszi/
```

- Kerestesse meg a _zoldseg_ katalógusban azokat a katalógusneveket (figyelem, a file-neveket ne!), amelyek "k" betűvel végződnek.

```bash
[sjim2307@linux labor2]$ find zoldseg/ -name "*k" -type d
zoldseg/nyari/retek
zoldseg/oszi/retek
```

- Készítsen hard linket a _zoldseg/oszi/burgonya_ katalógusban szereplő _etelek_ fájlra a _zoldseg_ katalógusban.

```bash
[sjim2307@linux labor2]$ ln zoldseg/oszi/burgonya/etelek zoldseg/
```

- Készítsen egy _etelek_ nevű szöveges állományt a _zoldseg/nyari/paprika_ katalógusba is és írja bele legalább 4 olyan ételnek a nevét, amely paprikát is tartalmaz, majd listáztassa ki a különböző sorokat a két _etelek_ állományból.

```bash
[sjim2307@linux labor2]$ cat > zoldseg/nyari/paprika/etelek
Paprikaleves
Rakottpaprika
Kirstálypaprika
Húsospaprika
Megpaprikásított leves
Rakottpaprika
[sjim2307@linux labor2]$ sort zoldseg/etelek zoldseg/nyari/paprika/etelek | uniq
Húsospaprika
Kirstálypaprika
Krumplikenyér
Krumplileves
Megpaprikásított leves
Paprikaleves
Paprikaskrumpli
Rakottkrumpli
Rakottpaprika
Szalmakrumpli
Törtkrumpli
```

- A _zoldseg/mas/peldak_ szöveges állományt tegye olvashatóvá mindenki számára.

```bash
[sjim2307@linux labor2]$ chmod a+r zoldseg/mas/peldak
```

- Mennyi helyet foglal a merevlemezen (bájtokban) a _zoldseg_ katalógus? Az alkatalógusok mérete ne legyen kilistázva. 

```bash
[sjim2307@linux labor2]$ du -b zoldseg/ -s
45266   zoldseg/
```

- Listázza ki a _zoldseg/mas/peldak_ szöveges állomány utolsó két sorát.

```bash
[sjim2307@linux labor2]$ tail -n 2 zoldseg/mas/peldak
Paradicsom
Hagyma
```

- Adjon hozzá még két burgonyás ételt a _zoldseg/oszi/burgonya/etelek_ állományhoz (ne használjon szövegszerkesztőt!), majd számoltassa meg a _zoldseg/etelek_ file-ban szereplő sorok számát.

```bash
[sjim2307@linux labor2]$ cat >> zoldseg/oszi/burgonya/etelek
Nagyburgonya porkolt
Kisburgonya porkolt
[sjim2307@linux labor2]$ wc -l zoldseg/etelek
8 zoldseg/etelek
```


### B)

- Írassa ki a saját felhasználónevét és azonosítóját, valamint azoknak a csoportoknak a nevét és azonosítóját, amelyekhez tartozik.

```bash
[sjim2307@linux labor2]$ id sjim2307
uid=1036857353(sjim2307) gid=1036857335(gr514) groups=1036857335(gr514)
```

- Törölje le a képernyő tartalmát.

```bash
[sjim2307@linux labor2]$ clear
```

- Listázza ki a múlt pénteken 14 óra előtt bejelentkezett utolsó 7 felhasználó adatait (a laborban megoldandó). 

```bash
[sjim2307@linux labor2]$ last -n 7 -t "2023-03-19 14:00"
jagi4420 pts/26       172.30.111.195   Sun Mar 19 13:24    gone - no logout
jagi4420 pts/14       172.30.111.195   Sun Mar 19 13:17    gone - no logout
nmch0015 pts/18       172.30.0.31      Sun Mar 19 12:38    gone - no logout
eech0000 pts/14       172.30.0.31      Sun Mar 19 12:26 - 12:58  (00:32)
lauraruf pts/29       172.30.120.8     Sun Mar 19 12:15    gone - no logout
drch0020 pts/2        172.30.0.31      Sun Mar 19 12:12    gone - no logout
eech0000 pts/28       172.30.0.31      Sun Mar 19 12:03 - 12:19  (00:16)
```

- A passwd adatbázisból keresse ki a legutoljára bejelentkezett felhasználónak megfelelő bemenetet. Megj. a legutoljára bejelentkezett felhasználót meghatározhatjuk egy külön paranccsal, majd annak a kimenetét kell felhasználni. Megpróbálhatjuk egyetlen (összetett) paranccsal megoldani. Arra is vigyázzunk, hogy ha az legutóbbi bejelentkező felhasználóneve 8-nál több karakterből áll, akkor is jelenjen meg a teljes felhasználónév. (getent parancs, a laborban megoldandó).

```bash
[sjim2307@linux ~]$ getent passwd `last | head -n 1 | cut -c 1-8`
krim2255:*:1036857301:1036857273:krim2255:/home/users/stud/licenta/1/512/krim2255:/bin/bash
```

- Vizsgálja meg, hogy elérhető-e a _sapientia.ro_ szerver. Csak 5 elérési próbálkozást engedélyezzen.

```bash
[sjim2307@linux labor2]$ ping -c 5 www.sapientia.ro
ping: socket: Address family not supported by protocol
PING www.sapientia.ro (146.70.77.146) 56(84) bytes of data.
64 bytes from email.sapientia.ro (146.70.77.146): icmp_seq=1 ttl=55 time=7.17 ms
64 bytes from email.sapientia.ro (146.70.77.146): icmp_seq=3 ttl=55 time=9.73 ms
64 bytes from email.sapientia.ro (146.70.77.146): icmp_seq=4 ttl=55 time=7.01 ms
64 bytes from email.sapientia.ro (146.70.77.146): icmp_seq=5 ttl=55 time=7.01 ms

--- www.sapientia.ro ping statistics ---
5 packets transmitted, 4 received, 20% packet loss, time 4033ms
rtt min/avg/max/mdev = 7.005/7.728/9.729/1.156 ms
```

- Listázza ki a host nevének rövid változatát.

```bash
[sjim2307@linux labor2]$ hostname -s
linux
```

- Listázza az _sealion.risc.uni-linz.ac.at_ ip címét.

```bash
[sjim2307@linux labor2]$ host sealion.risc.uni-linz.ac.at
sealion.risc.uni-linz.ac.at has address 193.170.37.52
sealion.risc.uni-linz.ac.at mail is handled by 10 mx1.risc.uni-linz.ac.at.
```

- Listázza ki az aktuális dátumot és rendszeridőt, a következő példának megfelelően:   
Pl. 2020.02.10.     (16:55:53)  
__Megjegyzés:__ A formátum megadását idézőjelek közé kell írni, különben a szóközök miatt nem egy paraméternek fogja értelmezni.

```bash
[sjim2307@linux labor2]$ date +"%Y.%m.%d."$'\t'"(%T)"
2023.03.21.     (15:51:52)
```

- Írassa ki, hogy mióta fut a rendszer.

```bash
[sjim2307@linux labor2]$ uptime -s
2023-02-08 08:06:20
```

- Írassa ki az operációs rendszermag (kernel) kiadását (release). 

```bash
[sjim2307@linux labor2]$ uname -r
5.14.0-162.12.1.el9_1.x86_64
```
