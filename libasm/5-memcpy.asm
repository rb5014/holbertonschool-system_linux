BITS 64                  ; Set the mode to 64-bit

section .text            ; Start the text section
	global asm_memcpy    ; Declare the function asm_memcpy as global

asm_memcpy:              ; Start of the asm_memcpy function
	; Inputs:
	;   rdi: pointer to the dest string
	;   rsi: pointer to the src string
    ;   rdx: number of char to copy


mov rcx, 0

.loop:                   ; Start of the loop to iterate through the string
    cmp rcx, rdx         ; End function when all chars have been copied
    je .end

    mov dl, [rsi + rcx]  ; Load char in rsi at position rcx
    mov [rdi + rcx], dl  ; Copy in rdi at position rcx the value in dl
	inc rcx              ; increment rcx counter
	jmp .loop            ; Repeat loop

.end:
    ret