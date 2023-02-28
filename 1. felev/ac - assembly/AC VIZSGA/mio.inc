%ifndef __MIO_INC__
%define __MIO_INC__

; Reads a character
; Out: AL - ASCII code
extern mio_readchar

; Writes a character
; In: AL - ASCII code
extern mio_writechar

; Writes a string (null-terminated)
; In: EAX - pointer
extern mio_writestr

; New line
extern mio_writeln

; Reads a 32-bit float
; Out: XMM0 - float
extern mio_readflt

; Writes a 32-bit float
; In: XMM0 - float
extern mio_writeflt

%endif