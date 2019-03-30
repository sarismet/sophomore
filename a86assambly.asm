code segment
take: ;take is a labet to take input from the user and convey it into relevant part
mov ax,0100h ; to take input from users
int 21h
sub ax,100h ; we need to subtract 100h because it is not the real input the user entered
cmp ax,2Ah ; to check if it is multiplication sign
je carp ; if it is so go to multiplication part 
cmp ax,2Bh ; to check if it is addition sign
je topla ;if it is so go to addition part 
cmp ax,2Fh; to check if it is division sign
je bol ;if it is so go to division part 
cmp ax,20h ;to check if it is space 
je pushspace;if it is so go to pushspace to push space  
cmp ax,0Dh ;to check if the user press enter button
je beforeendfirst ; if the user pressed go to beforeendfirst
cmp ax,94d  ; to check if it is xor sign
je iksor
cmp ax,38d ; to check if it is and sign
je ve
cmp ax,124d ; to check if it is or sign
je yada
jmp bringtheaction

iksor: ; this label is for xor comamnd 
pop ax ; this is probably a space 
pop ax ; this is real one 
pop dx ; this is probably a space 
pop dx ; this is real one
xor ax,dx ; applt xor dx to ax
push ax ; and then push it into stack again
jmp take

carp: ;this label is just for multiplying command. To overcome overflow we just use bx instead of dx
pop ax ;this is probably a space 
pop ax ; this is real one 
pop bx ;this is probably a space 
pop bx ; this is real one 
mov dx,0h
mul bx ;then multiply it

push ax ; after all push it the new value
jmp take ; go to take label to take a new value

ve: ; this label is for and command
pop ax ; this is probably space  
pop ax ; ths is a real value
pop dx ; this is probably space
pop dx ; this is a real value
and ax,dx ; apply the and command from dx to ax
push ax ; push it in to stack
jmp take ;go to take label to take a new value


topla:;this label is for adding command
pop ax ; this is probably space  
pop ax  ; ths is a real value
pop dx ; this is probably space  
pop dx  ; this is a real value
add ax,dx ; add dx and ax
push ax ; push it the new value 
jmp take; go to take label to take a new value

pushspace: ;this label is for pushing space because there is blank between input tokens
push ax ; push the space which is 20h
mov cx,0h ; we have to make cx 0h because there is a blank and we take the value with no blank between tokens according to cx value
jmp take ; go to take label to take a new value


yada:;this label is for or command
pop ax; this is probably space
pop ax ; ths is a real value
pop dx; this is probably space
pop dx ; ths is a real value
or ax,dx ; apply or command drom dx to ax
push ax ; push it the new value 
jmp take; go to take label to take a new value


bol:;this label is for division command
pop bx; this is probably space
pop bx; ths is a real value
pop ax; this is probably space
pop ax; ths is a real value
mov dx,0h
div bx ; apply division part

push ax ; now ax is created push it into stack
jmp take; go to take label to take a new value
alimp:
mov dx,0h
push dx
push dx
mov ah,0h ; clean the ah
jmp endingfirst ; let's go to endingfirst part to execute al 

beforeendfirst:;this label is for ending part but the ending is divided in to 2 part this is first part
mov dl,10d ; we need a new line first
mov ax,200h ; we show the new line
int 21h 
pop ax ; take the value left the after all process 
mov dx,33d ; make the dx 0021h which is a symbol to understand we reach out the end of the stack. The symbol is decided by us	
push dx ; push the dx value into end of the stack
mov dx,0h ; clean the dx
mov ch,ah ; store ah value in ch to prevent overflow
cmp al,0h
je alimp
mov ah,0h ; clean the ah
jmp endingfirst ; let's go to endingfirst part to execute al 


cokcikar: ; we have two different char first clasic number 1 2 3 and letters this part is for letters
sub al,55d ; we substract 55 in decimal format to make it the letter that A86 understands
mov bx,ax ;we need to store the ax value because we store another value in it
pop ax ; we have a value in stack and pop it into ax
mov dx,10h ; give the 10h value to dx 
mul dx ; multiplying
add ax,bx ; we now have the new ax which is mathematically correct
push ax ; push the new value
jmp take ; go to take label to take a new value


bringtheaction:; this label is to take numbers and if there is no bland before it then go to cokcikar part and make it mathematically corrent
inc ch ; we need to increase ch 
cmp ch,01h ; if the ch is 1 it means that it is the beginning of the input so it should be directly taken into stack 
je justpush ; so go to justpush
cmp ax,65d ; if it is not the beginning of the input then we need to compare it with 65d to see if it is letter or not
jae cokcikar ; if it is let go to cokcikar and substract 55d 
sub al,30h ; if it is a number ve need to suctract 48d or 30h
mov bx,ax ; we will need this ax later on 
pop ax ; it is the value once stored in stack
mov dx,10h 
mul dx
add ax,bx ; add bx and ax to build the new ax ex 12 = 1.10 + 2 
push ax ; push the new ax
jmp take ; go to take label to take a new value


upadd: ; this label is to suctract 55d to make the A86 understand a letter
sub al,55d
push ax
jmp take ; go to take label to take a new value


justpush: ; this label is to push something 
cmp ax,65d ; if it is a letter then go to upadd
jae upadd
sub al,30h ; if it is not then it is a number so substract 30h
push ax
jmp take


thisends: ; this label is to finish whole program
int 20h

ondanlow: ; this label is for things that is lower than 10d if it is so it is enough to add 30h to show its value on concole
mov dx,cx 
add dx,30h
mov ax,200h
int 21h
jmp bitir

tensixlow: ; this label is for things that is lower than 16d and bigger than 10d if it is so it is enough to add 37h to show its value on concole
mov dx,cx
add dx,37h
mov ax,200h
int 21h
jmp bitir

secondend: ; this label is the second part of finishing the programram
cmp ax,0h ; if we have ax 0000h than we reach out the end so we finish the program
je bitir 
mov dl,10h ; if it not the end of the program the divide it 10h the take the last digit
div dl
mov bx,0h ;clean the bx
mov bl,ah ; store the remainder value
push bx ;push the remainder and we could have some work on Quotient of ax 
mov ah,0h
jmp secondend ; so go to secondend label until the ax is 0000h 

ikinciasama:; this label is for the second part of the finilizing the program
mov al,ch ; we have the ah value stored in ch and we have no work on al so take it into al and go to secondend
jmp secondend


endingfirst: ;  this label is for the first part of the finilizing the program
cmp ax,0h ;if we have ax 0000h than we reach out the end so we must go to second part
je ikinciasama 
mov dl,10h ; if it is not the end of al then divide it by 10h to take digit
div dl
mov bx,0h ; clean the bx to make sure it is clean
mov bl,ah ; take the Quotient part into bl and 
push bx ; push it into stack
mov ah,0h ; we dont need the Quotient part
jmp endingfirst ; go again to endingfirst part until the ax is 0000h


bitir: ; this label is for to exacute the the over all value
pop cx ; take a valur from stack and look at its value 
cmp cx,33d ;if it is 33d ehich is ! then it is the end of stack so finish the program because we have no work on it this ! sign is decided by us
je thisends 
cmp cx,9d ; if it is not the end of the stack check if it is number or not
jbe ondanlow
cmp cx,15d
jbe tensixlow ;if it is not a number check if it is letter or not

code ends
