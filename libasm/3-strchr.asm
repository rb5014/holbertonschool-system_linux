BITS 64                  ; Set the mode to 64-bit

section .text            ; Start the text section
	global asm_strchr    ; Declare the function asm_strchr as global

asm_strchr:              ; Start of the asm_strchr function
	; Inputs:
	;   rdi: pointer to the string
	;   sil: character to search for (lower 8 bits of rdi)
	; Outputs:
	;   rax: pointer to the first occurrence of the character, or NULL if not found

.loop:                   ; Start of the loop to iterate through the string
	mov al, byte [rdi]   ; Load byte from the string into AL
	cmp al, sil          ; Compare the character with the target character
	je .found            ; If character matches, jump to .found

	test al, al          ; Check for end of string (null terminator)
	jz .not_found        ; If end of string, jump to .not_found

	inc rdi              ; Move to the next character in the string
	jmp .loop            ; Repeat loop

.found:                  ; Label for character found
	mov rax, rdi         ; Move the pointer to the found character into RAX
	ret                   ; Return from the function

.not_found:              ; Label for character not found
	mov rax, 0            ; Set RAX to 0 (NULL)
	ret                   ; Return from the function
