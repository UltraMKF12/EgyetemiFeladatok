; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: iopelda

; Compile:
; compile_module.bat iopelda

%include 'ionum.inc'
%include 'iostr.inc'

global main

section .text
Kiiras:
    ;EAX-et kiirja
    mov     esi, kiir_32
    call    WriteStr
    call    WriteInt
    call    NewLine

    mov     esi, kiir_hexa
    call    WriteStr
    call    WriteHex
    call    NewLine

    mov     esi, kiir_bin
    call    WriteStr
    call    WriteBin
    call    NewLine

    ret


Beolvasas_32:
    .kezdet:
        mov     esi, beolvas_32
        call    WriteStr
        call    ReadInt
        jc      .hiba
        jmp     .veg
    
    .hiba:
        call    NewLine
        mov     esi, hiba
        call    WriteStr
        call    NewLine
        jmp     .kezdet

    .veg:
        call    NewLine
        ret


Beolvasas_hexa:
    .kezdet:
        mov     esi, beolvas_hexa
        call    WriteStr
        call    ReadHex
        jc      .hiba
        jmp     .veg
    
    .hiba:
        call    NewLine
        mov     esi, hiba
        call    WriteStr
        call    NewLine
        jmp     .kezdet

    .veg:
        call    NewLine
        ret


Beolvasas_bin:
    .kezdet:
        mov     esi, beolvas_bin
        call    WriteStr
        call    ReadBin
        jc      .hiba
        jmp     .veg
    
    .hiba:
        call    NewLine
        mov     esi, hiba
        call    WriteStr
        call    NewLine
        jmp     .kezdet

    .veg:
        call    NewLine
        ret


main:
    call Beolvasas_32
    mov     ebx, eax
    call    Kiiras
    call    NewLine


    call    Beolvasas_hexa
    mov     ecx, eax
    call    Kiiras
    call    NewLine

    call    Beolvasas_bin
    mov     edx, eax
    call    Kiiras
    call    NewLine

    mov     eax, ebx
    add     eax, ecx
    add     eax, edx
    call    Kiiras
    call    NewLine

    ret
    
section .data
    beolvas_32      db  "Beolvas[32bit] = ", 0
    beolvas_hexa    db  "Beolvas[Hexa] = ", 0
    beolvas_bin     db  "Beolvas[Binaris] = ", 0
    kiir_32         db  "Kiir[32bit] >> ", 0
    kiir_hexa       db  "Kiir[Hexa] >> ", 0
    kiir_bin        db  "Kiir[Binaris] >> ", 0
    hiba            db  "Hiba", 0