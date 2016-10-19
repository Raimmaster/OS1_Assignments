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

   mov dx, 0
   mov ax, 5
   mov bx, 10
   div bx
   add ax, 48
   mov word[ent1], ax
   mov si, ent1
   call print_string

   call new_line

   mov si, second_prompt
   call print_string

   mov di, buffer_two
   call get_string

   call new_line

   ;»»»»»»»»
   ;addition
   mov cx, [buffer]
   mov dx, [buffer_two]
   add cx, dx
   sub cx, 48
   ;cambio
   mov ax, 128
   mov bx, answer_buffer
   call itos
   ;mov [answer_buffer], cx

   mov si, answer_buffer
   call print_string

   ;print newline
   call new_line     
   jmp mainloop 

 ;string literals  
 welcome db 'Sum of numbers!', 0x0D, 0x0A, 0
 prompt db 'Insert number 1: ', 0
 second_prompt db 'Insert number 2: ', 0
 buffer times 6 db 0
 buffer_two times 6 db 0
 answer_buffer times 6 db 0

; functions
new_line:
   mov ah, 0x0E
    mov al, 0x0D
    int 0x10
    mov al, 0x0A
    int 0x10      

    ret


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
 
   cmp al, 0x08 ;check for backspace char
   je .backspace
 
   cmp al, 0x0D ;check for enter char
   je .done_get 
 
   cmp cl, 0x05 ;check if 5 chars are in the input
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

 strlen:
   ;ax = direccion de la palabra
   mov cx, 0;iterador
   first_loop:
      mov bx, cx
      add bx, ax
      mov bl, byte[bx]
      cmp bl, 0
      je return
      inc cx
      jmp first_loop
   return:
      mov ax, cx
      ret

pow:
    ;ax = base
    ;bx = exponente
    mov cx, ax
    loop_pow:
        cmp bx, 1
        je salir_pow

        cmp bx, 0
        je pow_caso_uno
        
        mul cx
        dec bx
        jmp loop_pow
salir_pow:
    ret

pow_caso_uno:
    mov ax, 1
    ret

stoi:
   ;ax = direccion de la palabra
   push bp
   mov bp, sp
   sub sp, 6
   mov word[bp-2], ax; &buffer
   mov word[bp-4], 0; length
   mov word[bp-6], 0; return value

   call strlen
   mov word[bp-4], ax; length
   mov dx, 0; iterador
   stoi_loop:
      cmp word[bp-4], dx
      je salir_stoi
      mov ax, 10
      mov bx, word[bp-4]
      dec bx
      sub bx, dx
      call pow
      mov bx, word[bp-2]
      add bx, dx
      mov bl, byte[bx]
      sub bl, 48
      mul bl
      add word[bp-6], ax
      inc dx
      jmp stoi_loop

   salir_stoi:
      mov ax, word[bp-6]
      mov sp, bp
      pop bp
      ret

itos:
  ;ax = numero
  ;bx = &buffer
  push bp
  mov bp, sp
  sub sp,6
  mov word[bp-2], ax; numero
  mov word[bp-4], bx; &buffer
  mov word[bp-6], 0; contador
  itos_loop:
    mov ax, word[bp-2]; numero
    cmp ax, 0
    jle salir_itos
    mov bx, 10
    mov dx,0
    div bx;numero /10
    mov bx, word[bp-4]; &buffer
    mov cx, word[bp-6]
    add bx, cx
    add dx, 48
    mov word[bx], dx 
    inc word[bp-6];contador--
    mov word[bp-2], ax
    jmp itos_loop
  
  salir_itos:
    mov ax, answer_buffer
    call strlen
    mov bx, ax
    mov ax, answer_buffer
    call reverse
    mov sp, bp
    pop bp
    ret

swap:
  push bp
  mov bp, sp
  sub sp, 2
  mov word[bp-2], ax; temp = &str1
  mov ax, bx; str1 = str2
  mov bx, word[bp-2]; str2 = temp

  mov sp, bp
  pop bp
  ret

reverse:
  ;ax = str[]
  ;bx = length
  push bp
  mov bp, sp
  sub sp, 6
  mov word[bp-2], 0; start = 0
  mov word[bp-4], bx; end = length
  dec word[bp-4]
  mov word[bp-6], ax; &str

  while_start:
    mov bx, word[bp-2]
    cmp bx, word[bp-4]
    jl end_reverse
    mov ax, word[bp-6]
    add ax, word[bp-2]; str + start
    add bx, word[bp-4]; str + end
    call swap
    inc word[bp-2]
    dec word[bp-4]
    jmp while_start

  end_reverse:
    mov sp, bp
    pop bp
    ret

 ent1 times 4 db 0  