nasm -f win32 %1.asm
nlink iostr.obj strings.obj %1.obj -lmio -o %1.exe