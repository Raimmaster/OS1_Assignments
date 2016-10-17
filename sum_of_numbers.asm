 org 0x7C00   
 bits 16      
 ;setting up
   mov ax, 0  
   mov ds, ax
   mov es, ax
   mov ss, ax 
   mov sp, 0x7C00
 
   mov si, welcome
   call print_string

mainloop:
   mov si, prompt
   call print_string
 
   mov di, buffer
   call get_string
 	
   mov si, second_prompt
   call print_string

   mov di, buffer_two
   call get_string

   ;»»»»»»»»
   ;addition
   mov bx, answer_buffer
   mov cx, [buffer]
   mov dx, [buffer_two]
   add cx, dx
   sub cx, 48
   mov [answer_buffer], cx

   mov si, answer_buffer
   call print_string

   ;print newline
   mov al, 0x0A
   int 0x10		

   ;mov si, buffer
   ;cmp byte [si], 0  
   ;je mainloop       
 
   ; mov si, buffer
   ; mov di, cmd_hi  
   ; call strcmp
   ; jc .helloworld
 
   ; mov si, buffer
   ; mov di, cmd_help
   ; call strcmp
   ; jc .help
 
   ; mov si, badcommand
   ; call print_string 
   jmp mainloop 


 ;string literals  
 welcome db 'Sum of numbers!', 0x0D, 0x0A, 0
 prompt db 'Insert number 1: ', 0
 second_prompt db 'Insert number 2: ', 0
 buffer times 32 db 0
 buffer_two times 32 db 0
 answer_buffer times 32 db 0


; functions
print_string:
   lodsb        
 
   or al, al  
   jz .done   
 
   mov ah, 0x0E
   int 0x10   
 
   jmp print_string
 
 .done:
   ret
 
 get_string:
   xor cl, cl
 
 .loop:
   mov ah, 0
   int 0x16   
 
   cmp al, 0x08
   je .backspace
 
   cmp al, 0x0D 
   je .done_get 
 
   cmp cl, 0x3F 
   je .loop     
 
   mov ah, 0x0E
   int 0x10     
 
   stosb  
   inc cl
   jmp .loop
 
 .backspace:
   cmp cl, 0	
   je .loop	
 
   dec di
   mov byte [di], 0	
   dec cl		
 
   mov ah, 0x0E
   mov al, 0x08
   int 10h		
 
   mov al, ' '
   int 10h		
 
   mov al, 0x08
   int 10h		
 
   jmp .loop	
 
 .done_get:
   mov al, 0	
   stosb
 
   mov ah, 0x0E
   mov al, 0x0D
   int 0x10
   mov al, 0x0A
   int 0x10		

   ret