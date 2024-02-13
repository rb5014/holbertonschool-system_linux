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
	jne .compare           	;
	ret

.compare:
	or al, 0x20
	or bl, 0x20
	cmp al, bl
	je .loop

	sub bl, al
	mov al, bl
	ret                 ; Return from the function