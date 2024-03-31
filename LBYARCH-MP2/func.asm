
section .data
stencilSumSet dq 0.0

section .text
bits 64
default rel

global stencilComputation

stencilComputation:
	lea rsi, [rcx] ;pointer to X
	lea rdi, [rdx] ;pointer to Y
	mov r10, r8 ;size of array
	sub r10, 6 ;# loop of stencil
	mov r11, 0 ;counter of stencil loop
	movsd xmm0, [stencilSumSet] ;counter of stencil window sum

initialize:
	mov rcx, 7
loopX:
	movsd xmm1, [rsi]
	addsd xmm0, xmm1
	add rsi, 8
	loop loopX
	
	;write to Y
	movsd [rdi], xmm0
	;inc pointer to Y
	add rdi, 8

	inc r11
	cmp r10, r11
	jz tapos

	mov rcx, 6

resetLoopX:
	sub rsi, 8
	loop resetLoopX
	movsd xmm0, [stencilSumSet] ;counter
	jmp initialize
	
tapos:

ret 