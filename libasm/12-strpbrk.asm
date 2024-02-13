BITS 64                 ; Set the mode to 64-bit

section .text           ; Start the text section
	global asm_strpbrk   ; Declare the function asm_strpbrk as global

asm_strpbrk:            ; Start of the asm_strcmp function
	xor rax, rax         ; Initialize RAX register to 0
	xor rbx, rbx         ; Initialize RAX register to 0
	xor rdx, rdx          ; Initialize RCX register to 0


.loop:                  ; Start of the loop

	mov dh, byte [rdi]   ; Load byte from the string into AL
	test dh, dh
	jnz .strchr
	ret


.strchr:
	xor rcx, rcx          ; Initialize RCX register to 0
	.strchr_loop:                   ; Start of the loop to iterate through the string
		mov dl, byte [rsi + rcx]
    	cmp dh, dl         ; Compare the character with the target character
    	je .strchr_found            ; If character matches, jump to .found

    	test dl, dl          ; Check for end of string (null terminator)
    	jz .strchr_not_found        ; If end of string, jump to .not_found

    	inc rcx              ; Move to the next character in the string
    	jmp .strchr_loop            ; Repeat loop

    .strchr_found:                  ; Label for character found
		mov rax, rdi                 ; Return from the function
		ret

    .strchr_not_found:              ; Label for character not found
    	inc rdi
    	jmp .loop

