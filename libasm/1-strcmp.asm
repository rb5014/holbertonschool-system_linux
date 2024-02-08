BITS 64

section .text
	global asm_strcmp
asm_strcmp:
	mov rax, 0
	mov rcx, 0
	.loop:
		mov al, byte [rdi + rcx]
		mov bl, byte [rsi + rcx]
		inc rcx
		cmp al, 0
		je .end_0
		cmp al, bl
		je .loop
		ja .end_1
		jb .end_2
	.end_0:
		cmp bl, 0
		jne .end_2
		mov rax, 0
		ret
	.end_1:
		mov rax, 1
		ret
	.end_2:
		mov rax, -1
		ret
