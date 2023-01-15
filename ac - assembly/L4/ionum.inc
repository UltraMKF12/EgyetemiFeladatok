%ifndef __IONUM_INC__
%define __IONUM_INC__

extern ReadInt          ; ():(EAX)          – 32 bites előjeles egész beolvasása
extern WriteInt         ; (EAX):()          – 32 bites előjeles egész kiírása
extern ReadBin          ; ():(EAX)          – 32 bites bináris pozitív egész beolvasása
extern WriteBin         ; (EAX):()          –               - || -           kiírása
extern ReadHex          ; ():(EAX)          – 32 bites pozitív hexa beolvasása
extern WriteHex         ; (EAX):()          –               - || -           kiírása

%endif