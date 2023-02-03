%include 'ionum.inc'
%include 'iostr.inc'

;nasm -f win32 iostr.asm
;nlink ionum.obj iostr.obj vizsga1.obj -lmio -o vizsga1.exe

global main
section .text
main:
    mov     esi, keplet
    call    WriteLnStr

    mov     esi, a
    call    WriteStr
    call    ReadInt
    mov     [value_a], eax
    call    NewLine

    mov     esi, b
    call    WriteStr
    call    ReadInt
    mov     [value_b], eax
    call    NewLine

    mov     esi, c
    call    WriteStr
    call    ReadInt
    mov     [value_c], eax
    call    NewLine

    mov     esi, d
    call    WriteStr
    call    ReadInt
    mov     [value_d], eax
    call    NewLine

    mov     esi, e
    call    WriteStr
    call    ReadInt
    mov     [value_e], eax
    call    NewLine

    mov     esi, f
    call    WriteStr
    call    ReadInt
    mov     [value_f], eax
    call    NewLine

    mov     esi, g
    call    WriteStr
    call    ReadInt
    mov     [value_g], eax
    call    NewLine

    mov     esi, eredmeny
    call    WriteStr
    ;((D + C) div 3 - min(A+C, B+F) + E*(G-6)) mod (D - 5) * (E+C)


    ;(D + C) div 3 -> eax
    mov     eax, [value_d]
    mov     ebx, [value_c]
    add     eax, ebx
    mov     ebx, 3
    cdq
    idiv    ebx

    ;min(A+C, B+F) -> ebx
    mov     ebx, [value_a]
    mov     ecx, [value_c]
    add     ebx, ecx
    mov     ecx, [value_b]
    mov     edx, [value_f]
    add     ecx, edx
    cmp     ebx, ecx
    jle     .elso_kisebb

    .masodik_kisebb:
        mov     ebx, ecx
    .elso_kisebb:
        ;itt nem kell tenni semmit

    ;E*(G-6) -> ecx
    push    eax
    push    ebx
    mov     eax, [value_e]
    mov     ebx, [value_g]
    sub     ebx, 6
    cdq
    imul    ebx
    mov     ecx, eax
    pop     ebx
    pop     eax

    ;eax - ebx + ecx -> EAX [(D + C) div 3 - min(A+C, B+F) + E*(G-6)]
    sub     eax, ebx
    add     eax, ecx

    ;mod (D - 5)
    mov     ebx, [value_d]
    sub     ebx, 5
    cdq
    idiv    ebx
    mov     eax, edx

    ;* (E+C)
    mov     ebx, [value_e]
    mov     ecx, [value_c]
    add     ebx, ecx

    cdq
    imul    ebx

    call    WriteInt


    ret

section .data
    a db "A = ", 0
    b db "B = ", 0
    c db "C = ", 0
    d db "D = ", 0
    e db "E = ", 0
    f db "F = ", 0
    g db "G = ", 0
    eredmeny db "Eredmeny = ", 0
    keplet db "((D + C) div 3 - min(A+C, B+F) + E*(G-6)) mod (D - 5) * (E+C)", 0

section .bss
    value_a resb 256
    value_b resb 256
    value_c resb 256
    value_d resb 256
    value_e resb 256
    value_f resb 256
    value_g resb 256
    