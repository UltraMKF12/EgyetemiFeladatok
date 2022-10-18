; Széri József - sjim2307
; 514/2

; Labor: 1
; Feladat: a8

; A. feladat – aritmetikai kifejezés kiértékelése, „div” az egész osztás hányadosát, „mod” pedig a maradékát jelenti. 
;a, b, c, d, e, f, g előjeles egész számok, az io_readint függvénnyel olvassuk be őket ebben a sorrendben. Az eredményt az io_writeint eljárás segítségével írjuk ki.

;((f + a) div 5) - (e - 2 * (a + c)) + (b - c) div (g + 2) + ((d * g) mod 7) + 1

; Compile:
; nasm -f win32 L1\L1a_8_sjim2307.asm
; nlink L1\L1a_8_sjim2307.obj -lio -o L1\L1a_8_sjim2307.exe

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

    ; read E
    mov     eax, str_e
    call    io_writestr
    call    io_readint
    mov     [e], eax

    ; read F
    mov     eax, str_f
    call    io_writestr
    call    io_readint
    mov     [f], eax

    ; read G
    mov     eax, str_g
    call    io_writestr
    call    io_readint
    mov     [g], eax

    mov     eax, str_result
    call    io_writestr
    mov     eax, 213121
    call    io_writeint
    
    ret
    
section .data
    str_a  db 'A = ', 0
    str_b  db 'B = ', 0
    str_c  db 'C = ', 0
    str_d  db 'D = ', 0
    str_e  db 'E = ', 0
    str_f  db 'F = ', 0
    str_g  db 'G = ', 0
    str_result  db  "((f + a) div 5) - (e - 2 * (a + c)) + (b - c) div (g + 2) + ((d * g) mod 7) + 1 = ", 0
    a      dd 0
    b      dd 0
    c      dd 0
    d      dd 0
    e      dd 0
    f      dd 0
    g      dd 0