; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: ionum

; Compile:
; compile_module.bat ionum
; nasm -f win32 ionum.asm

%include 'iostr.inc'
%include 'mio.inc'

global ReadInt   
global WriteInt  
global ReadBin   
global WriteBin  
global ReadHex   
global WriteHex  


section .text

ReadInt:
    push    esi
    push    edi
    push    ebx
    push    ecx
    push    edx

    sub     esp, 500
    mov     esi, esp
    mov     ecx, 256
    call    ReadStr

    xor     eax, eax
    xor     ebx, ebx
    xor     edx, edx
    xor     edi, edi


    mov     ecx, 10
    ;esi - szám-szöveg
    ;ecx - szorzó
    ;eax - számjegy
    ;ebx - segédszám
    ;edi - ne legyen az elejen kivul mashol minusz jel
    .new_digit:
        lodsb

        cmp     al, 0
        je      .end

        ;Minusz jel
        cmp     al, '-'
        je      .minus
        inc     edi

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
        cmp     edi, 1
        jge     .error
        inc     edi

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
        mov     eax, ebx

        add     esp, 500
        pop     edx
        pop     ecx
        pop     ebx
        pop     edi
        pop     esi

        stc
        ret

    .end:
        mov     eax, ebx

        add     esp, 500
        pop     edx
        pop     ecx
        pop     ebx
        pop     edi
        pop     esi

        ret


WriteInt:
    ;A fügvény EAX-ből írja ki a számot.

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


ReadBin:
    ;EAX beolvasasa 32 bites bináris alakban
    push    ecx
    push    ebx
    push    esi

    sub     esp, 500
    mov     esi, esp
    mov     ecx, 256
    call    ReadStr
    

    xor     ecx, ecx                        ;counter
    xor     eax, eax
    xor     ebx, ebx

    .number_build:
        cmp     ecx, 33
        jge     .error

        lodsb
        cmp     al, 0
        je      .end
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
        mov     eax, ebx

        add     esp, 500
        pop     esi
        pop     ebx
        pop     ecx


        stc
        ret
    .end:
        mov     eax, ebx

        add     esp, 500
        pop     esi
        pop     ebx
        pop     ecx


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


ReadHex:
    ;AL                                   0000 0000 - FF
    ;AX                         0000 0000 0000 0000 - FFFF
    ;EAX    0000 0000 0000 0000 0000 0000 0000 0000 - FFFF FFFF
    
    ;A fügvény EAX-be olvassa be az értéket.
    push    esi
    push    ebx                             ;Kell az ebx szam felepitesre
    push    ecx                             ;Számláló, max 8 szám lehet beírva

    sub     esp, 500
    mov     esi, esp
    mov     ecx, 256
    call    ReadStr

    xor     ebx, ebx
    xor     ecx, ecx


    .uj_karakter:
        xor     eax, eax
        lodsb

        ;ENTER - eseten véget ér a beolvasás
        cmp     al, 0
        je      .end

        ;MAXIMÁLIS HOSSZ
        cmp     ecx, 8                      ;Ha 8 karakter hosszú a hexa számjegy, akkor már nem lehet többet beleírni.
        jge      .hiba

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


    .hiba:
        ;Betesszük a számot eax-be.
        mov     eax, ebx


        ;Visszaszerezzük az értékekek stackből.
        add     esp, 500
        pop     ecx
        pop     ebx
        pop     esi

        
        stc
        ret


    .end:
        ;Betesszük a számot eax-be.
        mov     eax, ebx


        ;Visszaszerezzük az értékekek stackből.
        add     esp, 500
        pop     ecx
        pop     ebx
        pop     esi


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
    

section .data
    str_hexa_prefix db "0x", 0