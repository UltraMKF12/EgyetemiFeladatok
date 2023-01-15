;Kovacs Elek Akos
;513/1
;2152
;Feladat : Készítsünk el egy-egy olyan eljárást, 
;amely 32 bites, egyszeres pontosságú lebegőpontos értéket 
;olvas be és ír ki, hagyományos (±1234.5678) és exponenciális 
;formában (±1.234567e±12) egyaránt. Az exponenciális formában 
;a pozitív előjelek opcionálisok (tehát ez is helyes: 1.37e2), 
;az e betű pedig lehet kicsi és nagy is.

%include 'mio.inc'

global main

section .text
main:
    
    mov     eax,E
    call    mio_writestr
    call    mio_writeln

    ;beolvas a
    mov     eax,read_normal
    call    mio_writestr
    mov     eax,a
    call    mio_writestr
    xorps   xmm0,xmm0
    call    ReadFloat
    jc      .hiba
    call    mio_writeln
    movd    eax,xmm0
    push    eax

    ;beolvas b
    mov     eax,read_exp
    call    mio_writestr
    mov     eax,b
    call    mio_writestr
    call    ReadFloatE
    jc      .hiba
    call    mio_writeln
    movd    eax,xmm0
    push    eax

    ;beolvas c
    mov     eax,read_normal
    call    mio_writestr
    mov     eax,c
    call    mio_writestr
    call    ReadFloat
    jc      .hiba
    call    mio_writeln
    movd    eax,xmm0
    push    eax

    ;beolvas d
    mov     eax,read_exp
    call    mio_writestr
    mov     eax,d
    call    mio_writestr
    call    ReadFloatE
    jc      .hiba
    call    mio_writeln
    movd    eax,xmm0
    push    eax

    ;xmm1 = b*b
    mov     eax,[esp+8]
    movd    xmm0,eax
    movss   xmm1,[pozitiv]
    mulss   xmm1,xmm0
    mulss   xmm1,xmm0

    ;xmm1 = (b^2 + a - c)
    mov     eax,[esp+12]
    movd    xmm2,eax
    addss   xmm1,xmm2

    mov     eax,[esp+4]
    movd    xmm2,eax
    subss   xmm1,xmm2

    ;(b^2 + a - c) / d
    mov     eax,[esp]           ;eax = d
    movd    xmm2,eax
    divss   xmm1,xmm2

    ;xmm2 = a*a
    mov     eax,[esp+12]        ;eax = a
    movd    xmm3,eax
    movss   xmm2,[pozitiv]
    mulss   xmm2,xmm3
    mulss   xmm2,xmm3

    ;xmm3 = (d - a^2 + b)
    mov     eax,[esp]         ;eax = d
    movd    xmm3,eax
    subss   xmm3,xmm2
    movss   xmm2,xmm3

    mov     eax,[esp+8]           ;eax = b
    movd    xmm3,eax
    addss   xmm3,xmm2

    ;xmm2 = min(d,2.1)
    mov     eax,[esp]
    movd    xmm2,eax
    movss   xmm4,[kettopontegy]
    minss   xmm2,xmm4

    ;xmm3 = (d - a^2 + b) / min(d, 2.1)
    divss  xmm3,xmm2

    ;xmm1 =  E(a,b,c,d) = (b^2 + a - c) / d - (d - a^2 + b) / min(d, 2.1) 
    subss   xmm1,xmm3

    movss   xmm0,xmm1
    mov     eax,read_normal
    call    mio_writestr
    mov     eax,E
    call    mio_writestr
    mov     eax,eq
    call    mio_writestr
    call    WriteFloat

    call    mio_writeln

    mov     eax,read_exp
    call    mio_writestr
    mov     eax,E
    call    mio_writestr
    mov     eax,eq
    call    mio_writestr
    call    WriteFloatE


    jmp     .return

    .hiba:
        call    mio_writeln
        push    eax
        mov     eax,hiba_uzenet
        call    mio_writestr
        pop     eax
    .return:
    ;!!!! empty stack
        pop     eax
        pop     eax
        pop     eax
        pop     eax
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

ReadFloatE:
     
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
    xorps   xmm5,xmm5     ;exponens elojele

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

            ;felepitem az exponenst
            cmp     bl,'e'
            je      .elojel
            cmp     bl,'E'
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
        jmp     .exponens

    .exponens:
        xor     ecx,ecx                 ;ecxbe epitem fel az exponenst

        inc     edx                     ;nezem az e vagy E utani karaktert
        cmp     [esi+edx],byte '+'           ;ha egy '+' jel, megjegyzem hogy pozitiv
        jne     .p1
        movss   xmm5,[pozitiv]
        jmp     .felepit_exponens

        .p1:
        cmp     [esi+edx],byte '-'           ;ha egy '-' jel akkor negativ
        jne     .nincs_elojel
        movss   xmm5,[negativ]
        jmp     .felepit_exponens

        .nincs_elojel:
        movss   xmm5,[pozitiv]   
        dec     edx
        .felepit_exponens:                            ;ha semmilyen jel nincs, akkor felepitjuk mint pozitiv
            inc     edx

            ;beolvas kovetekezo karakter
            xor     ebx,ebx                           
            mov     bl,[esi+edx]

            ;end of string
            cmp     bl,0
            je      .exponens_hozzaad                   ;felepitem a szamot klasszikus modon

            ;ha nem szamjegy
            cmp     bl,48
            jl      .hiba
            cmp     bl,57
            jg      .hiba

            sub     ebx,48      ;0...9

            ;felepitem az exponenst (ecx-et)
            imul    ecx,10
            add     ecx,ebx
            
            jmp     .felepit_exponens


    .exponens_hozzaad:
        ;xorps   xmm1,xmm1
        ;movss   xmm1,[pozitiv]          ;ha nem pozitiv akkro biztos hogy negativ az elojele
        cmp      ecx,0
        je       .return

        comiss     xmm5,[pozitiv]
        jne     .negativ_exponens

        ;pozitiv exponens felepit
        mulss   xmm0,[tiz]
        loop    .exponens_hozzaad
        jmp     .return
        ;negativ exponens felepit
        .negativ_exponens:
        divss   xmm0,[tiz]

        loop    .exponens_hozzaad
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

    movss       xmm7,xmm0
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

    movss       xmm0,xmm7
    popa
    ret

WriteFloatE:
    pusha

    movss       xmm7,xmm0
    xorps       xmm1,xmm1       ;elojelregiszter
    xorps       xmm2,xmm2
    xorps       xmm3,xmm3
    xorps       xmm4,xmm4
    xor     esi,esi                         ;esibe szamolom hanyszor kellett szorozni/osztani


    ;vizsgalom a szam elojelet
    xor         eax,eax
    movd        eax,xmm0
    rol         eax,1
    mov         ebx,1
    and         ebx,eax

    ;ha negativ akkor kiirom a '-' jelet, es ugy kezelem mintha egy pozitiv lenne
    cmp         ebx,0
    je          .tomorit
    mov         eax,'-'
    call        mio_writechar
    mulss       xmm0,[negativ]

    ;e-s alakra hozom

    .tomorit:
        ;ha nem a 0.0 es 10.0 kozott van akkor szorzom/osztom
        comiss       xmm0,[zero]             ;ha kisebb mint 0 osztani kell
        jb         .tomorit_szorzas
        comiss       xmm0,[tiz]              ;ha nagyobb vagy egyenlo mint 10 szorozni kell
        jae        .tomorit_osztas
        jmp        .tomorit_vege            ;ha kozte van akkor OK, kiléphetünk
        
    .tomorit_szorzas:
        mulss       xmm0,[tiz]
        dec         esi
        jmp         .tomorit
    .tomorit_osztas:
        divss       xmm0,[tiz]
        inc         esi
        jmp         .tomorit
    .tomorit_vege:

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

    mov         ecx,4
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

    ;kiiratom az e-s részét
    mov     al,'e'
    call    mio_writechar
    mov     eax,esi
    call    WriteInt

    movss   xmm0,xmm7

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
    zero    dd 0.0
    kettopontegy dd 2.1
    hiba_uzenet db 'Hiba: Rossz bemenet!',0
    read_normal db 'Klasszikus lebegopontos szam:',0
    read_exp db 'E alakos lebegopontos szam:',0
    a db 'a = ',0
    b db 'b = ',0
    c db 'c = ',0
    d db 'd = ',0
    E db 'E(a,b,c,d) = (b^2 + a - c) / d - (d - a^2 + b) / min(d, 2.1)',0
    eq db ' = ',0

section .bss
