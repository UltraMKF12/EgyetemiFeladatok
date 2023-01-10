; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: ionum

; Compile:
; compile_module.bat ionum

%include 'iostr.inc'
%include 'mio.inc'

;global ReadInt   
;global WriteInt  
;global ReadInt64 
;global WriteInt64
;global ReadBin   
;global WriteBin  
;global ReadBin64 
;global WriteBin64
;global ReadHex   
;global WriteHex  
;global ReadHex64 
;global WriteHex64

global main

section .text

ReadInt:
    push    esi
    push    edi
    push    ebx
    push    ecx
    push    edx

    xor     eax, eax
    xor     ebx, ebx
    xor     edx, edx

    mov     esi, esp
    sub     esi, 500
    mov     ecx, 256
    call    ReadStr

    mov     ecx, 10
    ;esi - szám-szöveg
    ;ecx - szorzó
    ;eax - számjegy
    ;ebx - segédszám
    .new_digit:
        lodsb

        cmp     al, 0
        je      .end

        ;Minusz jel
        cmp     al, '-'
        je      .minus

        ;Ha nem számjegy
        cmp     al, '0'
        jl      .error
        cmp     al, '9'
        jg      .error


        imul    ebx, ecx
        jo      .error

        sub     eax, '0'

        cmp     edx, 0
        je      .positive
        cmp     edx, 1
        je      .negative

        jmp     .error

     .minus:
        cmp     edx, 1
        je      .error
        mov     edx, 1
        jmp     .new_digit
    

    .negative:
        sub     ebx, eax
        jo      .error
        jmp     .new_digit
    
    .positive: 
        add     ebx, eax
        jo      .error
        jmp     .new_digit


    .error:
        stc

    .end:
        pop     edx
        pop     ecx
        pop     ebx
        pop     edi
        pop     esi

        ret


WriteInt:

    .end:
        ret


ReadInt64:

    .end:
        ret


WriteInt64:

    .end:
        ret


ReadBin:
    ;EAX beolvasasa 32 bites bináris alakban
    push    esi
    sub     esp, 500
    mov     esi, esp
    call    ReadStr
    
    xor     ecx, ecx                        ;counter
    xor     eax, eax
    xor     ebx, ebx

    .number_build:
        cmp     ecx, 32
        jge     .error

        lodsb
        cmp     al, '0'
        jl      .error
        cmp     al, '1'
        jg      .error

        sub     al, '0'

        shl     ebx, 1
        add     bl, al

        inc     ecx
        jmp     .number_build

    .error:
        add     esp, 500
        pop     esi

        mov     eax, ebx
        stc
        ret
    .end:
        add     esp, 500
        pop     esi

        mov     eax, ebx
        ret


WriteBin:
    ;EAX kiiratása 32 bites bináris alakban
    ;0111 1011 0101 0100 1101 0010 1010 1011
    ;8 csoport, csoportonként 4 számjegy
    pusha

    mov     ecx, 32                                 ;32 bit betevese stackbe
    mov     ebx, 2                                  ;Osztasi maradek szamlalasara

    .beolvasas:
        ;32-bit beolvasasa stackbe
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
        popa
        ret


ReadBin64:

    .end:
        ret


WriteBin64:

    .end:
        ret


ReadHex:
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
        push    esi
        mov     esi, str_hexa_prefix
        call    WriteStr
        pop     esi


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
        ;Betesszük a számot eax-be.
        mov     eax, ebx

        ;Visszaszerezzük az értékekek stackből.
        pop     ecx
        pop     ebx

        stc
        ret


    .end:
        ;Betesszük a számot eax-be.
        mov     eax, ebx

        ;Visszaszerezzük az értékekek stackből.
        pop     ecx
        pop     ebx

        ret


WriteHex:
    ;A fügvény EAX-ből írja ki a számot hexadecimális formában

    ;Szöveg kiírása
    push    esi
    mov     esi, str_hexa_prefix
    call    WriteStr
    pop     esi

    ;Értékek elmentése
    push    eax                             ;eax eredeti értékének elmentése
    push    ebx                             ;hexa szamjegyek? tárolása
    push    ecx                             ;Számláló
    push    edx

    mov     ecx, 8                          ;8 karaktert kell beolvasni

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


ReadHex64:

    .end:
        ret


WriteHex64:

    .end:
        ret



main:
    mov     esi, str_a_text
    call    WriteStr
    call    ReadBin
    call    NewLine
    call    WriteBin

    ret
    
section .data
    str_a_text db "A = ", 0
    str_hexa_prefix db "0x", 0

section .bss
    str_a   resb 256