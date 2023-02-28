%include 'ionum.inc'
%include 'iostr.inc'
%include 'strings.inc'

;nasm -f win32 vizsga3.asm
;nlink ionum.obj iostr.obj strings.obj vizsga3.obj -lmio -o vizsga3.exe

global main
section .text

leggyakoribb_betu:
    push    ebx
    push    ecx
    push    edx
    push    esi
    push    edi

    mov     edi, 'a'
    xor     ebx, ebx

    xor     eax, eax

    mov     ecx, 'a'
    mov     edx, 'A'
    .inner_loop:
        cmp     ecx, 'z'
        je      .end
        cmp     edx, "Z"
        je      .end

        xor     edx, edx
        push    esi
        .string_count:
            xor     eax, eax
            lodsb
            cmp     eax, ecx
            jne     .no_add
            cmp     eax, edx
            jne     .no_add
            cmp     eax, 0
            je      .ending
            inc     edx

            .no_add:
            jmp     .string_count

            .ending:
        
        pop     esi
        cmp     ebx, edx
        jg      .nagyobb
        jmp     .kisebb

        .kisebb:
            mov     ebx, edx
            mov     edi, ecx
        .nagyobb:


        inc     ecx
        inc     edx
        jmp     .inner_loop


    .end:
        mov     eax, edi
        pop     edi
        pop     esi
        pop     edx
        pop     ecx
        pop     ebx
        ret

main:
    xor     edx, edx
    xor     ebx, ebx
    
    .beolvasas:
        mov     esi, str_text
        call    WriteStr
        mov     esi, tomb
        add     esi, edx
        mov     ecx, 201
        call    ReadLnStr

        .feldolgozas:
            call    leggyakoribb_betu
            call    WriteInt  

        add     edx, 201
        inc     ebx
        call    StrLen
        cmp     eax, 0
        jne     .beolvasas



    ret

section .data
    str_text db "Szoveg = ", 0

section .bss
    tomb resb 20100