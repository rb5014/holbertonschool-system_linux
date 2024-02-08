BITS 64

section .text
	global asm_strncmp
asm_strncmp:
	mov rax, 0
	mov rcx, 0
	cmp rdx, 0
	ja .loop
	ret

.loop:
	mov al, byte [rdi + rcx]
	mov bl, byte [rsi + rcx]
	inc rcx
	cmp al, 0
	je .end_0
	cmp al, bl
	ja .end_1
	jb .end_2
    cmp rcx, rdx
    jne  .loop
    mov rax, 0
    ret

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
