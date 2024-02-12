BITS 64                 ; Set the mode to 64-bit

section .text           ; Start the text section
	global asm_strcasecmp   ; Declare the function asm_strcmp as global

asm_strcasecmp:            ; Start of the asm_strcmp function
	mov rax, 0          ; Initialize RAX register to 0
	mov rcx, 0          ; Initialize RCX register to 0

.loop:                  ; Start of the loop
	mov al, byte [rdi + rcx]  ; Load byte from the first string into AL
	mov bl, byte [rsi + rcx]  ; Load byte from the second string into BL
	inc rcx             ; Increment RCX to move to the next character

	cmp al, 0           ; Check if end of the first string is reached
	je .end_0           ; If so, exit loop and return result

	or al, 0x20			; Convert to lowercase
	or bl, 0x20			; Convert to lowercase

	cmp al, bl          ; Compare characters from both strings
	je .loop            ; If equal, continue loop
	ja .end_1           ; If character in first string is greater than in second, exit with 1
	jb .end_2           ; If character in first string is less than in second, exit with -1

.end_0:                 ; Label for ending loop if first string is ended
	cmp bl, 0           ; Check if end of the second string is reached
	jne .end_2          ; If not, exit with -1
	mov rax, 0          ; Both strings are equal, return 0
	ret                 ; Return from the function

.end_1:                 ; Label for ending loop if first string is greater than second
	sub al, bl
	ret                 ; Return from the function

.end_2:                 ; Label for ending loop if first string is less than second
	sub al, bl
	movsx rax, al
	ret                 ; Return from the function
