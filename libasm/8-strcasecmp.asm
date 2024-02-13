BITS 64                 ; Set the mode to 64-bit

section .text           ; Start the text section
	global asm_strcasecmp   ; Declare the function asm_strcmp as global

asm_strcasecmp:            ; Start of the asm_strcmp function
	xor rax, rax         ; Initialize RAX register to 0
	xor rbx, rbx         ; Initialize RBX register to 0
	xor rcx, rcx          ; Initialize RCX register to 0


.loop:                  ; Start of the loop
	mov al, byte [rdi + rcx]  ; Load byte from the first string into AL
	mov bl, byte [rsi + rcx]  ; Load byte from the second string into BL
	inc rcx             ; Increment RCX to move to the next character

	cmp al, 0           ; Check if end of the first string is reached
	je .end_0           ; If so, exit loop and return result

	jmp .check_first_char


.check_first_char:
	;This permits to convert only if it is an uppercase letter
	cmp al, 'A'
	jb .check_second_char
	cmp al, 'Z'
	ja .check_second_char
	or al, 0x20
	jmp .check_second_char

.check_second_char:
	;This permits to convert only if it is an uppercase letter
	cmp bl, 'A'
	jb .compare_chars
	cmp bl, 'Z'
	ja .compare_chars
	or bl, 0x20
	jmp .compare_chars

.compare_chars:
	cmp al, bl
	je .loop
	jmp .end

.end_0:
	mov rax, 0
	ret

.end:
	sub al, bl
	movsx rax, al
	ret                 ; Return from the function