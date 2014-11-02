print_string:
	pusha

loop_point:
	mov al, [bx]
	cmp al, 0
		je return_point
	mov ah, 0x0e
	int 0x10
	add bx, 1
	jmp loop_point
	
return_point:
	popa
	ret
