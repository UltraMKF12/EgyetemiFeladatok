nasm -f win32 %1.asm
nlink %1.obj -lmio -o %1.exe
%1.exe