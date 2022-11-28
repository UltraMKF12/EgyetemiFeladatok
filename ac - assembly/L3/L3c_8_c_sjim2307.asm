; Széri József - sjim2307
; 514/2

; Labor: 3
; Feladat: c8

;Készítsünk két assembly programot (NASM), amelyek beolvassák a szükséges karakterláncokat, 
;kiírják a felhasznált szabályt (mint üzenetet) és a beolvasott karakterláncokat külön sorokba, 
;majd előállítják és végül kiírják a művelet eredményét, ami szintén egy karakterlánc. 
;Az eredményt nem szabad több részletben kiírni, az egyetlen karakterlánc kell legyen, 
;amit elő kell állítani kiírás előtt! A karakterláncok olvasásához és írásához írjunk alprogramot 
;(a két feladatban különbözőek lesznek)!

;8. [A-ból az összes betű abc sorrendben (ASCII kód szerint), amelyek többször jelennek meg, 
;többször is kerülnek be az eredménybe (pl. "aeca" => "aace", "aAgH" => "AHag")] + 
;[B, melyben a "_" jelt az utána legközelebb található magángangzóra cseréltük,
;ha nincs utána magánhangzó, akkor marad a "_"]


; Compile:
; compile_run.bat L3\L3c_8_c_sjim2307
; actest L3c_8_c L3\L3c_8_c_sjim2307.exe

%include 'mio.inc'

global main

section .text
readStr:
    ;C string beolvasasa
    ; ebx - string
    ; ecx - karakter counter
    ; eax - karakterek

    push    ebx
    push    ecx
    push    edx

    mov     ebx, eax
    xor     ecx, ecx

    .new_character:
        xor     eax, eax
        call    mio_readchar

        ;ENTER
        cmp     al, 13
        je      .end

        call    mio_writechar
        mov     [ebx + ecx], al

        inc     ecx
        jmp     .new_character


    .end:
        mov     [ebx + ecx], byte 0
        mov     eax, ebx

        pop     edx
        pop     ecx
        pop     ebx
        ret

writeStr:
    ;Write C string to console
    push    eax
    push    ebx
    push    ecx

    mov     ebx, eax
    xor     ecx, ecx

    .next_character:
        xor     eax, eax
        mov     al, [ebx + ecx]

        cmp     al, 0
        je      .end

        call    mio_writechar
        inc     ecx
        jmp     .next_character

    .end:
        pop     ecx
        pop     ebx
        pop     eax
        ret


sort_ASCII:
    ;MAXIMUM 255 karakterrel tud dolgozni.
    pusha

    xor     ebx, ebx
    xor     ecx, ecx
    xor     edx, edx
    xor     esi, esi
    xor     edi, edi

    .count_characters:
        mov     bl, [eax + ecx]
        cmp     bl, 0
        je      .sort

        inc     ecx
        jmp     .count_characters

    .sort:
        ;Felcseréléses rendezés:
        ;cl - n - Karakterek száma

        ;esi - i - Jelenlegi pozició
        ;bh - string[i]

        ;edi - j - Hasonlítási pozíció
        ;bl - string[j]

        dec     ecx                                 ;Kell, mivel másként az ascii 0 is belekerül
        xor     ebx, ebx
    
    .sort_outer:
        cmp     ecx, esi                            ;Ha i == n, akkor vége a rendezésnek
        je      .end

        mov     bh, [eax + esi]                  ; bh = string[i]
        mov     edi, esi                          ; j = i

        .sort_inner:
            inc     edi
            mov     bl, [eax + edi]

            cmp     bh, bl
            jg      .swap

            jmp     .sort_inner_end

            .swap:
                mov     [eax + esi], bl
                mov     [eax + edi], bh
                mov     bh, bl
                dec     edi
                jmp     .sort_inner

            .sort_inner_end:
                cmp     ecx, edi
                je     .sort_outer_end

                jmp     .sort_inner

    .sort_outer_end:
        inc     esi
        jmp     .sort_outer

    .end:
        popa
        ret

underscore_switch_vowel:
    ;Kicseréli "_"-t utánna következő magánhangzókra, ha vannak.
    pusha

    xor     ebx, ebx
    xor     ecx, ecx
    xor     edx, edx
    xor     esi, esi
    xor     edi, edi

    jmp     .search_underscore

    .search_underscore:
        mov     bl, [eax + esi]

        cmp     bl, 0
        je      .end

        cmp     bl, "_"
        je     .search_vowel_setup

        inc     esi
        jmp     .search_underscore

    .search_vowel_setup:
        mov     edi, esi
    .search_vowel:
        inc     edi

        mov     bh, [eax + edi]

        cmp     bh, 0
        je      .end

        cmp     bh, "a"
        je      .switch
        cmp     bh, "e"
        je      .switch
        cmp     bh, "i"
        je      .switch
        cmp     bh, "o"
        je      .switch
        cmp     bh, "u"
        je      .switch

        cmp     bh, "A"
        je      .switch
        cmp     bh, "E"
        je      .switch
        cmp     bh, "I"
        je      .switch
        cmp     bh, "O"
        je      .switch
        cmp     bh, "U"
        je      .switch

        jmp     .search_vowel

    .switch:
        mov     [eax + esi], bh
        jmp     .search_underscore

    .end:
        popa
        ret

join_string:
    ;Joins eax and ebx string together in ecx
    pusha

    xor     edx, edx
    xor     esi, esi
    xor     edi, edi

    .first:
        mov     dl, [eax + esi]
        mov     [ecx + edi], dl

        cmp     dl, 0
        je      .second_setup

        inc     esi
        inc     edi
        jmp     .first

    .second_setup:
        xor     esi, esi
    .second:
        mov     dl, [ebx + esi]
        mov     [ecx + edi], dl

        cmp     dl, 0
        je      .end

        inc     esi
        inc     edi
        jmp     .second

    .end:
        popa
        ret

get_letters:
    pusha
    
    xor     ebx, ebx
    xor     esi, esi
    xor     edi, edi

    .current_position:
        mov     bl, [eax + esi]

        cmp     bl, 0
        je      .end

        cmp     bl, "Z"
        jle     .big

        cmp     bl, "z"
        jle     .small

        jmp     .no

        .big:
            cmp     bl, "A"
            jge     .yes
            jmp     .no

        .small:
            cmp     bl, "a"
            jge     .yes
            jmp     .no

        .no:
            mov     edi, esi
            jmp     .search_replace_letter

        .yes:
            inc     esi
            jmp     .current_position

    .search_replace_letter:
        inc     edi

        mov     bl, [eax + edi]

        cmp     bl, 0
        je      .replace_end

        cmp     bl, "Z"
        jle     .big2

        cmp     bl, "z"
        jle     .small2

        jmp     .no2

        .big2:
            cmp     bl, "A"
            jge     .yes2
            jmp     .no2

        .small2:
            cmp     bl, "a"
            jge     .yes2
            jmp     .no2

        .no2:
            jmp     .search_replace_letter

        .yes2:
            mov     bl, [eax + edi]
            mov     [eax + esi], bl
            mov     [eax + edi], byte "1"
            jmp     .current_position

    .replace_end:
        mov     [eax + esi], byte 0
    .end:
        popa
        ret

main:
    ;Beolvasas
    mov     eax, str_text_a
    call    writeStr
    mov     eax, str_a
    call    readStr
    call    mio_writeln

    mov     eax, str_text_b
    call    writeStr
    mov     eax, str_b
    call    readStr
    call    mio_writeln

    ;Szabaly
    call    mio_writeln
    mov     eax, str_text_szabaly
    call    writeStr
    call    mio_writeln

    ;A B
    mov     eax, str_text_a
    call    writeStr
    mov     eax, str_a
    call    writeStr
    call    mio_writeln

    mov     eax, str_text_b
    call    writeStr
    mov     eax, str_b
    call    writeStr
    call    mio_writeln

    ;C
    mov     eax, str_a
    call    sort_ASCII
    call    get_letters

    mov     eax, str_b
    call    underscore_switch_vowel

    mov     eax, str_text_c
    call    writeStr

    mov     eax, str_a
    mov     ebx, str_b
    mov     ecx, str_c
    call    join_string

    mov     eax, str_c
    call    writeStr

    ret


section .data
    str_text_szabaly db "Szabaly ==> C = [A, Betuk Ascii novekvo sorrendben rendezve] + [B, _ karaktert ha van utanna levo legkozelebbi maganhangzora lecserelunk]", 0
    str_text_a db "A = ", 0
    str_text_b db "B = ", 0
    str_text_c db "C = ", 0


section .bss
    str_a   resb 256
    str_b   resb 256
    str_c   resb 256
