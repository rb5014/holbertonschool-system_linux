BITS 64                 ; Set the mode to 64-bit

section .text           ; Start the text section
	global asm_strncasecmp   ; Declare the function asm_strcmp as global

asm_strncasecmp:            ; Start of the asm_strcmp function
	xor rax, rax         ; Initialize RAX register to 0
	xor rbx, rbx         ; Initialize RBX register to 0
	xor rcx, rcx          ; Initialize RCX register to 0


.loop:                  ; Start of the loop
	cmp rcx, rdx
	je .end
	mov al, byte [rdi + rcx]  ; Load byte from the first string into AL
	mov bl, byte [rsi + rcx]  ; Load byte from the second string into BL
	inc rcx             ; Increment RCX to move to the next character

	cmp al, 0
	je .check_end_2



.check_end_2:
	cmp bl, 0
	je .end
	jmp .compare
.compare:
		or al, 0x20
    	or bl, 0x20

    	cmp al, bl
    	je .loop
.end:
	sub bl, al
	mov al, bl
	ret                 ; Return from the function
