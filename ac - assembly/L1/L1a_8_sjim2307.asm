; Széri József - sjim2307
; 514/2

; Labor: 1
; Feladat: a8

; A. feladat – aritmetikai kifejezés kiértékelése, „div” az egész osztás hányadosát, „mod” pedig a maradékát jelenti. 
;a, b, c, d, e, f, g előjeles egész számok, az io_readint függvénnyel olvassuk be őket ebben a sorrendben. Az eredményt az io_writeint eljárás segítségével írjuk ki.

;((f + a) div 5) - (e - 2 * (a + c)) + (b - c) div (g + 2) + ((d * g) mod 7) + 1

%include 'io.inc'

global main

section .text
main:
    ; read A into EBX
    mov     eax, str_a
    call    io_writestr
    call    io_readint
    mov     ebx, eax
    
    ; read B into EAX
    mov     eax, str_b
    call    io_writestr
    call    io_readint
    
    add     ebx, eax        ; compute A+B into EBX
    
    ; write A+B
    call    io_writeln
    mov     eax, str_ab
    call    io_writestr
    mov     eax, ebx
    call    io_writeint
    call    io_writeln
    
    ret
    
section .data
    str_a  db 'A = ', 0
    str_b  db 'B = ', 0
    str_ab db 'A+B = ', 0