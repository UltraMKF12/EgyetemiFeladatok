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
main:
    ;beolvas egy előjeles 32 bites egész számot 10-es számrendszerben;
    mov     esi, beolvas_32
    call    WriteStr
    call    ReadInt
    call    NewLine
    mov     ebx, eax

    ;kiírja a beolvasott értéket 10-es számrendszerben előjeles egészként, 
    ;komplementer kódbeli ábrázolását 16-os 
    ;és kettes számrendszerben
    
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
    call    NewLine

    ;beolvas egy 32 bites hexa számot;
    mov     esi, beolvas_hexa
    call    WriteStr
    call    ReadHex
    call    NewLine
    mov     ecx, eax

    ;kiírja a beolvasott értéket 10-es számrendszerben előjeles egészként, 
    ;komplementer kódbeli ábrázolását 16-os 
    ;és kettes számrendszerben;
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
    call    NewLine

    ;beolvas egy 32 bites bináris számot;
    mov     esi, beolvas_bin
    call    WriteStr
    call    ReadBin
    call    NewLine
    mov     edx, eax

    ;kiírja a beolvasott értéket 10-es számrendszerben előjeles egészként, 
    ;komplementer kódbeli ábrázolását 16-os 
    ;és kettes számrendszerben;
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
    call    NewLine

    ;kiírja a három beolvasott érték összegét 10-es számrendszerben előjeles egészként, 
    ;komplementer kódbeli ábrázolását 16-os 
    ;és kettes számrendszerben
    mov     eax, ebx
    mov     esi, kiir_32
    call    WriteStr
    call    WriteInt
    call    NewLine
    mov     eax, ecx
    mov     esi, kiir_32
    call    WriteStr
    call    WriteInt
    call    NewLine
    mov     eax, edx
    mov     esi, kiir_32
    call    WriteStr
    call    WriteInt
    call    NewLine

    mov     eax, ebx
    mov     esi, kiir_hexa
    call    WriteStr
    call    WriteHex
    call    NewLine
    mov     eax, ecx
    mov     esi, kiir_hexa
    call    WriteStr
    call    WriteHex
    call    NewLine
    mov     eax, edx
    mov     esi, kiir_hexa
    call    WriteStr
    call    WriteHex
    call    NewLine

    mov     eax, ebx
    mov     esi, kiir_bin
    call    WriteStr
    call    WriteBin
    call    NewLine
    mov     eax, ecx
    mov     esi, kiir_bin
    call    WriteStr
    call    WriteBin
    call    NewLine
    mov     eax, edx
    mov     esi, kiir_bin
    call    WriteStr
    call    WriteBin
    call    NewLine

    ret
    
section .data
    beolvas_32      db  "Beolvas[32bit] = ", 0
    beolvas_hexa    db  "Beolvas[Hexa] = ", 0
    beolvas_bin     db  "Beolvas[Binaris] = ", 0
    kiir_32        db  "Kiir[32bit] >> ", 0
    kiir_hexa      db  "Kiir[Hexa] >> ", 0
    kiir_bin       db  "Kiir[Binaris] >> ", 0