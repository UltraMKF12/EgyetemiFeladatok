; Széri József - sjim2307
; 514/2

; Labor: 6 - SSE 2
; Feladat: 8

;Olvassunk be két (A és B) azonos hosszúságú lebegőpontos értékekből álló tömböt (max. 256 elem). 
;Olvassuk be a tömbök hosszát (n integer, 4<=n<=256), majd a tömbök elemeit, minden elemet új sorból 
;(azaz 2n lebegőpontos értéket olvasunk be). A tömbök minden elemére páronként végezzük el az alább megadott műveleteket, 
;tároljuk el az eredményeket egy másik tömbben, végül pedig írjuk ki azt. A feladat lényege, hogy ne skaláris utasításokat használjuk, 
;hanem vektorosokat (azaz pl. ADDSS helyett ADDPS-t használjunk 4 db. számpár párhuzamos összeadására). 
;Így a teljesítmény akár 4x nagyobb lehet. Csak 4-el osztható hosszúságú tömböket kell elfogadjon a program.

;8. E(a,b) = 2.7 * a * b - sqrt(a + b / 3) + max(a, b)

; Compile:
; compile_run.bat SSE2\L6_08_sjim2307

%include 'io.inc'

global main

section .text
main:
    mov     eax, str_feladat
    call    io_writestr
    call    io_writeln
    call    io_writeln

    mov     eax, str_n
    call    io_writestr
    call    io_readint

    ;Letesztelni, hogy osztható-e 4-el.
    push    eax

    cdq
    mov     ebx, 4
    idiv    ebx
    cmp     edx, 0
    jne     .hiba

    pop     eax


    ;Beolvasni a szamokat egyenkent.
    xor     ecx, ecx
    xor     esi, esi
    .tomb_a:
        push    eax
        mov     eax, str_a
        call    io_writestr
        pop     eax

        call    io_readflt
        movss   [a + esi], xmm0

        add     esi, 4
        inc     ecx
        
        cmp     ecx, eax
        jl      .tomb_a

    call    io_writeln

    xor     ecx, ecx
    xor     esi, esi
    .tomb_b:
        push    eax
        mov     eax, str_b
        call    io_writestr
        pop     eax

        call    io_readflt
        movss   [b + esi], xmm0

        add     esi, 4
        inc     ecx
        
        cmp     ecx, eax
        jl      .tomb_b


    ;Feladat: E(a,b) = 2.7 * a * b - sqrt(a + b / 3) + max(a, b)
    xor     ecx, ecx
    xor     esi, esi
    .feladat:
        ;-------------------------
        ; xmm0 - a
        ; xmm1 - b
        ; xmm2 - 2.7 * a * b
        ; xmm3 - sqrt(a + b / 3) <-- xmm5 = 3
        ; xmm4 - max(a, b)
        ;-------------------------

        ; xmm0 - a
        ; xmm1 - b
        movups  xmm0, [a + esi]
        movups  xmm1, [b + esi]

        ;xmm2 - 2.7 * a * b
        movups  xmm2, [float_ketto_het]
        mulps   xmm2, xmm0
        mulps   xmm2, xmm1

        ; xmm3 - sqrt(a + b / 3) <-- xmm5 = 3
        movups  xmm5, [float_harom]
        movups  xmm3, xmm1
        divps   xmm3, xmm5
        addps   xmm3, xmm0
        sqrtps  xmm3, xmm3

        ;xmm4 - max(a, b)
        movups  xmm4, xmm0
        maxps   xmm4, xmm1

        ;E(a,b) = 2.7 * a * b - sqrt(a + b / 3) + max(a, b)
        ; xmm2 - xmm3 + xmm4
        movups  xmm5, xmm2
        subps   xmm5, xmm3
        addps   xmm5, xmm4

        movups  [c + esi], xmm5

        add     esi, 16
        inc     ecx
        
        cmp     ecx, eax
        jl      .feladat


    ;Eredmeny Kiiratas:
    push    eax
    call    io_writeln
    mov     eax, str_megoldasok
    call    io_writestr
    call    io_writeln
    pop     eax

    xor     ecx, ecx
    xor     esi, esi
    .eredmeny_kiiratas:
        movss   xmm0, [c + esi]
        call    io_writeflt
        call    io_writeln

        add     esi, 4
        inc     ecx
        
        cmp     ecx, eax
        jl      .eredmeny_kiiratas

    .end:
        ret

    .hiba:
        mov     eax, str_rossz_n
        call    io_writestr
        ret
    
    
section .data
    str_feladat     db "Feladat: E(a,b) = 2.7 * a * b - sqrt(a + b / 3) + max(a, b)", 0
    str_a           db "A eleme >> ", 0
    str_b           db "B eleme >> ", 0
    str_n           db "N = ", 0
    str_rossz_n     db "Hiba: N nem oszthato 4-el!", 0
    str_megoldasok  db "Megoldasok: ", 0

    float_ketto_het dd 2.7, 2.7, 2.7, 2.7
    float_harom     dd 3.0, 3.0, 3.0, 3.0

section .bss
    a   resd 1025
    b   resd 1025
    c   resd 1025