	.file	"matrix.c"
	.text
	.comm	A,8388608,32
	.comm	B,8388608,32
	.comm	C,8388608,32
	.comm	ld,4,4
	.section	.rodata
.LC0:
	.string	"%lf"
	.text
	.globl	readMatrix
	.type	readMatrix, @function
readMatrix:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movq	-32(%rbp), %rax
	leaq	.LC0(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	addl	$1, -4(%rbp)
.L2:
	cmpl	$1023, -4(%rbp)
	jle	.L3
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	readMatrix, .-readMatrix
	.globl	mymatmul
	.type	mymatmul, @function
mymatmul:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L5
.L10:
	movl	$0, -8(%rbp)
	jmp	.L6
.L9:
	movl	$0, -4(%rbp)
	jmp	.L7
.L8:
	movl	ld(%rip), %eax
	imull	-8(%rbp), %eax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	C(%rip), %rax
	movsd	(%rdx,%rax), %xmm1
	movl	ld(%rip), %eax
	imull	-8(%rbp), %eax
	movl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	A(%rip), %rax
	movsd	(%rdx,%rax), %xmm2
	movl	ld(%rip), %eax
	imull	-12(%rbp), %eax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	B(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	mulsd	%xmm2, %xmm0
	movl	ld(%rip), %eax
	imull	-8(%rbp), %eax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	addsd	%xmm1, %xmm0
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	C(%rip), %rax
	movsd	%xmm0, (%rdx,%rax)
	addl	$1, -4(%rbp)
.L7:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L8
	addl	$1, -8(%rbp)
.L6:
	movl	-8(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L9
	addl	$1, -12(%rbp)
.L5:
	movl	-12(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L10
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	mymatmul, .-mymatmul
	.globl	cblasmatmul
	.type	cblasmatmul, @function
cblasmatmul:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movsd	.LC1(%rip), %xmm0
	movq	.LC1(%rip), %rdx
	movl	-4(%rbp), %edi
	movl	-4(%rbp), %esi
	movl	-4(%rbp), %eax
	movl	-4(%rbp), %ecx
	pushq	%rcx
	leaq	C(%rip), %rcx
	pushq	%rcx
	movl	-4(%rbp), %ecx
	pushq	%rcx
	leaq	B(%rip), %rcx
	pushq	%rcx
	movl	-4(%rbp), %ecx
	pushq	%rcx
	leaq	A(%rip), %rcx
	pushq	%rcx
	movapd	%xmm0, %xmm1
	movq	%rdx, %xmm0
	movl	%edi, %r9d
	movl	%esi, %r8d
	movl	%eax, %ecx
	movl	$111, %edx
	movl	$111, %esi
	movl	$101, %edi
	call	cblas_dgemm@PLT
	addq	$48, %rsp
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	cblasmatmul, .-cblasmatmul
	.section	.rodata
.LC2:
	.string	"r"
.LC3:
	.string	"../matrix/matrixA.txt"
.LC4:
	.string	"../matrix/matrixB.txt"
.LC5:
	.string	"w"
.LC6:
	.string	"../matrix/data.csv"
.LC7:
	.string	"N,my,GEMM\n"
.LC9:
	.string	"%d,%lf,%lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	leaq	.LC2(%rip), %rsi
	leaq	.LC3(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -56(%rbp)
	leaq	.LC2(%rip), %rsi
	leaq	.LC4(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -48(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	leaq	A(%rip), %rdi
	call	readMatrix
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	leaq	B(%rip), %rdi
	call	readMatrix
	leaq	.LC5(%rip), %rsi
	leaq	.LC6(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rcx
	movl	$10, %edx
	movl	$1, %esi
	leaq	.LC7(%rip), %rdi
	call	fwrite@PLT
	movl	$20, ld(%rip)
	jmp	.L13
.L14:
	call	clock@PLT
	movq	%rax, -32(%rbp)
	movl	ld(%rip), %eax
	movl	%eax, %edi
	call	mymatmul
	call	clock@PLT
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	subq	-32(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC8(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	call	clock@PLT
	movq	%rax, -32(%rbp)
	movl	ld(%rip), %eax
	movl	%eax, %edi
	call	cblasmatmul
	call	clock@PLT
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	subq	-32(%rbp), %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	.LC8(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	ld(%rip), %edx
	movsd	-8(%rbp), %xmm0
	movq	-16(%rbp), %rcx
	movq	-40(%rbp), %rax
	movapd	%xmm0, %xmm1
	movq	%rcx, %xmm0
	leaq	.LC9(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	movl	ld(%rip), %eax
	addl	$20, %eax
	movl	%eax, ld(%rip)
.L13:
	movl	ld(%rip), %eax
	cmpl	$1023, %eax
	jle	.L14
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1072693248
	.align 8
.LC8:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
