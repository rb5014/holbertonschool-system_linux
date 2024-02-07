BITS 64

section .text
    global asm_strlen          ; Declare the function as global

asm_strlen:
    xor     rax, rax          ; Clear rax to use it as a counter
.loop:
    cmp     byte [rdi + rax], 0   ; Compare the byte at the address in rdi + rax with null terminator
    je      .done             ; If it's zero, we're done
    inc     rax               ; Otherwise, move to the next character
    jmp     .loop             ; Repeat the loop
.done:
    ret                       ; Return the length stored in rax
