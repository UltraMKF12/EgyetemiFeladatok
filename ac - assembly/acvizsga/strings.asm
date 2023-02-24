; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: strings

; Compile:
; compile_run_module.bat strings

global StrLen
global StrCat
global StrUpper
global StrLower
global StrCompact

section .text
StrLen:
    ; Text ESI
    ; EAX return character

    push        esi
    push        ebx

    xor     eax, eax
    xor     ebx, ebx

    .next_character:
        lodsb

        cmp     al, 0
        je      .end

        inc     ebx
        jmp     .next_character

    .end:
        mov     eax, ebx
        pop     ebx
        pop     esi
        ret

StrCat:
    ;EDI = EDI + ESI
    pusha

    push    esi
    mov     esi, edi
    call    StrLen
    pop     esi

    add     edi, eax                                ; Eljutni a 0 karakterig, hogy a végére másoljunk EDI-ben

    call    StrLen                                  ; Megkapni hány karaket van ESI-ben.
    mov     ecx, eax

    .copy:
        movsb
        loop    .copy

    .end:
        popa
        ret

StrUpper:
    ; Converts 'a'-'z' to 'A'-'Z'
    ; Uses ESI
    pusha

    xor     eax, eax

    .new_character:
        lodsb

        cmp     al, 0
        je      .end

        cmp     al, 'a'
        jge     .convert

        jmp     .new_character

    .convert:
        cmp     al, 'z'
        jg      .new_character

        sub     al, " "                                 ;Nagy és kisbetü között dec-32 különbség van. Ami pont a SPACE karakter
        mov     [esi-1], al
        jmp     .new_character
        
    .end:
        popa
        ret

StrLower:
    ; Converts 'A'-'Z' to 'a'-'z'
    ; Uses ESI
    pusha

    xor     eax, eax

    .new_character:
        lodsb

        cmp     al, 0
        je      .end

        cmp     al, 'A'
        jge     .convert

        jmp     .new_character

    .convert:
        cmp     al, 'Z'
        jg      .new_character

        add     al, " "                                 ;Nagy és kisbetü között dec-32 különbség van. Ami pont a SPACE karakter
        mov     [esi-1], al
        jmp     .new_character
        
    .end:
        popa
        ret

StrCompact:
    ;Copies ESI to EDI, except 9, 13, 10, and space character
    pusha

    xor     eax, eax

    .new_character:
        lodsb

        cmp     al, 0
        je      .end

        cmp     al, 9
        je      .delete
        cmp     al, 10
        je      .delete
        cmp     al, 13
        je      .delete
        cmp     al, " "
        je      .delete

        stosb

    .delete:
        jmp     .new_character

    .end:
        mov     al, 0
        stosb
        popa
        ret