%ifndef __IONUM_INC__
%define __IONUM_INC__

extern ReadInt          ; ():(EAX)          – 32 bites előjeles egész beolvasása
extern WriteInt         ; (EAX):()          – 32 bites előjeles egész kiírása
extern ReadInt64        ; ():(EDX:EAX)      – 64 bites előjeles egész beolvasása
extern WriteInt64       ; (EDX:EAX):()      – 64 bites előjeles egész kiírása
extern ReadBin          ; ():(EAX)          – 32 bites bináris pozitív egész beolvasása
extern WriteBin         ; (EAX):()          –                    - || -                   kiírása
extern ReadBin64        ; ():(EDX:EAX)      – 64 bites bináris pozitív egész beolvasása
extern WriteBin64       ; (EDX:EAX):()      –                    - || -                   kiírása
extern ReadHex          ; ():(EAX)          – 32 bites pozitív hexa beolvasása
extern WriteHex         ; (EAX):()          –                    - || -                   kiírása
extern ReadHex64        ; ():(EDX:EAX)      – 64 bites pozitív hexa beolvasása
extern WriteHex64       ; (EDX:EAX):()      –                    - || -                   kiírása

%endif