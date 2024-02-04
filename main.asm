%include "lib/linux64.inc"

section .bss
	; must define digitSpace and digitSpacePos for printInt command
	digitSpace resb 100
	digitSpacePos resb 8
	name resb 100

section .data
	newline db 10,0
	space db " ",0
	hello db "Hello!",10,0
	askName db "What is your name?",10,0
	greet db "Hello ",0

section .text
global _start

_start:
	printStr hello
	printStr askName
	takeInput name
	printStr greet
	printStr name
	printStr newline
	exit
