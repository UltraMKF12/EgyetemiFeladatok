; Compile:
; nasm -f win32 miodemo.asm
; nlink miodemo.obj -lmio -o miodemo.exe

%include 'mio.inc'

global main

section .text
main:
    ; Write a character
    mov     al, '!'
    call    mio_writechar
    
    ; New line
    mov     al, 13              ; carriage return
    call    mio_writechar
    mov     al, 10              ; line feed
    call    mio_writechar
    
    ; Write a string
    mov     eax, message
    call    mio_writestr
    call    mio_writeln         ; new line - the easy way
    
    ; Read some text
.nextchar:
    ; read a character from the keyboard
    call    mio_readchar
    ; end if ENTER was pressed
    cmp     al, 13
    je      .end
    ; display the character on the screen!
    call    mio_writechar
    ; erase the previous character if BACKSPACE was pressed
    cmp     al, 8
    jne     .nextchar
    mov     al, ' '
    call    mio_writechar
    mov     al, 8
    call    mio_writechar
    ; next iteration
    jmp     .nextchar
    
.end:
    ret
    
section .data
    message db "Type something:", 0
