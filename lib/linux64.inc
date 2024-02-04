%macro printStr 1 ; printStr <pointer>
	mov rax, %1
	call _printRAX
%endmacro

%macro exit 0
	jmp _exit
%endmacro

%macro printInt 1
	mov rax, %1	
	call _printIntRAX
%endmacro

%macro takeInput 1 ; takeInput <pointer>
	mov rcx, %1
	call _takeInput
%endmacro

; PrintStr label start
_printRAX:
	push rax
	mov rbx, 0
_printLoop:
	inc rax
	inc rbx
	mov cl, [rax]
	cmp cl, 0
	jne _printLoop

	mov rax, SYS_WRITE
	mov rdi, STDOUT
	pop rsi
	mov rdx, rbx
	syscall

	ret
; PrintStr label end

; exit label start
_exit:
	mov rax, SYS_EXIT
	mov rdi, 0 ; Error code
	syscall

; exit label end

; PrintInt label start
_printIntRAX:
	mov rcx, digitSpace
	inc rcx
	mov [digitSpacePos], rcx

_printIntRAXLoop:
	mov rdx, 0
	mov rbx, 10
	div rbx
	push rax
	add rdx, 48

	mov rcx, [digitSpacePos]	
	mov [rcx], dl
	inc rcx
	mov [digitSpacePos], rcx

	pop rax
	cmp rax, 0
	jne _printIntRAXLoop

_printIntRAXLoop2:
	mov rcx, [digitSpacePos]

	mov rax, SYS_WRITE
	mov rdi, STDOUT
	mov rsi, rcx
	mov rdx, 1
	syscall

	mov rcx, [digitSpacePos]
	dec rcx
	mov [digitSpacePos], rcx

	cmp rcx, digitSpace
	jge _printIntRAXLoop2

	ret

; PrintInt label end

; takeInput label start
_takeInput:
	mov rax, SYS_READ
	mov rdi, STDIN
	mov rsi, rcx
	mov rdx, 16
	syscall
	mov byte [rsi + rax - 1], 0 ; removes last char (newline)
	ret
;takeInput label end

; Constants for syscall codes 
%include "lib/constant.inc"
