BITS 64                    ; Set the mode to 64-bit

section .text              ; Start the text section
	global asm_strncmp     ; Declare the function asm_strncmp as global

asm_strncmp:               ; Start of the asm_strncmp function
	mov rax, 0             ; Initialize RAX register to 0
	mov rcx, 0             ; Initialize RCX register to 0
	cmp rdx, 0             ; Compare the third parameter (length) with 0
	ja .loop               ; Jump to loop if length is greater than 0
	ret                    ; Return if length is not greater than 0

.loop:                     ; Start of the loop
	mov al, byte [rdi + rcx]  ; Load byte from the first string into AL
	mov bl, byte [rsi + rcx]  ; Load byte from the second string into BL
	inc rcx                ; Increment RCX to move to the next character

	cmp al, 0              ; Check if end of the first string is reached
	je .end_0              ; If so, exit loop and return result

	cmp al, bl             ; Compare characters from both strings
	ja .end_1              ; If character in first string is greater than in second, exit with 1
	jb .end_2              ; If character in first string is less than in second, exit with -1
	cmp rcx, rdx           ; Compare the length of strings with the provided length
	jne .loop              ; Continue looping if lengths are not equal

	mov rax, 0             ; Both strings are equal up to the provided length, return 0
	ret                    ; Return from the function

.end_0:                    ; Label for ending loop if first string is ended
	cmp bl, 0              ; Check if end of the second string is reached
	jne .end_2             ; If not, exit with -1
	mov rax, 0             ; Both strings are equal, return 0
	ret                    ; Return from the function

.end_1:                    ; Label for ending loop if first string is greater than second
	mov rax, 1             ; First string is greater than second string, return 1
	ret                    ; Return from the function

.end_2:                    ; Label for ending loop if first string is less than second
	mov rax, -1            ; First string is less than second string, return -1
	ret                    ; Return from the function
