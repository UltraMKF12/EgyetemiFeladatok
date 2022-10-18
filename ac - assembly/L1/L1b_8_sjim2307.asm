; Széri József - sjim2307
; 514/2

; Labor: 1
; Feladat: b8

;B. feladat – bitenkénti logikai műveletek
;Írassuk ki a kiértékelendő kifejezést, olvassuk be az a, b, c, d értékeket az io_readint függvény segítségével, majd írassuk ki a beolvasott értékeket és az eredményt egymás alá bináris formában az io_writebin függvény segítségével.

;(NOT a) AND((NOT c) OR(b AND d)) XOR b

; Compile:
; nasm -f win32 L1\L1b_8_sjim2307.asm
; nlink L1\L1b_8_sjim2307.obj -lio -o L1\L1b_8_sjim2307.exe

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
    
    ret
    
section .data
    str_a  db 'A = ', 0
    str_b  db 'B = ', 0
    str_c  db 'C = ', 0
    str_d  db 'D = ', 0
    str_result  db  "(NOT a) AND((NOT c) OR(b AND d)) XOR b = ", 0
    a      dd 0
    b      dd 0
    c      dd 0
    d      dd 0