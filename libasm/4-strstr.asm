BITS 64                  ; Set the mode to 64-bit

section .text            ; Start the text section
	global asm_strstr    ; Declare the function asm_strstr as global

asm_strstr:              ; Start of the asm_strstr function
	; Inputs:
	;   rdi: pointer to the string
	;   rsi: string to search for
	; Outputs:
	;   rax: pointer to the first char of the first occurrence of the string, or NULL if not found
mov rax, 0
cmp byte [rsi], 0
je .found_string
cmp rdi, rsi
jb .not_found

.loop:                   ; Start of the loop to iterate through the string
	mov rcx, 0
	mov al, byte [rdi]   ; Load byte from the string into AL
	mov bl, byte [rsi]	 ; Load byte from the string to find into BL
	cmp al, bl          ; Compare the character with the target character
	je .loop_found_char            ; If character matches, jump to .found_char

	test al, al          ; Check for end of string (null terminator)
	jz .not_found        ; If end of string, jump to .not_found

	inc rdi              ; Move to the next character in the string
	jmp .loop            ; Repeat loop


.loop_found_char:                  ; Label for character found
	mov al, byte [rdi + rcx]
	mov bl, byte [rsi + rcx]
	test bl, bl
	jz .found_string
	inc rcx


	cmp al, bl
	je .loop_found_char

	inc rdi
	jmp .loop

.found_string:           ; Label for string found
	mov rax, rdi      ; Move the pointer to the first char of found string into RAX
	ret                   ; Return from the function

.not_found:              ; Label for string not found
	mov rax, 0            ; Set RAX to 0 (NULL)
	ret                   ; Return from the function
