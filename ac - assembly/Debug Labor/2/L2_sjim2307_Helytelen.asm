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

    push    ebx ;Kell az ebx szam felepitesre
    push    ecx ;Kell az ecx szorzo tarolasara, hogy ne mindig push / pop oljuk szorzaskor imullal
    push    edx ;Osztás miatt

    xor     eax, eax ;Lenullánzi az eax jelenlegi értékét.
    xor     ebx, ebx ;Ugyanugy az ebx is 0 kell legyen
    mov     ecx, 10  ;szorzas miatt.

    .uj_karakter:
        call    mio_readchar

        ;ENTER eseten véget ér a beolvasás
        cmp     al, 13
        je      .end

        ;Kiirni a beirt karaktert
        call    mio_writechar
        
        ;Backspace eset lekezelese
        cmp     al, 8
        je      .backspace

        ;Leellenőrizni, hogy a beirt karakter szám.
        ;Ha a beirt szám nem számjegy, akkor hiba lépett fel.
        cmp     al, '0' ;48
        jl      .hiba
        cmp     al, '9' ;57
        jg      .hiba

        ;Ha szam akkor szorozzuk a jelenlegit 10el es hozzaadjuk a beolvasottat
        imul    ebx, ecx ; ebx * 10
        sub     eax, '0' ; Ki kell vonni a 0 karakter értékét, ezzel karakter kódból, számmá konvertáljuk.
        add     ebx, eax ; eax-ban csak al értéke található, és ezért működni fog rendesen

        jmp     .uj_karakter

    .backspace:
        ;Mivel a backspace karakter már ki volt irva, ezért felül kell irni egy üres karakterrel a jelenlegi dolgot,
        ;Majd egy új backspace karakterrel helyére helyre tesszük a szöveg mutatót? a következő szám beírásnak.
        mov     al, ' '
        call    mio_writechar
        mov     al, 8
        call    mio_writechar

        ;Osztani a szamot 10-el. Igy eltüntetjük a kitörölt számot. (pontosabban edx-be kerül)
        ;EBX értékét kellene csökkenteni -> bemásoljuk és vissza eax-be.
        mov     eax, ebx
        cdq
        idiv    ecx ; Osztjuk eax-et 10-el
        mov     ebx, eax

        ;Uj karaktert kell bekerni.
        jmp    .uj_karakter

    .hiba:
        ;ide hibakezelest

    .end:
        ;Betesszük a számot eax-be.
        mov     eax, ebx

        ;Visszaszerezzük az értékekek stackből.
        pop     edx
        pop     ecx
        pop     ebx

        ret







main:
    call    beolvas_decimal32
    call    mio_writeln
    call    io_writeint
    ret