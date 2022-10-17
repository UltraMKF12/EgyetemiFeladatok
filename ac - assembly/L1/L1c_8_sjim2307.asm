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