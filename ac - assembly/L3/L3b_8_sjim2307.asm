; Széri József - sjim2307
; 514/2

; Labor: 3
; Feladat: b8

;Keszítsünk assembly programot (NASM), amely beolvas három előjel nélküli egész számot 
;(használjuk a hexa olvasás függvényt) 32 bites egészként, kiírja a felhasznált szabályt, 
;mint üzenetet, és a beolvasott értékeket, mint 32 bites bináris egészeket, külön soronként, 
;majd előállítja és végül kiírja bináris formában a művelet eredményét, 
;ami szintén egy 32 bites egész szám.

;8. A[8:7] OR 01, A[7:5] AND 010, 1, B[11:11] AND A[23:23], A[26:6], B[12:9] + A[31:28]

; Compile:
; nasm -f win32 L3\L3b_8_sjim2307.asm
; nlink L3\L3b_8_sjim2307.obj -lmio -o L3\L3b_8_sjim2307.exe
; actest L3b_8 L3\L3b_8_sjim2307.exe

%include 'mio.inc'

global main

section .text
writebin:
    ;EAX kiiratása 32 bites bináris alakban
    ;0111 1011 0101 0100 1101 0010 1010 1011
    ;8 csoport, csoportonként 4 számjegy
    ;Alternativkén lehetne használni ADC-t osztály helyett

    ;Szöveg kiírása
    ;push    eax
    ;mov     eax, str_binaris_kiiras
    ;call    mio_writestr
    ;pop     eax


    push    eax                                     ;Itt van a szam
    push    ebx
    push    ecx                                     ;Szamlalo
    push    edx

    mov     ecx, 32                                 ;32 bit betevese stackbe
    mov     ebx, 2                                  ;Osztasi maradek szamlalasara

    .beolvasas:
        ;32-bit beolvasasa
        xor     edx, edx
        div     ebx
        push    edx                                 ;1 vagy 0 lehet
        
        loop    .beolvasas
    
    mov     ecx, 32                                 ;32 bitet irunk ki.
    mov     ebx, 4                                  ;4 bitenként space ellenőrzés
    .kiiras:
        ;Kiirni stackből a biteket
        pop     eax
        add     eax, '0'
        call    mio_writechar

        ;4 bitenként kell egy space karakter
        mov     eax, ecx
        xor     edx, edx
        div     ebx
        cmp     edx, 1
        jne     .kiiras_veg

        mov     al, ' '
        call    mio_writechar
        
    .kiiras_veg:
        loop    .kiiras

    .end:
        ;Értékek visszatérítése a stackből
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


main:
    ;Számok beolvasása
    call    beolvas_hexa
    call    mio_writeln
    mov     [a], eax
    
    call    beolvas_hexa
    call    mio_writeln
    mov     [b], eax

    call    beolvas_hexa
    call    mio_writeln
    mov     [c], eax

    
    ;Szabály és számok kiiratása
    call    mio_writeln
    mov     eax, str_szabaly
    call    mio_writestr
    call    mio_writeln

    mov     eax, str_a
    call    mio_writestr
    mov     eax, [a]
    call    writebin
    call    mio_writeln

    mov     eax, str_b
    call    mio_writestr
    mov     eax, [b]
    call    writebin
    call    mio_writeln

    mov     eax, str_c
    call    mio_writestr
    mov     eax, [c]
    call    writebin
    call    mio_writeln

    ;A[8:7] OR 01, A[7:5] AND 010, 1, B[11:11] AND A[23:23], A[26:6], B[12:9] + A[31:28]
    xor     edx, edx                        ;Itt tároljuk az eredményt

    ;A[8:7] OR 01  //  31,30 bit
    mov     eax, [a]
    shr     eax, 7
    AND     eax, 11b
    OR      eax, 01b
    shl     eax, 30
    add     edx, eax

    ;A[7:5] AND 010  //  29-27 bit
    mov     eax, [a]
    shr     eax, 5
    AND     eax, 010b
    shl     eax, 27
    add     edx, eax

    ;1  //  26 bit
    mov     eax, 1
    shl     eax, 26
    add     edx, eax

    ;B[11:11] AND A[23:23]  //  25 bit
    mov     eax, [a]
    mov     ebx, [b]
    shr     eax, 23
    shr     ebx, 11
    AND     eax, 1b                              ;Megkapni az utolsó bitet
    AND     ebx, 1b
    AND     eax, ebx
    shl     eax, 25
    add     edx, eax

    ;A[26:6]  //  24-4 bit
    mov     eax, [a]
    shl     eax, 5
    shr     eax, 11
    shl     eax, 4
    add     edx, eax

    ;B[12:9] + A[31:28]  //  4-0 bit
    mov     ebx, [b]
    shr     ebx, 9
    AND     ebx, 1111b

    mov     eax, [a]
    shr     eax, 28
    AND     ebx, 1111b

    add     eax, ebx
    AND     eax, 1111b

    add     edx, eax


    ;Eredmeny kiiratas
    call    mio_writeln
    mov     eax, str_eredmeny
    call    mio_writestr
    mov     eax, edx
    call    writebin
    call    mio_writeln

    ret


section .data
    str_binaris_kiiras db "[Kiiras]Binaris = ", 0
    str_hexa_beolvasas  db "[Beolvasas]Hexa (32bit) >> ", 0
    str_hexa_prefix db "0x", 0
    str_hiba  db "Hiba: Helytelen bemenet! Probald Ujra!", 0
    str_szabaly db "Szabaly: A[8:7] OR 01, A[7:5] AND 010, 1, B[11:11] AND A[23:23], A[26:6], B[12:9] + A[31:28]", 0
    str_a db "A = ", 0
    str_b db "B = ", 0
    str_c db "C = ", 0
    str_eredmeny db "D = ", 0
    a           dd 0
    b           dd 0
    c           dd 0
