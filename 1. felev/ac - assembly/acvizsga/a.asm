%include 'ionum.inc'
%include 'iostr.inc'

;nasm -f win32 a.asm
;nlink iostr.obj ionum.obj strings.obj -lmio a.obj -o a.exe

global main

section .text
main:
    mov     ecx, 255

    mov     esi, keplet
    call    WriteLnStr
    call    NewLine

    mov     esi, a_str
    call    WriteStr
    call    ReadInt
    mov     [A], eax
    call    NewLine

    mov     esi, b_str
    call    WriteStr
    call    ReadInt
    mov     [B], eax
    call    NewLine

    mov     esi, c_str
    call    WriteStr
    call    ReadInt
    mov     [C], eax
    call    NewLine

    mov     esi, d_str
    call    WriteStr
    call    ReadInt
    mov     [D], eax
    call    NewLine

    mov     esi, e_str
    call    WriteStr
    call    ReadInt
    mov     [E], eax
    call    NewLine

    mov     esi, f_str
    call    WriteStr
    call    ReadInt
    mov     [F], eax
    call    NewLine

    mov     esi, g_str
    call    WriteStr
    call    ReadInt
    mov     [G], eax
    call    NewLine

    call    NewLine
    mov     esi, eredmeny
    call    WriteStr

    ;min(F, B)*(D-3*B)/5 + E^2 - ((8 + G - A) mod 12) * (B - F*C/4)

    ;min(F, B) -> EAX
    mov     eax, [F]
    mov     ebx, [B]
    cmp     eax, ebx
    jge     .nagyobb
    jmp     .kisebb

    .nagyobb:
        mov     eax, ebx
    .kisebb:

    ;(D-3*B) -> EBX
    mov      ebx, [B]
    mov      ecx, 3
    imul     ebx, ecx
    mov      ecx, [D]
    sub      ecx, ebx
    mov      ebx, ecx

    ;min(F, B)*(D-3*B) -> EAX
    imul     eax, ebx

    ;eax / 5
    mov      ebx, 5
    cdq
    idiv     ebx

    ;E^2 -> EBX
    mov     ebx, [E]
    mov     ecx, [E]
    imul    ebx, ecx

    ;EAX + EBX -> EAX
    add     eax, ebx

    ;((8 + G - A) mod 12) -> EBX
    mov     ebx, [G]
    mov     ecx, [A]
    add     ebx, 8
    sub     ebx, ecx

    push    eax
    mov     eax, ebx
    mov     ebx, 12
    cdq
    idiv    ebx
    mov     ebx, edx
    pop     eax

    ;(B - F*C/4) -> ECX
    mov     ecx, [F]
    mov     edx, [C]
    imul    ecx, edx

    push    eax
    push    ebx

    mov     eax, ecx
    mov     ebx, 4
    cdq
    idiv    ebx
    mov     edx, eax

    pop     ebx
    pop     eax

    mov     ecx, [B]
    sub     ecx, edx

    ;EAX - EBX * ECX
    imul    ebx, ecx
    sub     eax, ebx

    call    WriteInt
    ret

section .data
    a_str   db "A = ", 0
    b_str   db "B = ", 0
    c_str   db "C = ", 0
    d_str   db "D = ", 0
    e_str   db "E = ", 0
    f_str   db "F = ", 0
    g_str   db "G = ", 0
    keplet  db "min(F, B)*(D-3*B)/5 + E^2 - ((8 + G - A) mod 12) * (B - F*C/4)", 0
    eredmeny db "Eredmeny = ", 0

section .bss
    A   resd 1
    B   resd 1
    C   resd 1
    D   resd 1
    E   resd 1
    F   resd 1
    G   resd 1