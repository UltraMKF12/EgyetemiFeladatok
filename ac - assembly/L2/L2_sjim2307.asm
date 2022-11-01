; Széri József - sjim2307
; 514/2

; Labor: 2

;Írjunk meg egy-egy ASM alprogramot (függvényt, eljárást) 
;32 bites, előjeles egész (decimális), 
;illetve 32 bites, pozitív hexa számok beolvasására és kiírására.

; Compile:
; nasm -f win32 L2\L2_sjim2307.asm
; nlink L2\L2_sjim2307.obj -lmio -lio -o L2\L2_sjim2307.exe
; actest L2 L2\L2_sjim2307.exe

%include 'mio.inc'
%include 'io.inc'

global main

section .text
beolvas_decimal32:
    ;AL                                   0000 0000 - FF
    ;AX                         0000 0000 0000 0000 - FFFF
    ;EAX    0000 0000 0000 0000 0000 0000 0000 0000 - FFFF FFFF
    

    xor     ecx, ecx ;le kell nullázni az eax-et.

.uj_karakter:
    call    mio_readchar

    ;ENTER
    cmp     al, 13
    je      .end

    ;Kiirni a beirt karaktert
    call    mio_writechar

    ;Leellenőrizni, hogy a beirt karakter szám.
    ; 0 - karatker
    cmp     al, 48
    jl      .hiba
    ; 9 - karatker
    cmp     al, 57
    jg      .hiba

    ;Ha szam akkor szorozzuk a jelenlegit 10el es hozzaadjuk a beolvasottat
    push    ebx
    mov     ebx, 10
    imul    ecx, ebx
    pop     ebx
    sub     al, 48 ;ascii -> int
    add     cl, al

    jmp     .uj_karakter


    .hiba:
        ;ide hibakezelest
    .end:
        ret



main:
    call    beolvas_decimal32
    call    mio_writeln
    mov     eax, ecx
    call    io_writeint
    ret