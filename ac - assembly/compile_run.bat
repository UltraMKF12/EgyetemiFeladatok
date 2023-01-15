nasm -f win32 %1.asm
nlink %1.obj -lmio -lio -o %1.exe
%1.exe