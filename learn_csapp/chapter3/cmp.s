	.file	"cmp.c"
	.text
	.globl	comp
	.type	comp, @function
comp:
.LFB0:
	.cfi_startproc
	movl	8(%esp), %eax
	cmpl	%eax, 4(%esp)
	setl	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	comp, .-comp
	.globl	comp2
	.type	comp2, @function
comp2:
.LFB1:
	.cfi_startproc
	movl	8(%esp), %eax
	cmpl	%eax, 4(%esp)
	setb	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	comp2, .-comp2
	.globl	comp3
	.type	comp3, @function
comp3:
.LFB2:
	.cfi_startproc
	movzwl	8(%esp), %eax
	cmpw	%ax, 4(%esp)
	setl	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	comp3, .-comp3
	.globl	comp4
	.type	comp4, @function
comp4:
.LFB3:
	.cfi_startproc
	movzwl	8(%esp), %eax
	cmpw	%ax, 4(%esp)
	setb	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE3:
	.size	comp4, .-comp4
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
