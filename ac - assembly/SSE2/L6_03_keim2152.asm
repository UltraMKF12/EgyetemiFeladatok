;Kovacs Elek Akos
;513/1
;2152
;Feladat : Olvassunk be két (A és B) azonos hosszúságú lebegőpontos értékekből álló tömböt (max. 256 elem). 
;Olvassuk be a tömbök hosszát (n integer, 4<=n<=256), majd a tömbök elemeit, minden elemet 
;új sorból (azaz 2n lebegőpontos értéket olvasunk be). A tömbök minden elemére páronként végezzük el az alább 
;megadott műveleteket, tároljuk el az eredményeket egy másik tömbben, végül pedig írjuk ki azt. 
;A feladat lényege, hogy ne skaláris utasításokat használjuk, hanem vektorosokat (azaz pl. ADDSS helyett ADDPS-t 
;használjunk 4 db. számpár párhuzamos összeadására).

%include 'io.inc'

global main

section .text
main:

    ;egyenlet kiiras
    push    eax
    mov     eax,str_egyenlet
    call    io_writestr
    call    io_writeln
    pop     eax

    xor     esi,esi     ;index
    xor     ebx,ebx     ;N
    xor     edx,edx
    ;beolvasom az N-et
    push    eax
    mov     eax,str_n
    call    io_writestr
    ;call    io_writeln
    pop     eax

    call    io_readint
    mov     ebx,eax
    cmp     eax,0
    je      .hiba

    ;megnezem ha N4l oszthato
    push    ebx
    mov     ebx,4
    cdq
    idiv     ebx
    cmp     edx,0
    jne     .hiba
    pop     ebx
    
    xor     edx,edx
    xor     eax,eax


    ;beolvasom az elso tombot
    mov     ecx,ebx
    .beolvas_A:

        ;elem beolvas
        push    eax
        mov     eax,str_first
        call    io_writestr
        ;call    io_writeln
        pop     eax

        xorps   xmm0,xmm0
        call    io_readflt
        movss  [arr_A + esi],xmm0
        add     esi,4
        loop    .beolvas_A

    ;beolvasom a masodik tombot
    mov     ecx,ebx
    xor     esi,esi
    .beolvas_B:

        ;elem beolvas
        push    eax
        mov     eax,str_sec
        call    io_writestr
        ;call    io_writeln
        pop     eax

        xorps   xmm0,xmm0
        call    io_readflt
        movss  [arr_B + esi],xmm0
        add     esi,4   
        loop    .beolvas_B

    ;muvelet
    xor     esi,esi       ;index
    xor     ecx,ecx
    xor     edx,edx
    mov     ecx,4
    mov     eax,ebx
    cdq
    idiv     ecx

    mov     ecx,eax
    .muvelet:
        xorps  xmm0,xmm0
        xorps  xmm1,xmm1
        xorps  xmm2,xmm2
        xorps  xmm3,xmm3
        xorps  xmm4,xmm4
        xorps  xmm5,xmm5

        movups  xmm0,[arr_A + esi]      ;olvas a
        movups  xmm1,[arr_B + esi]      ;olvas b
        
        
        ;a^2 = xmm2
        movups  xmm2,[egy]
        mulps   xmm2,xmm0
        mulps   xmm2,xmm0

        ;- 1.4 * b * a = xmm3
        movups  xmm3,[negegy]
        mulps   xmm3,[egynegy]
        mulps   xmm3,xmm0
        mulps   xmm3,xmm1

        ;-sqrt(a / b - 2.1) = xmm4
        movups  xmm4,xmm0
        divps   xmm4,xmm1
        subps   xmm4,[kettegy]
        sqrtps  xmm4,xmm4
        mulps   xmm4,[negegy]

        ;max(a - b, b)  = xmm5
        movups  xmm5,xmm0
        subps   xmm5,xmm1
        maxps   xmm5,xmm1

        ;E(a,b)
        xorps   xmm6,xmm6
        addps   xmm6,xmm2
        addps   xmm6,xmm3
        addps   xmm6,xmm4
        addps   xmm6,xmm5

        movups [arr_C + esi],xmm6

        ;novelem az indexet
        add     esi,16

        loop    .muvelet

    mov     ecx,ebx
    xor     esi,esi
    .kiir:

        ;elem kiir
        push    eax
        mov     eax,str_meg
        call    io_writestr
        ;call    io_writeln
        pop     eax

        xorps   xmm0,xmm0
        movups  xmm0,[arr_C+esi]
        add     esi,4
        call    io_writeflt
        call    io_writeln
        loop    .kiir

    jmp     .return
        

    .hiba:
        pop     eax
        mov     eax,str_hiba
        call    io_writestr
        ret

    .return:
    ret

section .bss
    arr_A   resd    256
    arr_B   resd    256 
    arr_C   resd    256 

section .data
    egy         dd   1.0,1.0,1.0,1.0
    negegy      dd   -1.0,-1.0,-1.0,-1.0
    egynegy     dd   1.4,1.4,1.4,1.4
    kettegy     dd   2.1,2.1,2.1,2.1
    str_egyenlet    db   'E(a,b) = a^2 - 1.4 * b * a - sqrt(a / b - 2.1) + max(a - b, b)',0
    str_hiba        db    'Hiba, rossz bemenet N-re',0
    str_first       db    'Elso tomb eleme:',0
    str_sec         db    'Masodik tomb eleme:',0
    str_meg         db    'Egyenlet megoldasai:',0
    str_n           db    'n = ',0