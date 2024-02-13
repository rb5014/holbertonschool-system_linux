
section .text            ; Start the text section
	global asm_putc    ; Declare the function asm_putc as global

asm_putc:              ; Start of the asm_memcpy function
	; Inputs:
	;   rdi: char to print
    ; Set up the registers for sys_write
mov rax, 1  	; Sys_write system call number
mov [rsi], dil  ; Get char in rdi (dil is lowest byte)
mov rdi, 1   	; File descriptor for stdout
mov rdx, 1 		; Length of the message
syscall 		; Trigger the system call
ret 			; Return from the function

