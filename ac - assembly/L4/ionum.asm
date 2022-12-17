; Széri József - sjim2307
; 514/2

; Labor: 4 - Modulok
; Feladat: ionum

; Compile:
; compile_module.bat ionum

%include 'iostr.inc'

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

    .end:
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

    .end:
        ret

        
WriteBin:

    .end:
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

    mov     ecx, 20
    mov     esi, str_a
    call    ReadLnStr

    call    WriteStr
    ret
    
section .data
    str_a_text db "A = ", 0

section .bss
    str_a   resb 256