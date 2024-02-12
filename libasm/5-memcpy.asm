
section .text            ; Start the text section
	global asm_memcpy    ; Declare the function asm_memcpy as global

asm_memcpy:              ; Start of the asm_memcpy function
	; Inputs:
	;   rdi: pointer to the dest string
	;   rsi: pointer to the src string
    ;   rdx: number of char to copy
mov rax, rdi
mov rcx, rdx
rep movsb
ret
