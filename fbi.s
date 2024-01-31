section .text
    global fib

fib:
    ; Input: RDI = n
    ; Output: RAX = fib(n)

    ; Base cases
    cmp rdi, 0
    je .base_case_0
    cmp rdi, 1
    je .base_case_1

    ; Recursive case
    ; Calculate fib(n-1)
    dec rdi
    call fib
    mov rsi, rax

    ; Calculate fib(n-2)
    dec rdi
    call fib

    ; Add fib(n-1) and fib(n-2)
    add rax, rsi

    ret

.base_case_0:
    ; fib(0) = 0
    mov rax, 0
    ret

.base_case_1:
    ; fib(1) = 1
    mov rax, 1
    ret
