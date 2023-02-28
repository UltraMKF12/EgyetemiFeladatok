; Széri József - sjim2307
; 514/2

; Labor: 3
; Feladat: a

;Írjunk assembly eljárást (NASM), amely egy 32 bites, 
;előjel nélküli egész számot ír ki a képernyőre bináris formában, 
;kötelezően mindig 32 bináris számjegy formájában.

; Compile:
; nasm -f win32 L3\L3a_sjim2307.asm
; nlink L3\L3a_sjim2307.obj -lmio -o L3\L3a_sjim2307.exe
; actest L3a L3\L3a_sjim2307.exe

%include 'mio.inc'

global main

section .text
writebin:
    ;EAX kiiratása 32 bites bináris alakban
    ;0111 1011 0101 0100 1101 0010 1010 1011
    ;8 csoport, csoportonként 4 számjegy
    ;Alternativkén lehetne használni ADC-t osztály helyett

    ;Szöveg kiírása
    push    eax
    mov     eax, str_binaris_kiiras
    call    mio_writestr
    pop     eax


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
    call    beolvas_hexa
    call    mio_writeln
    mov     ebx, eax                                ;Első szám elemntése ebx-ben
    call    beolvas_hexa
    call    mio_writeln
    mov     ecx, eax                                ;Második szám elmentése ecx-ben

    mov     eax, ebx
    call    writebin
    call    mio_writeln

    mov     eax, ecx
    call    writebin
    call    mio_writeln

    add     eax, ebx
    call    writebin
    
    ret



section .data
    str_binaris_kiiras db "[Kiiras]Binaris = ", 0
    str_hexa_beolvasas  db "[Beolvasas]Hexa (32bit) >> ", 0
    str_hexa_prefix db "0x", 0
    str_hiba  db "Hiba: Helytelen bemenet! Probald Ujra!", 0