;
; A simple boot sector that prints a string using our function
;

[org 0x7C00]

mov bx, HELLO_MSG
call print_string

mov bx, GOODBYE_MSG
call print_string

jmp $

%include "print_string.asm"


HELLO_MSG:
	db 'Hello, World!', 0	; the zero on the end tells our routine
							; when to stop printing characters

GOODBYE_MSG:
	db 'Goodbye !', 0


times 510-($-$$) db 0		; pad the boot section out with zeros

dw 0xaa55					; Last two bytes form the magic number
							; so BIOS knows we are a boot sector
