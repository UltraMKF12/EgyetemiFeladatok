; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: iostr

; Compile:
; compile_run.bat L4\iostr

%include 'mio.inc'

global ReadStr
global WriteStr
global ReadLnStr
global WriteLnStr
global NewLine

section .text
ReadStr:
    ;Stores string to ESI
    ;ECX max charcters
    pusha

    xor     eax, eax
    xor     ebx, ebx
    mov     edi, esi

    .new_character:
        call    mio_readchar

        ;ENTER
        cmp     al, 13
        je      .end

        ;BACKSPACE
        cmp     al, 8
        je      .backspace

        inc     ebx
        call    mio_writechar

        ;Check if out of characters to store
        cmp     ebx, ecx
        jg      .new_character

        stosb
        jmp     .new_character

    .backspace:
        ;Don't delete more than it should
        cmp     ebx, 0
        jle     .new_character
        
        mov     al, 8
        call    mio_writechar
        mov     al, " "
        call    mio_writechar
        mov     al, 8
        call    mio_writechar

        dec     ebx

        cmp     ebx, ecx
        jge     .new_character

        dec     edi
        jmp     .new_character

    .end:
        mov     al, 0
        stosb

        popa
        ret

WriteStr:
    ;Write string from ESI to console
    pusha

    xor     eax, eax
    .next_character:
        lodsb

        cmp     al, 0
        je      .end

        call    mio_writechar
        jmp     .next_character

    .end:
        popa
        ret

ReadLnStr:
    call    ReadStr
    call    NewLine
    ret

WriteLnStr:
    call    WriteStr
    call    NewLine
    ret

NewLine:
    pusha
    xor     eax, eax
    mov     al, 13
    call    mio_writechar
    mov     al, 10
    call    mio_writechar
    popa
    ret