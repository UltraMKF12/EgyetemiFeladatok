; Széri József - sjim2307
; 514/2

; Labor: 5 - SSE 1
; Feladat: SSE 1

;Készítsünk el egy-egy olyan eljárást, amely 32 bites, egyszeres pontosságú lebegőpontos értéket olvas be és ír ki, hagyományos (±1234.5678) 
;és exponenciális formában (±1.234567e±12) egyaránt. Az exponenciális formában a pozitív előjelek opcionálisok (tehát ez is helyes: 1.37e2), 
;az e betű pedig lehet kicsi és nagy is.

;E(a,b,c,d) = a * (d - b) - sqrt(a + c / 2)

; Compile:
; compile_run.bat SSE1\L5_sjim2307

%include 'mio.inc'
%include 'io.inc'

global main
section .text
;--------------------------------------------------------------
;---------[ Szükséges függvények előző feladatokból ]----------
;-------------------------------------------------------------
ReadInt:
    push    esi
    push    edi
    push    ebx
    push    ecx
    push    edx

    ; sub     esp, 500
    ; mov     esi, esp
    ; mov     ecx, 256
    ; call    ReadStr

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

        ; add     esp, 500
        pop     edx
        pop     ecx
        pop     ebx
        pop     edi
        pop     esi

        stc
        ret

    .end:
        mov     eax, ebx

        ; add     esp, 500
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


ReadStr:
    ;Stores string to ESI
    ;ECX max charcters
    pusha

    xor     eax, eax
    xor     ebx, ebx
    mov     edi, esi

    .new_character:
        call    mio_readchar

        ;ENTER
        cmp     al, 13
        je      .end

        ;BACKSPACE
        cmp     al, 8
        je      .backspace

        inc     ebx
        call    mio_writechar

        ;Check if out of characters to store
        cmp     ebx, ecx
        jg      .new_character

        stosb
        jmp     .new_character

    .backspace:
        ;Don't delete more than it should
        cmp     ebx, 0
        jle     .new_character
        
        mov     al, 8
        call    mio_writechar
        mov     al, " "
        call    mio_writechar
        mov     al, 8
        call    mio_writechar

        dec     ebx

        cmp     ebx, ecx
        jge     .new_character

        dec     edi
        jmp     .new_character

    .end:
        mov     al, 0
        stosb

        popa
        ret


WriteStr:
    ;Write string from ESI to console
    pusha

    xor     eax, eax
    .next_character:
        lodsb

        cmp     al, 0
        je      .end

        call    mio_writechar
        jmp     .next_character

    .end:
        popa
        ret

ReadLnStr:
    call    ReadStr
    call    NewLine
    ret

WriteLnStr:
    call    WriteStr
    call    NewLine
    ret

NewLine:
    pusha
    xor     eax, eax
    mov     al, 13
    call    mio_writechar
    mov     al, 10
    call    mio_writechar
    popa
    ret
;-------------------------------------------------------------
;-------------------------------------------------------------
;-------------------------------------------------------------

;Seged Függvények
Kettevalasztas:
    ;Return eax and ebx with integers, edx 0 or 1(positive/negative)
    xor     eax, eax
    xor     ebx, ebx
    xor     ecx, ecx    
    xor     edx, edx    ;Elojel index
    xor     edi, edi    
    

    ;Elojel teszt
    lodsb
    cmp     al, "-"
    je      .negativ
    cmp     al, "+"
    je      .pozitiv
    
    cmp     al, "9"
    jg      .hiba
    cmp     al, "0"
    jl      .hiba

    jmp     .szamjegy

    .negativ:
        mov     edx, 1
        jmp     .folyatas
    .pozitiv:
        mov     edx, 0
        jmp     .folyatas
    .szamjegy:
        mov     edx, 0
        sub     esi, 1
        jmp     .folyatas


    .folyatas:
    mov     edi, temp1
    .darabolas:
        xor     eax, eax
        lodsb

        cmp     al, 0
        je      .end

        cmp     al, "."
        je      .pont

        cmp     al, "9"
        jg      .hiba
        cmp     al, "0"
        jl      .hiba
        
        stosb
        mov     [edi + 1], byte 0

        jmp     .darabolas

    .pont:
        mov     edi, temp2
        jmp     .darabolas

    .hiba:
        stc
        ret
    .end:
        mov     esi, temp2
        call    ReadInt
        mov     ebx, eax
        mov     esi, temp1
        call    ReadInt
        ret


KettevalasztasEX:
    ;Return eax and ebx with integers, edx 0 or 1(positive/negative)
    xor     eax, eax
    xor     ebx, ebx
    xor     ecx, ecx    ;Ide kerul E erteke
    xor     edx, edx    ;Elojel index
    xor     edi, edi    
    

    ;Elojel teszt
    lodsb
    cmp     al, "-"
    je      .negativ
    cmp     al, "+"
    je      .pozitiv
    
    cmp     al, "9"
    jg      .hiba
    cmp     al, "0"
    jl      .hiba

    jmp     .szamjegy

    .negativ:
        mov     edx, 1
        jmp     .folyatas
    .pozitiv:
        mov     edx, 0
        jmp     .folyatas
    .szamjegy:
        mov     edx, 0
        sub     esi, 1
        jmp     .folyatas


    .folyatas:
    mov     edi, temp1
    .darabolas:
        xor     eax, eax
        lodsb

        cmp     al, 0
        je      .end

        cmp     al, "."
        je      .pont

        cmp     al, "e"
        je      .e_betu

        cmp     al, "E"
        je      .e_betu

        cmp     al, "9"
        jg      .hiba
        cmp     al, "0"
        jl      .hiba
        
        stosb
        mov     [edi + 1], byte 0

        jmp     .darabolas

    .pont:
        mov     edi, temp2
        jmp     .darabolas

    .e_betu:
        mov     edi, temp4
        xor     eax, eax
        lodsb
        
        cmp     al, "-"
        je      .jeles
        cmp     al, "+"
        je      .jeles

        dec     esi
        jmp     .e_betu_loop

        .jeles:
            stosb
            
    .e_betu_loop:
        xor     eax, eax
        lodsb

        cmp     al, 0
        je      .end

        cmp     al, "9"
        jg      .hiba
        cmp     al, "0"
        jl      .hiba

        stosb
        mov     [edi + 1], byte 0

        jmp     .e_betu_loop

    .hiba:
        stc
        ret
    .end:
        mov     esi, temp4
        call    ReadInt
        mov     ecx, eax

        mov     esi, temp2
        call    ReadInt
        mov     ebx, eax
        mov     esi, temp1
        call    ReadInt
        call    NewLine
        ret


;_______[Sima float]_______
ReadFloat:
    pushad

    ;Beolvasni a számot
    ;+- első karakter után állítani a +- dolgot.
    ;. karakternél kettéválaszatni, két számjegyet kinyerni, majd floatos cuccként összeadni
    mov     esi, temp3
    mov     ecx, 256
    call    ReadStr
    call    Kettevalasztas      ;Kettevalasztja eax es ebx-be a pontnal a szamokat. EDX elojel

    ;Egesz resz
    xorps       xmm0, xmm0
    cvtsi2ss    xmm0, eax

    ;Tort resz
    xorps       xmm1, xmm1
    cvtsi2ss    xmm1, ebx

    movss       xmm2, [float_div]

    .nullazas:
        cvttss2si   eax, xmm1
        cmp         eax, 0
        je          .end

        divss       xmm1, xmm2
        jmp         .nullazas
    

    .end:
        addss   xmm0, xmm1
        cmp     edx, 1
        je      .negativos
        jmp     .nem_negativos
        .negativos:
            movss   xmm2, [float_negativ]
            mulss   xmm0, xmm2
        .nem_negativos:
        popad
        ret

WriteFloat:
    ;Megnezni negativ vagy pozitiv
    pushad

    cvttss2si   eax, xmm0
    cmp         eax, 0
    jl          .negativ
    jmp         .nem_negativ

    .negativ:
        movss   xmm1, [float_negativ]
        mulss   xmm0, xmm1
        mov     eax, "-"
        call    mio_writechar

    .nem_negativ:
    cvttss2si   eax, xmm0
    call    WriteInt

    cvtsi2ss    xmm1, eax
    subss       xmm0, xmm1

    mov     eax, "."
    call    mio_writechar

    movss   xmm1, [float_negy]
    mulss   xmm0, xmm1
    cvttss2si   eax, xmm0
    call    WriteInt

    .end:
        popad
        ret
;---------------------------



;_______[EX float]_______
ReadFloatEX:
    pushad

    ;Beolvasni a számot
    ;+- első karakter után állítani a +- dolgot.
    ;. karakternél kettéválaszatni, két számjegyet kinyerni, majd floatos cuccként összeadni
    mov     esi, temp3
    mov     ecx, 256
    call    ReadStr
    call    KettevalasztasEX
    ;EAX = elso resz
    ;EBX = masodik resz
    ;ECX = E erteke
    ;EDX = elojel

    ;Egesz resz
    xorps       xmm0, xmm0
    cvtsi2ss    xmm0, eax

    ;Tort resz
    xorps       xmm1, xmm1
    cvtsi2ss    xmm1, ebx

    movss       xmm2, [float_div]

    .nullazas:
        cvttss2si   eax, xmm1
        cmp         eax, 0
        je          .e_ezes

        divss       xmm1, xmm2
        jmp         .nullazas
    
    .e_ezes:
        addss   xmm0, xmm1
        cmp     edx, 1
        je      .negativos
        jmp     .nem_negativos
        .negativos:
            movss   xmm2, [float_negativ]
            mulss   xmm0, xmm2
        .nem_negativos:
        movss     xmm1, [float_div]
        cmp     ecx, 0
        jl      .e_ezes_loop_negativ
        jmp     .e_ezes_loop_pozitiv
    .e_ezes_loop_pozitiv:
        cmp     ecx, 0
        je      .end

        dec     ecx
        mulss   xmm0, xmm1

        jmp     .e_ezes_loop_pozitiv
    .e_ezes_loop_negativ:
        call    io_writeflt
        call    NewLine
        cmp     ecx, 0
        je      .end

        inc     ecx
        divss   xmm0, xmm1

        jmp     .e_ezes_loop_negativ

    .end:
        popad
        ret

WriteFloatEX:
    ret

;------------------------
main:
    ;E(a,b,c,d) = a * (d - b) - sqrt(a + c / 2)
    call    io_readflt
    call    NewLine
    call    WriteFloat
    ret
    
    
section .data
    str_feladat         db "Feladat: E(a,b,c,d) = a * (d - b) - sqrt(a + c / 2)", 0
    str_feladat2        db "E(a,b,c,d) = ", 0
    str_beolvas_float   db "[Beolvas][Float] = ", 0
    str_beolvas_ex      db "[Beolvas][EX-Float] = ", 0
    str_kiir_float      db "[Kiir][EX-Float] >>> ", 0
    str_kiir_ex         db "[Kiir][EX-Float] >>> ", 0

    float_div           dd 10.0
    float_negy          dd 10000.0
    float_negativ       dd -1.0

section .bss
    temp1 resb 256
    temp2 resb 256
    temp3 resb 256
    temp4 resb 256
    a   resd 1
    b   resd 1
    c   resd 1
    d   resd 1