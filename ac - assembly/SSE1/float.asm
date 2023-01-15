%include 'mio.inc'
%include 'io.inc'

global main

section .text
main:
    call    ReadFloat
    jc      .hiba
    call    mio_writeln
    call    io_writeflt
    call    mio_writeln
    call    WriteFloat
    jmp     .return

    .hiba:
        call    mio_writeln
        push    eax
        mov     eax,hiba_uzenet
        call    mio_writestr
        pop     eax
    .return:
        ret

ReadFloat:
     
    pusha                     

    sub     esp,100
    mov     esi,esp
    
    ;lementem a stack "moge a karakterlancot, amit beolvasok"
    xor     eax,eax
    xor     ebx,ebx
    xor     ecx,ecx
    xor     edx,edx

    xorps   xmm0,xmm0     ;egesz resz regisztere
    xorps   xmm1,xmm1     ;elojel regisztere
    xorps   xmm2,xmm2     ;tort resz regisztere
    xorps   xmm3,xmm3     ;segedregiszter
    xorps   xmm4,xmm4     ;segedregiszter

    .beolvas_karakter:
        xor     eax,eax
        call    mio_readchar

        ;on_enter
        cmp     eax,13
        je      .ellenoriz

        ;on_backspace
        cmp     al,8
        je      .torol_karakter
        jmp     .lement_karakter

        .torol_karakter:
        ;a kepernyon letorlom a karaktert
        call    mio_writechar
        mov     al,32
        call    mio_writechar
        mov     al,8
        call    mio_writechar
        dec     ecx
        cmp     ecx,0
        jnl     .nem_gond
        mov     ecx,0
        .nem_gond:
        jmp     .beolvas_karakter

        .lement_karakter:
        call    mio_writechar
        mov     [esi+ecx],al
        inc     ecx
        jmp     .beolvas_karakter

    .ellenoriz:
        ;ellenorzom ha van elojele
        mov     [esi+ecx],byte 0
        cmp     [esi], byte'-'
        je      .negativ_float
        cmp     [esi], byte'+'
        je      .pozitiv_float
        ;ha nincs elojele akkor pozitiv es a 0.karaktertol epitem a szamot
        xor     edx,edx
        dec     edx

    ;beallitom az elojelnek szant regiszteremet ( = {-1,1})
    ;a szamot minding pozitivkent epitem fel,majd a legvegen megszorzom az elojelevel
    .pozitiv_float:
        movss    xmm1,[pozitiv]      ;xmm7 az elojel regiszter
        jmp     .felepit_egesz
    .negativ_float:
        movss    xmm1,[negativ]      ;xmm7 az elojel regiszter
        jmp     .felepit_egesz

    .felepit_egesz:
        inc     edx
        xorps    xmm4,xmm4
        ;beolvas kov karakter
        xor     ebx,ebx         
        mov     bl,[esi+edx]

        ;end of string
        cmp     bl,0
        je      .return

        ;ha elertuk a tizedesvesszot
        cmp     bl, '.'
        je      .felepit_tizedes

        ;ha nem szamjegy
        cmp     bl,48
        jl      .hiba
        cmp     bl,57
        jg      .hiba

        sub     ebx,48      ;0...9

        ;szam-felepites
        cvtsi2ss    xmm4,ebx    ;char to int
        mulss       xmm0,[tiz]   ;szamjegy * 10
        addss       xmm0,xmm4   ;(szam*10) + szamjegy

        jmp    .felepit_egesz

    .felepit_tizedes:
        
        movss   xmm3,[pozitiv]      ;mm3 = 1
    
        .felepit_tizedes_ciklus:
    
            inc     edx             ;egybol atugrom a '.' karaktert
            xorps    xmm4,xmm4

            ;beolvas kov karakter
            xor     ebx,ebx         
            mov     bl,[esi+edx]

            ;end of string
            cmp     bl,0
            je      .elojel

            ;ha nem szamjegy
            cmp     bl,48
            jl      .hiba
            cmp     bl,57
            jg      .hiba

            sub     ebx,48      ;0...9


            ;a kovetkezo szamjegyet szorzom a 10 negativ hatvanyaival -1,-2,-3..
            ;majd hozzaadom az eredmenyhez
            ;szam-felepites
            cvtsi2ss    xmm4,ebx    ;char to int
            divss       xmm3,[tiz]  ;xmm 3 = 0.1, 0.01 , 0.001 ...
            mulss       xmm4,xmm3   ;szamjegy * 0.1
            addss       xmm0,xmm4   ;egeszresz + 0,szamjegy...

            jmp    .felepit_tizedes_ciklus
    
    .elojel:
        mulss   xmm0,xmm1
        jmp     .return

    .hiba:
        add     esp,100
        popa
        stc
        ret 

    .negalas:
        neg     eax

    ;visszaalitod a stacket
    .return:
        add     esp,100
        popa
        clc
        ret 

WriteFloat:
    pusha

    xorps       xmm1,xmm1       ;elojelregiszter
    xorps       xmm2,xmm2
    xorps       xmm3,xmm3
    xorps       xmm4,xmm4

    ;vizsgalom a szam elojelet
    xor         eax,eax
    movd        eax,xmm0
    rol         eax,1
    mov         ebx,1
    and         ebx,eax

    ;ha negativ akkor kiirom a '-' jelet, es ugy kezelem mintha egy pozitiv lenne
    cmp         ebx,0
    je          .egesz_kiiras
    mov         eax,'-'
    call        mio_writechar
    mulss       xmm0,[negativ]

    ;kiirom az egeszreszt
    .egesz_kiiras:
    xor         eax,eax
    cvttss2si   eax,xmm0
    call        WriteInt

    ;kiirom a tizedesvesszot
    mov         eax,'.'
    call        mio_writechar

    ;elokeszulok a tizedesek kiirasara
    roundss     xmm1,xmm0,3
    subss       xmm0,xmm1

    mov         ecx,6
    .tortresz_kiiras:
        xorps       xmm1,xmm1
        xor         eax,eax   
        mulss       xmm0,[tiz]
        roundss     xmm1,xmm0,3
        subss       xmm0,xmm1
        cvttss2si   eax,xmm1
        add         eax,48
        call        mio_writechar
        loop        .tortresz_kiiras

    popa
    ret

WriteInt:
    push    eax
    push    ebx
    push    ecx
    push    edx

    ;negativ -> postitve
    ;csak kiirom  a'-' jelet
    cmp     eax,0
    ;ha pozitiv szamom van-
    jge      .Pos

    ;ha negativ, kiirom a minuszt
    push    eax
    mov     al,45
    call    mio_writechar
    pop     eax

    ;poztiv binaris alajara hozom
    neg     eax
    
    .Pos:
        xor     ebx,ebx
        xor     ecx,ecx
        mov     ebx,10

        .osztom:
            cdq
            idiv     ebx
            push    edx
            inc     ecx
            cmp     eax,0
            jne     .osztom
        
        .kiir:
            pop     eax
            add     eax,48
            call    mio_writechar
            loop    .kiir


    pop     edx
    pop     ecx
    pop     ebx
    pop     eax
    ret
section .data
    tiz dd 10.0
    pozitiv dd 1.0
    negativ dd -1.0
    hiba_uzenet db 'Hiba: Rossz bemenet!',0

section .bss
