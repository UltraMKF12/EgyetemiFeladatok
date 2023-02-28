; Nev: Vezetek_Nev Kereszt_Nev
; Azonosito: xyim1234
; Csoportszam: xyz

; Labor: L3A_9

; Feladat: (vagy roviditett valtozata) - sorszamozott feladatok eseten mindenkepp tartalmazza a sorszamnak megfelelo feladatot

%include 'mio.inc'

global main
section .text

;---------------------------------
;32 bites decimalis egeszeket beolvaso fuggveny
;eax-ben teriti vissza a beolvasott szamot
;CF: 1 hogyha hibas a bemenet, 0 hogyha nem
ReadInt:
	push	ebx				
	push	ecx
	
	xor 	eax, eax
	xor		ebx, ebx		;ebx - ben epiti fel a szamat
	mov		ecx, 10			;ecx = 10
	
.nextchar:					;ciklus, amely egyenkent beolvassa a karaketereket es felipiti a szamot
	call	mio_readchar	
	call	mio_writechar
	
	;beolvasott karakter ellenorzese
	cmp		eax, 13			;enter eseten leall a ciklus
	je		.end
	
	; ide meg kell a hibakezeles 
	; hiba eseten a carry flaget beallitjuk	
	
	;szam felepitese
	imul	ebx, ecx		
	add		ebx, eax		;ebx = ebx*10 + eax
	jmp		.nextchar		;vissza a ciklus elejere	
	
.end:						
	mov 	eax, ebx		;eax = beolvasott szam
	
	pop		ecx				;ebx, ecx eredeti allapotanak visszaallitasa
	pop		ebx
	clc						;CF = 0  - nincs hiba
	ret

	
;--------------------------------
;32 bites decimalis egeszeket kiiro fuggveny
;eax: ebben a regiszterben kapja a kiirando szamot
WriteInt:
	push	ebx
	push	ecx
	push	edx
	
	mov		ebx, 10			;ebx = 10 - ezzel osztjuk a szamot
	xor		ecx, ecx		;ecx = 0  - szamjegy szamlalo
	
.next_digit:				;ciklus amelyben a szamot szamjegyeire bontjuk
	cdq						;szam osztasa 10-zel
	idiv 	ebx
	push	edx				;utolso szamjegy a verembe kerul
	
	test	eax,eax
	jnz		.next_digit		;ciklus ismetlese, amig nem 0 a szam
	
.next_char:					;ciklus ami a szamjegyeket kiirja a kepernyore
	;tovabbi kod	
	jmp		.nextchar
		
	pop		edx
	pop		ecx
	pop		ebx
	ret

	
;---------------------------------
main:
    ;Elso szam beolvasasa
	mov		eax, messageA
	call	mio_writestr
	call	ReadInt
	jc		.hiba
	mov		ebx, eax		;ebx = A
	
	;masodik szam beolvasasa
	mov		eax, messageB
	call	mio_writestr
	call	ReadInt			;eax = B
	jc		.hiba
	
	;szamok osszeadasa
    add		eax, ebx		;eax = A+B
	
	;osszeg kiirasa a kepernyore
	mov		eax, messageC
	call	mio_writestr
	call	WriteInt		

	ret
	
.error:						;hibauzenet kiirasa
	;tovabbi kod
	ret
	
	
section .data
    messageA db "A = ", 0
	messageB db "B = ", 0
	messageC db "C = ", 0















