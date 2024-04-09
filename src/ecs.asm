	.file	"ecs.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	init_ecs
	.type	init_ecs, @function
init_ecs:
.LFB24:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	edx, 131072
	lea	rdi, entities[rip]
	xor	esi, esi
	call	memset@PLT
	lea	rdx, components[rip]
	mov	ecx, 128
	xor	eax, eax
	mov	rdi, rdx
	rep stosq
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	init_ecs, .-init_ecs
	.p2align 4
	.globl	add_entity
	.type	add_entity, @function
add_entity:
.LFB25:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	xor	r15d, r15d
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 8
	.cfi_def_cfa_offset 64
	mov	r13d, DWORD PTR entity_count[rip]
	cmp	r13d, 16383
	jg	.L4
	mov	rbx, rdi
	mov	edi, 1552
	movsx	rbp, esi
	call	malloc@PLT
	lea	rdx, entities[rip]
	mov	ecx, 128
	lea	r14, [rbx+rbp*8]
	mov	r15, rax
	movsx	rax, r13d
	mov	QWORD PTR [rdx+rax*8], r15
	mov	rdi, r15
	xor	eax, eax
	lea	rdx, 1024[r15]
	rep stosq
	mov	ecx, 64
	mov	rax, -1
	mov	rdi, rdx
	rep stosq
	test	ebp, ebp
	jg	.L13
	.p2align 4,,10
	.p2align 3
.L14:
	lea	eax, 1[r13]
	mov	DWORD PTR 1536[r15], r13d
	mov	DWORD PTR entity_count[rip], eax
	mov	rax, QWORD PTR id_counter[rip]
	mov	DWORD PTR 1540[r15], 0
	add	rax, 1
	mov	QWORD PTR id_counter[rip], rax
	mov	QWORD PTR 1544[r15], rax
.L4:
	add	rsp, 8
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	mov	rax, r15
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L19:
	.cfi_restore_state
	movsx	rbp, DWORD PTR 12[r12]
	cmp	QWORD PTR [r15+rbp*8], 0
	je	.L11
.L20:
	mov	eax, DWORD PTR 1024[r15+rbp*4]
	test	eax, eax
	js	.L11
.L8:
	add	rbx, 8
	cmp	rbx, r14
	je	.L14
.L13:
	mov	edx, DWORD PTR component_count[rip]
	mov	r12, QWORD PTR [rbx]
	cmp	edx, 127
	jg	.L8
	mov	ecx, DWORD PTR 16[r12]
	test	ecx, ecx
	jne	.L19
	lea	eax, 1[rdx]
	movsx	rbp, edx
	mov	DWORD PTR 12[r12], edx
	mov	DWORD PTR component_count[rip], eax
	cmp	QWORD PTR [r15+rbp*8], 0
	lea	rax, components[rip]
	mov	DWORD PTR 16[r12], 1
	mov	QWORD PTR [rax+rbp*8], r12
	jne	.L20
.L11:
	mov	rdi, QWORD PTR 24[r12]
	call	malloc@PLT
	mov	rdx, QWORD PTR [r12]
	mov	QWORD PTR [r15+rbp*8], rax
	movsx	rax, DWORD PTR 8[r12]
	lea	esi, 1[rax]
	mov	DWORD PTR 1024[r15+rbp*4], eax
	mov	DWORD PTR 8[r12], esi
	mov	QWORD PTR [rdx+rax*8], r15
	jmp	.L8
	.cfi_endproc
.LFE25:
	.size	add_entity, .-add_entity
	.p2align 4
	.globl	init_components
	.type	init_components, @function
init_components:
.LFB29:
	.cfi_startproc
	test	edx, edx
	jle	.L26
	movsx	rdx, edx
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	lea	r12, [rdi+rdx*8]
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	mov	rbp, rsi
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rbx, rdi
	.p2align 4,,10
	.p2align 3
.L23:
	mov	rax, QWORD PTR [rbx]
	add	rbx, 8
	mov	rdi, rbp
	call	[QWORD PTR 32[rax]]
	cmp	rbx, r12
	jne	.L23
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L26:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	ret
	.cfi_endproc
.LFE29:
	.size	init_components, .-init_components
	.p2align 4
	.globl	add_component
	.type	add_component, @function
add_component:
.LFB30:
	.cfi_startproc
	mov	eax, DWORD PTR component_count[rip]
	cmp	eax, 127
	jg	.L37
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	mov	r12, rsi
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	edx, DWORD PTR 16[rdi]
	mov	rbx, rdi
	test	edx, edx
	je	.L32
	movsx	rbp, DWORD PTR 12[rdi]
	cmp	QWORD PTR [r12+rbp*8], 0
	je	.L34
.L40:
	mov	eax, DWORD PTR 1024[r12+rbp*4]
	test	eax, eax
	js	.L34
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L37:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	ret
	.p2align 4,,10
	.p2align 3
.L32:
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	.cfi_offset 6, -24
	.cfi_offset 12, -16
	movsx	rbp, eax
	mov	DWORD PTR 12[rdi], eax
	lea	edx, 1[rax]
	lea	rax, components[rip]
	cmp	QWORD PTR [r12+rbp*8], 0
	mov	DWORD PTR 16[rdi], 1
	mov	DWORD PTR component_count[rip], edx
	mov	QWORD PTR [rax+rbp*8], rdi
	jne	.L40
.L34:
	mov	rdi, QWORD PTR 24[rbx]
	call	malloc@PLT
	mov	rdx, QWORD PTR [rbx]
	mov	QWORD PTR [r12+rbp*8], rax
	movsx	rax, DWORD PTR 8[rbx]
	lea	ecx, 1[rax]
	mov	DWORD PTR 1024[r12+rbp*4], eax
	mov	DWORD PTR 8[rbx], ecx
	mov	QWORD PTR [rdx+rax*8], r12
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE30:
	.size	add_component, .-add_component
	.p2align 4
	.globl	remove_component
	.type	remove_component, @function
remove_component:
.LFB31:
	.cfi_startproc
	mov	edx, DWORD PTR 16[rdi]
	test	edx, edx
	je	.L47
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsi
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	mov	rbx, rdi
	sub	rsp, 8
	.cfi_def_cfa_offset 32
	movsx	rax, DWORD PTR 12[rdi]
	cmp	QWORD PTR [rsi+rax*8], 0
	je	.L41
	mov	eax, DWORD PTR 1024[rsi+rax*4]
	test	eax, eax
	js	.L41
	mov	rdi, rsi
	call	[QWORD PTR 48[rbx]]
	movsx	rax, DWORD PTR 12[rbx]
	mov	rdi, QWORD PTR 0[rbp+rax*8]
	call	free@PLT
	movsx	rdi, DWORD PTR 12[rbx]
	mov	edx, DWORD PTR 8[rbx]
	lea	rcx, 256[rdi]
	lea	r8d, -1[rdx]
	mov	QWORD PTR 0[rbp+rdi*8], 0
	mov	esi, DWORD PTR 0[rbp+rcx*4]
	cmp	esi, r8d
	jge	.L43
	sub	edx, 2
	movsx	r10, esi
	mov	r9, QWORD PTR [rbx]
	sub	edx, esi
	add	rdx, r10
	lea	rax, [r9+r10*8]
	lea	rsi, 8[r9+rdx*8]
	.p2align 4,,10
	.p2align 3
.L44:
	mov	rdx, QWORD PTR 8[rax]
	add	rax, 8
	mov	QWORD PTR -8[rax], rdx
	sub	DWORD PTR [rdx+rcx*4], 1
	cmp	rax, rsi
	jne	.L44
.L43:
	mov	DWORD PTR 1024[rbp+rdi*4], -1
	mov	DWORD PTR 8[rbx], r8d
.L41:
	add	rsp, 8
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L47:
	.cfi_restore 3
	.cfi_restore 6
	ret
	.cfi_endproc
.LFE31:
	.size	remove_component, .-remove_component
	.p2align 4
	.globl	remove_entity
	.type	remove_entity, @function
remove_entity:
.LFB26:
	.cfi_startproc
	push	r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	mov	r13d, esi
	push	r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	push	rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	mov	rbp, rdi
	push	rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	sub	rsp, 8
	.cfi_def_cfa_offset 48
	mov	edx, DWORD PTR component_count[rip]
	test	edx, edx
	jle	.L51
	xor	ebx, ebx
	lea	r12, components[rip]
	.p2align 4,,10
	.p2align 3
.L53:
	mov	rdi, QWORD PTR [r12+rbx*8]
	movsx	rax, DWORD PTR 12[rdi]
	cmp	QWORD PTR 0[rbp+rax*8], 0
	je	.L52
	mov	eax, DWORD PTR 1024[rbp+rax*4]
	test	eax, eax
	js	.L52
	mov	rsi, rbp
	call	remove_component
.L52:
	add	rbx, 1
	cmp	DWORD PTR component_count[rip], ebx
	jg	.L53
.L51:
	test	r13d, r13d
	je	.L54
	mov	edx, DWORD PTR entity_count[rip]
	mov	ecx, DWORD PTR 1536[rbp]
	lea	eax, -1[rdx]
	cmp	ecx, eax
	jge	.L54
	sub	edx, 2
	movsx	rsi, ecx
	lea	rax, entities[rip]
	sub	edx, ecx
	lea	rcx, entities[rip+8]
	lea	rax, [rax+rsi*8]
	add	rdx, rsi
	lea	rcx, [rcx+rdx*8]
	.p2align 4,,10
	.p2align 3
.L55:
	mov	rdx, QWORD PTR 8[rax]
	add	rax, 8
	mov	QWORD PTR -8[rax], rdx
	sub	DWORD PTR 1536[rdx], 1
	cmp	rax, rcx
	jne	.L55
.L54:
	mov	rdi, rbp
	call	free@PLT
	sub	DWORD PTR entity_count[rip], 1
	add	rsp, 8
	.cfi_def_cfa_offset 40
	pop	rbx
	.cfi_def_cfa_offset 32
	pop	rbp
	.cfi_def_cfa_offset 24
	pop	r12
	.cfi_def_cfa_offset 16
	pop	r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE26:
	.size	remove_entity, .-remove_entity
	.p2align 4
	.globl	update_ecs
	.type	update_ecs, @function
update_ecs:
.LFB27:
	.cfi_startproc
	mov	edi, DWORD PTR component_count[rip]
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	test	edi, edi
	jle	.L63
	lea	rbp, components[rip]
	xor	r12d, r12d
	.p2align 4,,10
	.p2align 3
.L64:
	mov	rax, QWORD PTR 0[rbp]
	xor	ebx, ebx
	mov	ecx, DWORD PTR 8[rax]
	test	ecx, ecx
	jle	.L67
	.p2align 4,,10
	.p2align 3
.L66:
	mov	rdx, QWORD PTR [rax]
	mov	rdi, QWORD PTR [rdx+rbx*8]
	mov	esi, DWORD PTR 1540[rdi]
	test	esi, esi
	jne	.L65
	call	[QWORD PTR 40[rax]]
	mov	rax, QWORD PTR 0[rbp]
.L65:
	add	rbx, 1
	cmp	DWORD PTR 8[rax], ebx
	jg	.L66
.L67:
	add	r12d, 1
	add	rbp, 8
	cmp	DWORD PTR component_count[rip], r12d
	jg	.L64
.L63:
	mov	edx, DWORD PTR entity_count[rip]
	xor	ebx, ebx
	lea	rbp, entities[rip]
	test	edx, edx
	jg	.L68
	jmp	.L62
	.p2align 4,,10
	.p2align 3
.L79:
	add	ebx, 1
	cmp	DWORD PTR entity_count[rip], ebx
	jle	.L62
.L68:
	movsx	rax, ebx
	mov	rdi, QWORD PTR 0[rbp+rax*8]
	mov	eax, DWORD PTR 1540[rdi]
	test	eax, eax
	je	.L79
	mov	esi, 1
	call	remove_entity
	cmp	DWORD PTR entity_count[rip], ebx
	jg	.L68
.L62:
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE27:
	.size	update_ecs, .-update_ecs
	.p2align 4
	.globl	delete_ecs
	.type	delete_ecs, @function
delete_ecs:
.LFB28:
	.cfi_startproc
	movsx	rax, DWORD PTR entity_count[rip]
	test	eax, eax
	jle	.L85
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	lea	rbx, entities[rip]
	lea	rbp, [rbx+rax*8]
	sub	rsp, 8
	.cfi_def_cfa_offset 32
	.p2align 4,,10
	.p2align 3
.L82:
	mov	rdi, QWORD PTR [rbx]
	xor	esi, esi
	add	rbx, 8
	call	remove_entity
	cmp	rbx, rbp
	jne	.L82
	add	rsp, 8
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L85:
	.cfi_restore 3
	.cfi_restore 6
	ret
	.cfi_endproc
.LFE28:
	.size	delete_ecs, .-delete_ecs
	.globl	component_count
	.bss
	.align 4
	.type	component_count, @object
	.size	component_count, 4
component_count:
	.zero	4
	.globl	entity_count
	.align 4
	.type	entity_count, @object
	.size	entity_count, 4
entity_count:
	.zero	4
	.local	id_counter
	.comm	id_counter,8,8
	.globl	components
	.align 32
	.type	components, @object
	.size	components, 1024
components:
	.zero	1024
	.globl	entities
	.align 32
	.type	entities, @object
	.size	entities, 131072
entities:
	.zero	131072
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
