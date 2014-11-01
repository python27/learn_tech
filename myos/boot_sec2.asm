;
; A simple boot sector that demonstrates addressing
;

mov ah, 0x0e			;int 10/ah = 0eh->scrolling teletype BIOS routine

mov al, the_secret
int 0x10

mov al, [the_secret]
int 0x10

mov bx, the_secret
add bx, 0x7C00
mov al, [bx]
int 0x10

mov al, [0x7C1D]
int 0x10

jmp $					;jmpt to current address (i.e. forever)

the_secret:
	db 'X'

;
; Padding and magic BIOS number
;
times 510-($-$$) db 0	; pad the boot section out with zeros

dw 0xaa55				; Last two bytes form the magic number
						; so BIOS knows we are a boot sector
