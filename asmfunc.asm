section .text
bits 64
default rel

global distance_asm

distance_asm:

    mov rax, [rsp + 40]     
    mov r10d, [rsp + 48]    

    xor r11, r11            

    LoopStart:
        cmp r11, r10           
        jge LoopEnd             

        movsd xmm0, [r9 + r11*8]    
        subsd xmm0, [rdx + r11*8]   
        mulsd xmm0, xmm0            

        movsd xmm1, [rax + r11*8]   
        subsd xmm1, [r8 + r11*8]    
        mulsd xmm1, xmm1            

        addsd xmm0, xmm1           
        sqrtsd xmm0, xmm0          

        movsd [rcx + r11*8], xmm0   

        inc r11                     
        jmp LoopStart

    LoopEnd:
    ret