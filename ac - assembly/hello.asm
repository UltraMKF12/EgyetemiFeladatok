; Compile:
; nasm -f win32 hello.asm
; nlink hello.obj -lio -o hello.exe

%include 'io.inc'

global main 

section .text
main:
    mov     eax, 42
    call    io_writeint
    call    io_writeln
    ret
