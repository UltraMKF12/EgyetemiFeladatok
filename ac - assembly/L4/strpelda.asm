; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: iostr

; Compile:
; compile_run_module.bat L4\strpelda

%include 'L4\iostr.inc'

global main

section .text
main:
    mov     esi, str_a_text
    call    WriteStr

    mov     ecx, 20
    mov     esi, str_a
    call    ReadLnStr

    call    WriteStr
    ret
    
section .data
    str_a_text db "A = ", 0

section .bss
    str_a   resb 256