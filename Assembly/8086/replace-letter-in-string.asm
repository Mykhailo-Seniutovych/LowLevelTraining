; this program replaces a letter with another letter in a string

org 100h

call main
ret

data:                                                
    read_message_prompt db 'Type message:', 0
    read_original_letter_prompt db 'Type letter that should be replaced:', 0
    read_new_letter_prompt db 'Type new letter:', 0 
    
    original_letter: db ? ; placeholder for the original letter
    new_letter: db ? ; placeholder for the new letter
    message_buffer db 100, ?, 100 dup(0) ; set message buffer for 100 characters, that will be populated with user input
    
main:
    call print_message_prompt
    call read_message
    
    call print_original_letter_prompt
    call read_original_letter  
    
    call print_new_letter_prompt
    call read_new_letter
                               
    call replace_message

    call print_message
    ret

print_message_prompt:
    ; set bp to point to the beginning of the message to be printed (first two bytes contain message max length and actual length)
    mov si, offset read_message_prompt
    call print_chars
    ret  

print_original_letter_prompt:
    ; set cursor position on next line
	mov dh, 2
	mov dl, 0
	mov bh, 0
	mov ah, 2
	int 10h 
	
    ; set bp to point to the beginning of the message to be printed (first two bytes contain message max length and actual length)
    mov si, offset read_original_letter_prompt
    call print_chars
    ret  

print_new_letter_prompt:
    ; set cursor position on next line
	mov dh, 4
	mov dl, 0
	mov bh, 0
	mov ah, 2
	int 10h 
	
    ; set bp to point to the beginning of the message to be printed (first two bytes contain message max length and actual length)
    mov si, offset read_new_letter_prompt
    call print_chars
    ret

print_chars:
    lodsb
    cmp al, 0  
    je ret_print_chars    
    mov ah, 0eh
    int 10h
    jmp print_chars
    ret_print_chars: ret 

read_original_letter:
    ; set cursor position on next line
	mov dh, 3
	mov dl, 0
	mov bh, 0
	mov ah, 2
	int 10h
	   
    ; read single letter
    mov ah, 1
	int 21h 
	
	; write read letter into new_letter
	mov bx, offset original_letter
	mov [bx], al
	
	ret
	
read_new_letter:
    ; set cursor position on next line
	mov dh, 5
	mov dl, 0
	mov bh, 0
	mov ah, 2
	int 10h
	   
    ; read single letter
    mov ah, 1
	int 21h 
	
	; write read letter into new_letter
	mov bx, offset new_letter
	mov [bx], al
	
	ret
    
read_message: 
    ; set cursor position on next line
	mov dh, 1
	mov dl, 0
	mov bh, 0
	mov ah, 2
	int 10h
	
	; read message
    mov dx, offset message_buffer
    mov ah, 0ah
    int 21h
     
replace_message:
    mov ax, offset message_buffer
    add ax, 2 ; the actual message start after first two bytes
    mov si, ax
     
    replace_char: 
        lodsb
        cmp al, 0
        je ret_replace_message ; return if end of string
        
        mov bx, original_letter
        cmp al, [bx]
        jne replace_char ; return if this letter is not matched
        
        mov bx, new_letter
        mov al, [bx]
        mov [si - 1], al 
        jmp replace_char
        
    ret_replace_message: ret

; print message using INT 10h / AH = 13h interrupt https://jbwyatt.com/253/emu/8086_bios_and_dos_interrupts.html#int10h_13h    
print_message:
    ; set bp to point to the beginning of the message to be printed (first two bytes contain message max length and actual length)
    mov ax, offset message_buffer
    add ax, 2 
    mov bp, ax 
    
    mov bx, offset message_buffer
    add bx, 1 ; second byte contains number of characters read
    mov ch, 0
    mov cl, byte [bx]  
    
    mov al, 0
    mov bh, 0
    mov bl, 0010_1111b
    
    ; print message in third row and first column
    mov dh, 6
    mov dl, 0
    
    mov ah, 13h
    int 10h 
    
    ret
 

