; this program reads an input from a user and prints it as it is 

org 100h   
	
call read_string
call print_string
ret	
	

read_string:
    ; initialize buffer with up to 100 characters  
    mov bx, buffer_start_addr
    mov [bx], 100
    
    ; read input from standard input and store it in the buffer
    mov dx, buffer_start_addr
    mov ah, 0ah
    int 21h
    
    ret

print_string: 
    ; set cl to length of the message, length of the message is stored in the second byte of the buffer
    mov bx,  buffer_start_addr
    inc bx
    mov cl, [bx]
                                          
    mov al, 0
    mov bh, 0
    mov bl, 0010_1111b ; set green background with white font
    
    mov dl, 0
    mov dh, 1
    mov bp, buffer_start_addr ; set the address from where to start printing 
    add bp, 2
    
    ; print the string
    mov ah, 13h
    int 10h
    
    ret 
    
buffer_start_addr dw 0xFF00



