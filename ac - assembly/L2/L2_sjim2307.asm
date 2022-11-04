; Széri József - sjim2307
; 514/2

; Labor: 2

;Írjunk meg egy-egy ASM alprogramot (függvényt, eljárást) 
;32 bites, előjeles egész (decimális), 
;illetve 32 bites, pozitív hexa számok beolvasására és kiírására.

; Compile:
; nasm -f win32 L2\L2_sjim2307.asm
; nlink L2\L2_sjim2307.obj -lmio -lio -o L2\L2_sjim2307.exe
; actest L2 L2\L2_sjim2307.exe

%include 'mio.inc'
%include 'io.inc'

global main

section .text
beolvas_decimal32:
    ;AL                                   0000 0000 - FF
    ;AX                         0000 0000 0000 0000 - FFFF
    ;EAX    0000 0000 0000 0000 0000 0000 0000 0000 - FFFF FFFF
    
    ;A fügvény EAX-be olvassa be az értéket.

    ;------ Ismert bug-ok: ------
    ;1. A backspace nem törli ki a minusz jel számítást edx-ből.
    ;2. MINUSZ jelet csak egyszer lehet beírni, viszt bármikor be lehet irni a program futása során. Ez azt eredményezi, hogy MINUSZ jel után ki lesznek vonva a számok az előzőből.
    ;  Lényegében számológépként dolgozik, miközebn 10-el szoroz és furcsa eredményt kapunk. pl 1-2 = 8 -> 1*10 = 10 - 2 = 9
    ;----------------------------


    push    ebx                             ;Kell az ebx szam felepitesre
    push    ecx                             ;Kell az ecx szorzo tarolasara, hogy ne mindig push / pop oljuk szorzaskor imullal
    push    edx                             ;Itt tároljuk, hogy a szám negatív, vagy pozitív - 0 pozitív, 1 negatív

    .bemenet_szoveg:
        mov     eax, str_decimalis_beolvasas
        call    mio_writestr

    xor     eax, eax                        ;Lenullánzi az eax jelenlegi értékét.
    xor     ebx, ebx                        ;Ugyanugy az ebx is 0 kell legyen
    mov     ecx, 10                         ;szorzas miatt.
    mov     edx, 0                          ;A beolvasásra váró szám alapértelmezett pozitív


    .uj_karakter:
        call    mio_readchar

        ;ENTER - eseten véget ér a beolvasás
        cmp     al, 13
        je      .end

        ;Karakter kiiratasa
        call    mio_writechar
        
        ;MINUSZ - negativ szamok beolvasasank jelzese.
        cmp     al, '-'
        je      .minusz_jel

        ;BACKSPACE
        cmp     al, 8
        je      .backspace

        ;Leellenőrizni, hogy a karakter szám
        cmp     al, '0'                     ;48
        jl      .hiba
        cmp     al, '9'                     ;57
        jg      .hiba

        ;Szám esetén:
        ;Szorozzuk az eredményt 10-el majd hozzáadjuk az beolvasott számjegyet.
        imul    ebx, ecx ; ebx * 10
        jo      .hiba                       ;Overflow esetén hiba

        sub     eax, '0'                    ;Ki kell vonni a 0 karakter értékét, ezzel karakter kódból számmá konvertáljuk.

        ;Pozitív eredményhez számjegy hozzáadás
        cmp     edx, 0
        je      .pozitiv

        ;Negatív eredményhez számjegy hozzáadás
        cmp     edx, 1
        je      .negativ

        ;Ha az edx más értéket vett fel valamiért, akkor hiba lépett fel.
        jmp     .hiba


    .minusz_jel:
        ;Ha már volt beírva egy minusz jel, akkor egy új minusz jel hibás
        cmp     edx, 1
        je      .hiba

        mov     edx, 1                      ; Jelzi, hogy a szám negatív.
        jmp     .uj_karakter
    

    .negativ:
        ;Negatív számok esetén, számjegy hozzáadás.

        sub     ebx, eax                    ;ki kell vonni ebx-ből a számjegyet
        jo      .hiba                       ;Overflow esetén hiba, ha a szorzás, pont nem fogta meg.
        jmp     .uj_karakter

    
    .pozitiv: 
        ;Pozitív számok esetén, számjegy hozzáadás.

        add     ebx, eax                    ;hozzá kell adni a számjegyet.
        jo      .hiba                       ;Overflow esetén hiba, ha a szorzás, pont nem fogta meg.
        jmp     .uj_karakter


    .backspace:
        ;Mivel a backspace karakter már ki volt irva, ezért felül kell irni egy üres karakterrel a jelenlegi dolgot,
        ;Majd egy új backspace karakterrel helyére helyre tesszük a szöveg mutatót? a következő szám beírásnak.
        mov     al, ' '
        call    mio_writechar
        mov     al, 8
        call    mio_writechar

        push    edx                         ; Negativ szamjegy jelzo kell az osztashoz.

        ;Osztani a szamot 10-el. Igy eltüntetjük a kitörölt számot. (pontosabban edx-be kerül)
        ;EBX értékét kellene csökkenteni -> bemásoljuk és vissza eax-be.
        mov     eax, ebx
        cdq
        idiv    ecx                         ; Osztjuk eax-et 10-el
        mov     ebx, eax
        xor     eax, eax

        pop     edx                         ; Visszaszerezni a negativ szamjegy jelzot

        ;Uj karaktert kell bekerni.
        jmp    .uj_karakter


    .hiba:
        ;Hiba szöveg kiiratása
        mov     eax, str_hiba
        call    mio_writeln
        call    mio_writestr
        call    mio_writeln

        ;Ujrakezdjük a beolvasást
        xor     eax, eax
        xor     ebx, ebx
        xor     edx, edx
        jmp     .bemenet_szoveg


    .end:
        ;Betesszük a számot eax-be.
        mov     eax, ebx

        ;Visszaszerezzük az értékekek stackből.
        pop     edx
        pop     ecx
        pop     ebx

        ret


kiir_decimal32:
    ;A fügvény EAX-ből írja ki a számot.
    
    ;Szöveg kiírása
    push    eax
    mov     eax, str_decimalis_kiiras
    call    mio_writestr
    pop     eax

    ;Értékek elmentése
    push    eax                             ;Az eax értéke ne változzon a fügvény végére.
    push    ebx                             ;ebx-el osztunk meg maradekot szamolunk
    push    ecx                             ;Szamjegy szamlalo
    push    edx                             ;Ide kerül majd számjegyenként az eax

    ;Regiszterek beállítása
    mov     ebx, 10                         ;Osztó
    mov     ecx, 0                          ;Számjegy számláló


    ;Pozitív és negatív számokra egyaránt működik
    .szamjegy_lebontas:
        cdq
        idiv    ebx
        push    edx                         ;A maradekot betenni a stackbe, hogy jó legyen a beolvasás

        inc     ecx                         ;Növelni a számjegyek számát.

        cmp     eax, 0
        jne     .szamjegy_lebontas          ;Addig ismételni ameddig a számjegy nem 0


    ;Meg kell szerezni a stack legfelső elemét, pop majd push-al nem rontjuk el a stack sorrendjét.
    pop     eax
    push    eax

    ;Ha a szám negatív, akkor másként iratjuk ki
    test    eax,eax
    js      .negativ_szam


    ;++++++++++++++
    ;Pozitiv kiírás
    ;++++++++++++++
    .karakter_kiiras_pozitiv:
        pop     eax                         ;Kiszedni a stackben levő számjegyet
        add     eax, '0'                    ;A számjegyet karakter kóddá változtatni
        call    mio_writechar               ;Kiiratni a számjegyet

        loop    .karakter_kiiras_pozitiv    ;Addig ismételni amennyi számjegy van
    

    ;A kiírás végén .end-hez ugrunk.
    jmp    .end 


    ;--------------
    ;Negatív kiírás
    ;--------------
    .negativ_szam:
        ;Minusz jel kiírása
        push    eax
        mov     al, '-'
        call    mio_writechar
        pop     eax

    .karakter_kiiras_negativ:
        pop     eax                         ;Kiszedni a stackben levő számjegyet

        ;Komplementer kódolás
        NOT     eax
        inc     eax

        add     eax, '0'                    ;A számjegyet karakter kóddá változtatni
        call    mio_writechar               ;Kiiratni a számjegyet

        loop    .karakter_kiiras_negativ    ;Addig ismételni amennyi számjegy van


    .end:
        ;Visszaszerezzük az értékekek stackből.
        pop     edx
        pop     ecx
        pop     ebx
        pop     eax

        ret


beolvas_hexa:
    ;AL                                   0000 0000 - FF
    ;AX                         0000 0000 0000 0000 - FFFF
    ;EAX    0000 0000 0000 0000 0000 0000 0000 0000 - FFFF FFFF
    
    ;A fügvény EAX-be olvassa be az értéket.

    push    ebx                             ;Kell az ebx szam felepitesre
    push    ecx                             ;Számláló, max 8 szám lehet beírva
    xor     ebx, ebx
    xor     ecx, ecx

    .bemenet_szoveg:
        ;Szöveg kiiratás
        mov     eax, str_hexa_beolvasas
        call    mio_writestr
        mov     eax, str_hexa_prefix
        call    mio_writestr


    .uj_karakter:
        xor     eax, eax                    ;Le kell nullázni hibák elkerülésére
        call    mio_readchar

        ;ENTER - eseten véget ér a beolvasás
        cmp     al, 13
        je      .end

        ;BACKSPACE
        cmp     al, 8
        je      .backspace

        ;Karakter kiiratasa
        call    mio_writechar

        ;MAXIMÁLIS HOSSZ
        cmp     ecx, 8                      ;Ha 8 karakter hosszú a hexa számjegy, akkor már nem lehet többet beleírni.
        je      .hiba

        ;--------Szám Ellenrőzések--------
        ;(ASCII) Legkissebtől kezdbe, legnagyobbig haladva, megnézzük, hogy benne van e a felső határban.
        ;Ha igen, akkor le kell tesztelni, hogy az alsó határban is benne van, különben hiba.
        ;---------------------------------
        cmp     al, '9'                     ;57
        jle     .szamjegy
        cmp     al, 'F'                     ;70
        jle     .nagy_betu
        cmp     al, 'f'                     ;102
        jle     .kis_betu

        jmp     .hiba                       ;Minden más esetben helytelen karakter.


    .szamjegy:
        cmp     al, '0'
        jl      .hiba

        shl     ebx, 4                      ; 4-el eltoljuk az ebx-et
        sub     eax, '0'                    ; megszerezzük a számjegy értékét
        add     ebx, eax                    ; hozzáadjuk ebx-hez, garantáltan 4 biten elfér

        inc     ecx                         ;Karakter számláló növelése
        jmp     .uj_karakter

    
    .nagy_betu:
        cmp     al, 'A'
        jl      .hiba

        shl     ebx, 4                      ; 4-el eltoljuk az ebx-et
        sub     eax, 'A'                    ; megszerezzük a betü értékét
        add     eax, 10                     ; hozzá kell adni 10-et, mert 10 a legkisebb szám (A)
        add     ebx, eax                    ; hozzáadjuk ebx-hez, garantáltan 4 biten elfér

        inc     ecx                         ;Karakter számláló növelése
        jmp     .uj_karakter
    

    .kis_betu:
        cmp     al, 'a'
        jl      .hiba

        shl     ebx, 4                      ; 4-el eltoljuk az ebx-et
        sub     eax, 'a'                    ; megszerezzük a betü értékét
        add     eax, 10                     ; hozzá kell adni 10-et, mert 10 a legkisebb szám (a)
        add     ebx, eax                    ; hozzáadjuk ebx-hez, garantáltan 4 biten elfér

        inc     ecx                         ;Karakter számláló növelése
        jmp     .uj_karakter

    
    .backspace:
        cmp     ecx, 0                      ;Ne tudjuk kitörölni olyan szöveget, amit nem mi irtunk
        je      .uj_karakter
        
        mov     al, 8                       ;Nem volt kiírva a backspace, hogy ne menjünk vissza, ha nem lenne szabad
        call    mio_writechar
        mov     al, ' '
        call    mio_writechar
        mov     al, 8
        call    mio_writechar

        dec     ecx                         ;Csökken a karakter számláló
        shr     ebx, 4                      ;Visszavisszük a beolvasható poziciót

        ;Uj karaktert kell bekerni.
        jmp    .uj_karakter


    .hiba:
        ;Hiba szöveg kiiratása
        mov     eax, str_hiba
        call    mio_writeln
        call    mio_writestr
        call    mio_writeln

        ;Ujrakezdjük a beolvasást
        xor     eax, eax
        xor     ebx, ebx
        xor     ecx, ecx
        jmp     .bemenet_szoveg


    .end:
        ;Betesszük a számot eax-be.
        mov     eax, ebx

        ;Visszaszerezzük az értékekek stackből.
        pop     ecx
        pop     ebx

        ret


kiir_hexa:
    ;A fügvény EAX-ből írja ki a számot hexadecimális formában

    ;Szöveg kiírása
    push    eax
    mov     eax, str_hexa_kiiras
    call    mio_writestr
    mov     eax, str_hexa_prefix
    call    mio_writestr
    pop     eax

    ;Értékek elmentése
    push    eax                             ;eax eredeti értékének elmentése
    push    ebx                             ;hexa szamjegyek? tárolása
    push    ecx                             ;Számláló
    push    edx

    mov     ecx, 8                          ;8 karaktert kell beolvasni

    ;--KOMPLEMENTER ÁTALAKÍTÁS NEGATÍV SZÁMOK ESETÉN--
    test    eax, eax
    jns     .felbontas

    NOT     eax
    inc     eax
    ;--------------------------------------------------

    .felbontas:
        mov     ebx, 0xF                    ;.... 0000 1111
        and     ebx, eax                    ;Megszerezzük a számot az utolsó 4 bitről.
        push    ebx                         ;Elmentjük a számot

        shr     eax, 4                      ;Eltoljuk 4-el az eax-et, hogy megkapjuk a következő számot
        loop    .felbontas


    mov     ecx, 8                          ;8 karaktert kell kiírni
    .kiiras:
        pop     eax                         ;Kiszedjük a számot a stackből.

        cmp     eax, 10                     
        jl      .szamjegy                   ;Ha ebx < 10(1010) akkor számjegyről van szó.
        jmp     .betu                       ;Ellenkező esetben betűről


    .szamjegy:
        add     eax, '0'                    ; Számjegy ASCII kóddá alakítása
        call    mio_writechar

        jmp     .kiiras_veg
    

    .betu:
        sub     eax, 10                     ;Ahhoz, hogy A-F karaktert kapjunk, ki kell vonni 10-et. A=10
        add     eax, 'A'
        call    mio_writechar

        jmp     .kiiras_veg


    .kiiras_veg:
        loop    .kiiras


    .end:
        ;Visszaszerezzük az értékekek stackből.
        pop     edx
        pop     ecx
        pop     ebx
        pop     eax

        ret


main:
    call    beolvas_decimal32
    call    mio_writeln

    call    kiir_decimal32
    call    mio_writeln

    call    beolvas_hexa
    call    mio_writeln

    call    kiir_hexa
    
    ret


section .data
    str_hiba  db "Hiba: Helytelen bemenet! Probald Ujra!", 0
    str_decimalis_beolvasas  db "[Beolvasas]Decimalis (32bit) >> ", 0
    str_decimalis_kiiras db "[Kiiras]Decimalis (32bit) = ", 0
    str_hexa_beolvasas  db "[Beolvasas]Hexa (32bit) >> ", 0
    str_hexa_kiiras db "[Kiiras]Hexa (32bit) = ", 0
    str_hexa_prefix db "0x", 0