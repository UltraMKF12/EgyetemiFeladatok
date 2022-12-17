; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: ionum

; Compile:
; compile_module.bat ionum

%include 'iostr.inc'

;global ReadInt   
;global WriteInt  
;global ReadInt64 
;global WriteInt64
;global ReadBin   
;global WriteBin  
;global ReadBin64 
;global WriteBin64
;global ReadHex   
;global WriteHex  
;global ReadHex64 
;global WriteHex64

global main

section .text

ReadInt:
    push    esi
    push    edi
    push    ebx
    push    ecx
    push    edx

    xor     eax, eax
    xor     ebx, ebx
    xor     edx, edx

    mov     esi, esp
    sub     esi, 500
    mov     ecx, 256
    call    ReadStr

    mov     ecx, 10
    ;esi - szám-szöveg
    ;ecx - szorzó
    ;eax - számjegy
    ;ebx - segédszám

    .new_digit:
        lodsb

        cmp     al, 0
        je      .end

        ;Minusz jel
        cmp     al, '-'
        je      .minus

        ;Ha nem számjegy
        cmp     al, '0'
        jl      .error
        cmp     al, '9'
        jg      .error


        imul    ebx, ecx
        jo      .error

        sub     eax, '0'

        cmp     edx, 0
        je      .positive
        cmp     edx, 1
        je      .negative

        jmp     .error

     .minus:
        cmp     edx, 1
        je      .error
        mov     edx, 1
        jmp     .new_digit
    

    .negative:
        sub     ebx, eax
        jo      .error
        jmp     .new_digit
    
    .positive: 
        add     ebx, eax
        jo      .error
        jmp     .new_digit


    .error:
        stc

    .end:
        pop     edx
        pop     ecx
        pop     ebx
        pop     edi
        pop     esi

        ret


WriteInt:

    .end:
        ret


ReadInt64:

    .end:
        ret


WriteInt64:

    .end:
        ret


ReadBin:

    .end:
        ret


WriteBin:

    .end:
        ret


ReadBin64:

    .end:
        ret


WriteBin64:

    .end:
        ret


ReadHex:

    .end:
        ret


WriteHex:

    .end:
        ret


ReadHex64:

    .end:
        ret


WriteHex64:

    .end:
        ret



main:
    mov     esi, str_a_text
    call    WriteStr

    call    ReadInt

    ret
    
section .data
    str_a_text db "A = ", 0

section .bss
    str_a   resb 256