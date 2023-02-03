%include 'ionum.inc'
%include 'iostr.inc'

;nasm -f win32 vizsga2.asm
;nlink ionum.obj iostr.obj vizsga2.obj -lmio -o vizsga2.exe

global main
section .text
main:
    mov     esi, str_a
    call    WriteStr
    call    ReadHex
    mov     [a], eax
    call    NewLine

    mov     esi, str_b
    call    WriteStr
    call    ReadHex
    mov     [b], eax
    call    NewLine
    call    NewLine

    mov     esi, str_binarias
    call    WriteLnStr
    mov     eax, [a]
    call    WriteBin
    call    NewLine
    mov     eax, [b]
    call    WriteBin
    call    NewLine
    call    NewLine

    ;Invertalni a-ban azt ami a es b ben 0
    mov     ecx, 32
    xor     edx, edx
    xor     ebx, ebx
    mov     eax, [a]
    mov     ebx, [b]

    .invertalas:
        shl     eax, 1
        jnc     .csere
        shl     ebx, 1
        jmp     .nincs_csere1
        .csere:
            shl     ebx, 1
            jc     .nincs_csere2

            shl     edx, 1
            add     edx, 1


        .nincs_csere1:
            shl     edx, 1
            add     edx, 1
            jmp     .end
        .nincs_csere2:
            shl     edx, 1
            jmp     .end

        .end:
            dec     ecx
            cmp     ecx, 0
            jg      .invertalas
            

    mov     esi, str_invertalva
    call    WriteLnStr
    mov     eax, edx    
    call    WriteBin

    call    NewLine
    call    NewLine

    mov     ecx, 8
    xor     edx, edx
    xor     esi, esi
    xor     edi, edi
    xor     edx, edx
    mov     ebx, [b]

    .levagasos:
        push    edi
        xor     esi, esi
        push    ecx
        mov     ecx, 4
        .repeater:
            shl     esi, 1
            shl     eax, 1
            adc     esi, 0

            shl     edi, 1
            shl     ebx, 1
            adc     edi, 0
            dec     ecx
            cmp     ecx, 0
            jge      .repeater

        add     esi, edi
        pop     ecx
        pop     edi
        cmp     esi, 0x10
        je      .overflow
        jmp     .ismetles

        .overflow:
            inc     edi
        .ismetles:
            shl     edx, 4
            add     edx, esi
            dec     ecx
            cmp     ecx, 0
            jg      .levagasos

            sub     edx, esi
            add     esi, edi
            and     esi, 0xF
            add     edx, esi

    mov     eax, edx
    call    WriteBin

    ret

section .data
    str_invertalva db "Invertalva: ", 0
    str_binarias db "Binarisan: ", 0
    str_a db "A[HEXA] = ", 0
    str_b db "B[HEXA] = ", 0

section .bss
    a resb 256
    b resb 256