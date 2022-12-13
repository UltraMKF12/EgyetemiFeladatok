nasm -f win32 %1.asm
nlink L4\iostr.obj %1.obj -lmio -o %1.exe
%1.exe