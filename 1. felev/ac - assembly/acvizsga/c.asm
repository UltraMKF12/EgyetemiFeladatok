%include "iostr.inc"
%include "strings.inc"

;nasm -f win32 c.asm
;nlink iostr.obj ionum.obj strings.obj -lmio c.obj -o c.exe

global main
section .text
eltolas:
    pushad
    ;ebx eltolas mennyisege

    ;Megkeresni az utolso karaktert
    ;Utolso karaktertol visszafele eltolni mindent

    mov     edi, esi
    dec     edi

    cmp     [esi], byte 0
    je      .end

    .nullas_kereses:
        xor     eax, eax
        lodsb

        cmp     al, 0
        jne     .nullas_kereses
    
    .eltolas:
        cmp     esi, edi
        je      .end
        
        mov     al, [esi]
        mov     [esi+ebx], al
        dec     esi
        jmp     .eltolas

    .end:
        popad

feladat:
    pushad
    ;EBX - hanyadik szo utan kell betenni
    ;ECX - jelenlegi szo szam
    ;ESI - jelenlegi szoveg
    ;EDX - UTOLSO KARAKTER
    mov     ebx, eax
    xor     eax, eax
    xor     ecx, ecx
    xor     edx, edx

    ;Az elso betu sohase lehet szo barmilyen karakter is legyen
    lodsb
    .szo_szamlalas:
        ;Igy akkor 0 karakter is szonak szamit, a legvegen
        cmp     edx, 1
        jge     .end

        xor     eax, eax
        lodsb

        cmp     al, 0
        je      .utolso_szo

        cmp     al, ' '
        je      .szo_ellenorzes
        cmp     al, ','
        je      .szo_ellenorzes
        cmp     al, ''
        je      .szo_ellenorzes

        jmp     .szo_szamlalas

    .utolso_szo:
        inc     edx
        jmp     .szo_ellenorzes

    .szo_ellenorzes:
        mov     al, [esi-2]

        cmp     al, "A"
        jl      .szo_szamlalas
        cmp     al, "Z"
        jg      .kis_betu
        jmp     .igen_betu

        .kis_betu:
        cmp     al, "a"
        jl      .szo_ellenorzes
        cmp     al, "z"
        jg      .szo_ellenorzes

        .igen_betu:
        inc     ecx
        cmp     ecx, ebx
        je      .beillesztes
        jmp     .szo_szamlalas

    .beillesztes:
        dec     esi
        call    eltolas
        mov     [esi], byte 0
        mov     edi, esi
        mov     esi, s
        call    StrCat
        jmp     .end


    .end:
        popad
        ret

main:
    mov     ecx, 255
    
    mov     esi, szo
    call    WriteStr
    mov     esi, s
    call    ReadStr
    call    StrLen
    call    NewLine
    call    NewLine

    mov     ecx, 250
    .ismetles:
        mov     esi, szoveg
        call    WriteStr
        mov     esi, t
        call    ReadStr
        call    NewLine

        cmp     [esi], byte ''
        je      .ismetles_vege

        call    feladat

        mov     esi, modositva
        call    WriteStr
        mov     esi, t
        call    WriteStr
        call    NewLine
        call    NewLine
        
        jmp     .ismetles
    .ismetles_vege:
    ret

section .data
    szo     db "Szo = ", 0
    szoveg  db "Szoveg = ", 0
    modositva db "Modositva >> ", 0

section .bss
    s   resb 256
    t   resb 500