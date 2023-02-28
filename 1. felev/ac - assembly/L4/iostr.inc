%ifndef __IOSTR_INC__
%define __IOSTR_INC__

extern ReadStr                  ; To ESI, ECX = max character
extern WriteStr                 ; From ESI
extern ReadLnStr                ; ReadStr + NewLine
extern WriteLnStr               ; WriteStr + NewLine
extern NewLine

%endif