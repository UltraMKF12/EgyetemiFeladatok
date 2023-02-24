; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: strpelda

;A stringek olvasását egyszerre lehet bemutatni a stringeken végzett műveletekkel.  
;Mindkét stringnek kiírjuk a hosszát, kompaktált formáját, 
;majd a kompaktált formát kis betűkre alakítva és nagy betűkre alakítva. 
;Végül hozzáfűzzük az első string nagybetűs verziójához a második string kisbetűs verzióját 
;és kiírjuk a hosszával együtt.

; Compile:
; compile_module.bat strpelda

%include 'ionum.inc'
%include 'iostr.inc'
%include 'strings.inc'

global main

section .text
main:
    ;megfelelő üzenet kiíratása után beolvasunk egy stringet;
    mov     esi, beolvas_string
    call    WriteStr
    mov     esi, str_a
    mov     ecx, 256
    call    ReadLnStr

    ;kiírjuk a hosszát;
    mov     esi, hossz
    call    WriteStr
    mov     esi, str_a
    call    StrLen
    call    WriteInt
    call    NewLine

    ;kiírjuk a tömörített formáját;
    mov     esi, tomoritett
    call    WriteStr
    mov     esi, str_a
    mov     edi, str_a_compact
    call    StrCompact
    mov     esi, edi
    call    WriteStr
    call    NewLine

    ;kiírjuk a tömörített formáját kisbetűkre alakítva;
    push    esi
    mov     esi, kisbetu
    call    WriteStr
    pop     esi
    call    StrLower
    call    WriteLnStr
    call    NewLine


    ;megfelelő üzenet kiíratása után beolvasunk egy stringet;
    mov     esi, beolvas_string
    call    WriteStr
    mov     esi, str_b
    mov     ecx, 256
    call    ReadLnStr

    ;kiírjuk a hosszát;
    mov     esi, hossz
    call    WriteStr
    mov     esi, str_b
    call    StrLen
    call    WriteInt
    call    NewLine

    ;kiírjuk a tömörített formáját;
    mov     esi, tomoritett
    call    WriteStr
    mov     esi, str_b
    mov     edi, str_b_compact
    call    StrCompact
    mov     esi, edi
    call    WriteStr
    call    NewLine

    ;kiírjuk a tömörített formáját nagybeture alakítva;
    push    esi
    mov     esi, nagybetu
    call    WriteStr
    pop     esi
    call    StrUpper
    call    WriteLnStr
    call    NewLine

    ;létrehozunk a memóriában egy új stringet: 
    ;az első string nagybetűs verziójához hozzáfűzzük a második string kisbetűs verzióját;
    mov     esi, str_a
    call    StrUpper
    mov     esi, str_b
    call    StrLower
    mov     edi, str_c
    mov     [str_c], byte 0
    mov     esi, str_a
    call    StrCat

    mov     esi, str_b
    call    StrCat

    ;kiírjuk a létrehozott stringet;
    mov     esi, kiir_string
    call    WriteStr
    mov     esi, str_c
    call    WriteStr
    call    NewLine

    ;kiírjuk a létrehozott string hosszát;
    mov     esi, hossz
    call    WriteStr
    mov     esi, str_c
    call    StrLen
    call    WriteInt

    ret
    
section .data
    beolvas_string  db  "Beolvas[string] = ", 0
    kiir_string     db  "Kiir[string] >> ", 0
    hossz           db  "Hossz >> ", 0
    tomoritett      db  "Tomoritett >> ", 0
    kisbetu         db  "Kisbetu >> ", 0
    nagybetu         db  "Nagybetu >> ", 0

section .bss
    str_a           resb 256
    str_a_compact   resb 256
    str_b           resb 256
    str_b_compact   resb 256
    str_c           resb 256