; Széri József - sjim2307
; 514/2

; Labor: 1
; Feladat: c8

;C. feladat – feltételes kifejezés
;Írassuk ki a kiértékelendő kifejezést, olvassuk be az a, b, c, d értékeket az io_readint függvény segítségével, majd írassuk ki a beolvasott értékeket és az eredményt egymás alá (előjeles egész számként).

;ha d mod 4 = 0 : (b + c) div 3
;ha d mod 4 = 1 : a - 6
;ha d mod 4 = 2 : (c - 2) * (b + 2)
;ha d mod 4 = 3 : (b * a) - (2 * c)

; Compile:
; nasm -f win32 L1\L1c_8_sjim2307.asm
; nlink L1\L1c_8_sjim2307.obj -lio -o L1\L1c_8_sjim2307.exe

%include 'io.inc'

global main

section .text
main:
    ; read A
    mov     eax, str_a
    call    io_writestr
    call    io_readint
    mov     [a], eax

    ; read B
    mov     eax, str_b
    call    io_writestr
    call    io_readint
    mov     [b], eax

    ; read C
    mov     eax, str_c
    call    io_writestr
    call    io_readint
    mov     [c], eax

    ; read D
    mov     eax, str_d
    call    io_writestr
    call    io_readint
    mov     [d], eax
    
    ; Move D to eax then divide by 4 to get he modulo in edx
    mov     eax, [d]
    cdq
    mov     ebx, 4 ; IDIV does not work with numbers, it does not compile that way.
    idiv    ebx

    ; Handle possibilities
    cmp     edx, 0
    je      .zero

    cmp     edx, 1
    je      .one

    cmp     edx, 2
    je      .two

    cmp     edx, 3
    je      .three

    .zero:
        ;d mod 4 = 0 : (b + c) div 3

        ; First text, then result
        mov     eax, str_result0
        call    io_writestr

        ;(b+c) -> eax
        mov     eax, [b]
        add     eax, [c]

        ;(b+c) div 3 -> eax
        mov     ebx, 3
        cdq
        idiv     ebx

        call    io_writeint
        jmp     .end
    
    .one:
        ;d mod 4 = 1 : a - 6

        ; First text, then result
        mov     eax, str_result1
        call    io_writestr

        ;a - 6
        mov     eax, [a]
        sub     eax, 6

        call    io_writeint
        jmp     .end

    .two:
        ;d mod 4 = 2 : (c - 2) * (b + 2)

        ; First text, then result
        mov     eax, str_result2
        call    io_writestr

        ;(c - 2) -> ecx
        mov     ecx, [c]
        sub     ecx, 2

        ;(b + 2) -> ebx
        mov     ebx, [b]
        add     ebx, 2

        ;(c - 2) * (b + 2) -> ebx -> eax
        imul    ebx, ecx
        mov     eax, ebx

        call    io_writeint
        jmp     .end
    
    .three:
        ;d mod 4 = 3 : (b * a) - (2 * c)

        ; First text, then result
        mov     eax, str_result3

        ;(b * a) -> eax
        mov     eax, [a]
        imul    eax, [b]

        ;(2 * c) -> ecx
        mov     ecx, [c]
        imul    ecx, 2

        ;(b * a) - (2 * c) -> eax
        sub     eax, ecx

        call    io_writeint
        call    io_writestr
        jmp     .end

    .end:
        ret
    
section .data
    str_a  db 'A = ', 0
    str_b  db 'B = ', 0
    str_c  db 'C = ', 0
    str_d  db 'D = ', 0
    str_result0  db  "d mod 4 = 0 : (b + c) div 3 = ", 0
    str_result1  db  "d mod 4 = 1 : a - 6 = ", 0
    str_result2  db  "d mod 4 = 2 : (c - 2) * (b + 2) = ", 0
    str_result3  db  "d mod 4 = 3 : (b * a) - (2 * c) = ", 0
    a      dd 0
    b      dd 0
    c      dd 0
    d      dd 0