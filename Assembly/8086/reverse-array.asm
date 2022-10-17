; this program copies reverses and copies an array to a specified memory location

org 100h

; store the address of the last array element in si register, and set direction flag
 
mov al, 0 
add al, length
dec al ; offset to get the last element
lea bx, array                          
add ax, bx ; address of the last element
mov si, ax
std

mov cx, 0
jmp copy_array_element

ret

copy_array_element:
    lodsb 
    
    ; write loaded byte to the next memory location
    mov bx, new_array_start_addr
    add bx, cx
    mov [bx], al
    inc cx
    
    ; exit when all elements copied
    mov bx, si 
    lea dx, array
    sub bx, dx
    jae copy_array_element
    ret            

length db 3    
array db 5,1,2
new_array_start_addr dw 0xFF00  





