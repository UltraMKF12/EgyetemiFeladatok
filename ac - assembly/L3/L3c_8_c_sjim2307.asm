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


main:
    ;Feladat
    mov     eax, str_a
    call    readStr
    call    mio_writeln
    call    writeStr

    ret


section .data
    str_szabaly db "[Kiiras]Binaris = ", 0


section .bss
    str_a   resb 256
    str_b   resb 256
    str_c   resb 256
