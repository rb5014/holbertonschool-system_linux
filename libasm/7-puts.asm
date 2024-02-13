
section .text            ; Start the text section
	global asm_puts    ; Declare the function asm_puts as global
	extern asm_strlen  ; Declare extern function

asm_puts:              ; Start of the asm_memcpy function
	; Inputs:
	;   rdi: chars to print
    ; Set up the registers for sys_write

call asm_strlen 		; Length of the message
mov rdx, rax	; Get strlen result
mov rax, 1  	; Sys_write system call number
mov rsi, rdi  ; Get string in rdi
mov rdi, 1   	; File descriptor for stdout


syscall 		; Trigger the system call
ret 			; Return from the function

