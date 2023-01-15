; Széri József - sjim2307
; 514/2

; Labor: 5 - SSE 1
; Feladat: SSE 1

;Készítsünk el egy-egy olyan eljárást, amely 32 bites, egyszeres pontosságú lebegőpontos értéket olvas be és ír ki, hagyományos (±1234.5678) 
;és exponenciális formában (±1.234567e±12) egyaránt. Az exponenciális formában a pozitív előjelek opcionálisok (tehát ez is helyes: 1.37e2), 
;az e betű pedig lehet kicsi és nagy is.

; Compile:
; compile_run.bat SSE1\L5_sjim2307

%include 'io.inc'

global main

section .text
main:
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