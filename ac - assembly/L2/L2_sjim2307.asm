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


    push    ebx ;Kell az ebx szam felepitesre
    push    ecx ;Kell az ecx szorzo tarolasara, hogy ne mindig push / pop oljuk szorzaskor imullal
    push    edx ;Itt tároljuk, hogy a szám negatív, vagy pozitív - 0 pozitív, 1 negatív

    xor     eax, eax ;Lenullánzi az eax jelenlegi értékét.
    xor     ebx, ebx ;Ugyanugy az ebx is 0 kell legyen
    mov     ecx, 10  ;szorzas miatt.
    mov     edx, 0   ;A beolvasásra váró szám alapértelmezett pozitív


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
        cmp     al, '0' ;48
        jl      .hiba
        cmp     al, '9' ;57
        jg      .hiba

        ;Szám esetén:
        ;Szorozzuk az eredményt 10-el majd hozzáadjuk az beolvasott számjegyet.
        imul    ebx, ecx ; ebx * 10
        jo      .hiba ; Overflow esetén hiba

        sub     eax, '0' ; Ki kell vonni a 0 karakter értékét, ezzel karakter kódból számmá konvertáljuk.

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

        mov     edx, 1 ; Jelzi, hogy a szám negatív.
        jmp     .uj_karakter
    

    .negativ:
        ;Negatív számok esetén, számjegy hozzáadás.

        sub     ebx, eax ;ki kell vonni ebx-ből a számjegyet
        jo      .hiba ;Overflow esetén hiba, ha a szorzás, pont nem fogta meg.
        jmp     .uj_karakter

    
    .pozitiv: 
        ;Pozitív számok esetén, számjegy hozzáadás.

        add     ebx, eax ;hozzá kell adni a számjegyet.
        jo      .hiba ;Overflow esetén hiba, ha a szorzás, pont nem fogta meg.
        jmp     .uj_karakter


    .backspace:
        ;Mivel a backspace karakter már ki volt irva, ezért felül kell irni egy üres karakterrel a jelenlegi dolgot,
        ;Majd egy új backspace karakterrel helyére helyre tesszük a szöveg mutatót? a következő szám beírásnak.
        mov     al, ' '
        call    mio_writechar
        mov     al, 8
        call    mio_writechar

        push    edx ; Negativ szamjegy jelzo kell az osztashoz.

        ;Osztani a szamot 10-el. Igy eltüntetjük a kitörölt számot. (pontosabban edx-be kerül)
        ;EBX értékét kellene csökkenteni -> bemásoljuk és vissza eax-be.
        mov     eax, ebx
        cdq
        idiv    ecx ; Osztjuk eax-et 10-el
        mov     ebx, eax
        xor     eax, eax

        pop     edx; Visszaszerezni a negativ szamjegy jelzot

        ;Uj karaktert kell bekerni.
        jmp    .uj_karakter


    .hiba:
        ;Hiba szöveg kiiratása
        mov     eax, hiba
        call    mio_writeln
        call    mio_writestr

        ;Ujrakezdjük a beolvasást
        xor     eax, eax
        xor     ebx, ebx
        xor     edx, edx
        jmp     .uj_karakter


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


main:
    call    beolvas_decimal32
    call    mio_writeln
    call    kiir_decimal32

    ret


section .data
    hiba  db "Hiba: Helytelen bemenet! Uj bemenet: ", 0