%ifndef __STRINGS_INC__
%define __STRINGS_INC__

extern StrLen                   ; Returns string length in ESI to EAX
extern StrCat                   ; EDI + ESI string
extern StrUpper
extern StrLower
extern StrCompact               ; Copies ESI to EDI, except 9, 13, 10, and space character

%endif