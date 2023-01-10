; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: ionum

; Compile:
; compile_module.bat ionum

%include 'iostr.inc'
%include 'mio.inc'

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
    ;EAX beolvasasa 32 bites bináris alakban
    push    esi
    sub     esp, 500
    mov     esi, esp
    call    ReadStr
    
    xor     ecx, ecx                        ;counter
    xor     eax, eax
    xor     ebx, ebx

    .number_build:
        cmp     ecx, 32
        jge     .error

        lodsb
        cmp     al, '0'
        jl      .error
        cmp     al, '1'
        jg      .error

        sub     al, '0'

        shl     ebx, 1
        add     bl, al

        inc     ecx
        jmp     .number_build

    .error:
        add     esp, 500
        pop     esi

        mov     eax, ebx
        stc
        ret
    .end:
        add     esp, 500
        pop     esi

        mov     eax, ebx
        ret


WriteBin:
    ;EAX kiiratása 32 bites bináris alakban
    ;0111 1011 0101 0100 1101 0010 1010 1011
    ;8 csoport, csoportonként 4 számjegy
    pusha

    mov     ecx, 32                                 ;32 bit betevese stackbe
    mov     ebx, 2                                  ;Osztasi maradek szamlalasara

    .beolvasas:
        ;32-bit beolvasasa stackbe
        xor     edx, edx
        div     ebx
        push    edx                                 ;1 vagy 0 lehet
        
        loop    .beolvasas
    
    mov     ecx, 32                                 ;32 bitet irunk ki.
    mov     ebx, 4                                  ;4 bitenként space ellenőrzés
    .kiiras:
        ;Kiirni stackből a biteket
        pop     eax
        add     eax, '0'
        call    mio_writechar

        ;4 bitenként kell egy space karakter
        mov     eax, ecx
        xor     edx, edx
        div     ebx
        cmp     edx, 1
        jne     .kiiras_veg

        mov     al, ' '
        call    mio_writechar
        
    .kiiras_veg:
        loop    .kiiras

    .end:
        popa
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
    call    ReadBin
    call    NewLine
    call    WriteBin

    ret
    
section .data
    str_a_text db "A = ", 0

section .bss
    str_a   resb 256