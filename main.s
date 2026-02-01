parse_proc_files:
;; modify an address after storing it
;; so were modifying
;; it's called the post index invarient
	stp x29, x30, [sp, #-96]!
	mov x29, sp
	str x0, [sp, #24]
	str x1, [sp, #16]               str xzr, [sp, #80]
	mov w0, #0x3a                   // #58
	strb w0, [sp, #79]
	mov w0, #0x920                  // #2336
	strh w0, [sp, #32]
	mov w0, #0xa                    // #10
	strb w0, [sp, #78]
	mov x1, #0x8                    // #8
	ldr x0, [sp, #16]
	bl 0x400a6c <arena_alloc>
	str x0, [sp, #64]
	ldr x0, [sp, #24]
	cmp x0, #0x0
	b.eq 0x400f50 <parse_proc_files+84>  // b.none
	ldr x0, [sp, #16]
	cmp x0, #0x0
	b.ne 0x400fa8 <parse_proc_files+172>  // b.any
	mov x2, #0x9                    // #9
	adrp x0, 0x401000 <is_numeric+8>
	add x1, x0, #0x788
	mov w0, #0x1                    // #1
	bl 0x400700 <write@plt>
	mov x2, #0x32                   // #50
	adrp x0, 0x401000 <is_numeric+8>
	add x1, x0, #0x798
	mov w0, #0x2                    // #2
	bl 0x400700 <write@plt>
	mov x2, #0x32                   // #50
	adrp x0, 0x401000 <is_numeric+8>
	add x1, x0, #0x860
	mov w0, #0x1                    // #1
	bl 0x400700 <write@plt>
	mov x2, #0x1                    // #1
	adrp x0, 0x401000 <is_numeric+8>
	add x1, x0, #0x7b8
	mov w0, #0x1                    // #1
	bl 0x400700 <write@plt>
	mov x0, #0x0                    // #0
	b 0x400ff0 <parse_proc_files+244>
	mov x2, #0x8                    // #8
	ldr x1, [sp, #88]
	ldr w0, [sp, #60]
	bl 0x400740 <read@plt>
	str x0, [sp, #48]
	b 0x400fd4 <parse_proc_files+216>
	ldr x0, [sp, #88]
	str x0, [sp, #40]
	ldr x0, [sp, #88]
	add x0, x0, #0x1
	str x0, [sp, #88]
	ldr x1, [sp, #80]
	ldr x0, [sp, #48]
	cmp x1, x0
	b.cc 0x400fc0 <parse_proc_files+196>  // b.lo, b.ul, b.last
	ldr w0, [sp, #60]
	bl 0x4006e0 <close@plt>
	ldr x0, [sp, #64]
	ldp x29, x30, [sp], #96
	ret


__internal_syscall_cancel:
	bti c
	mrs x9, tpidr_el0
	sub x9, x9, #0x618
	ldr w7, [x9]
	adrp x8, 0xfffff7f87000 <fork_handlers+1184>
	ldrb w8, [x8, #1432]
	cbnz w8, 0xfffff7e4b858 <__internal_syscall_cancel+120>
	tbnz w7, #0, 0xfffff7e4b858 <__internal_syscall_cancel+120>
	tbnz w7, #4, 0xfffff7e4b858 <__internal_syscall_cancel+120>
	mov x8, x6
	paciasp
	stp x29, x30, [sp, #-32]!
	mov x7, x5
	mov x5, x3
	mov x3, x1
	mov x1, x8
	mov x29, sp
	mov x6, x4
	mov x4, x2
	mov x2, x0
	mov x0, x9
	str x9, [sp, #24]
	bl 0xfffff7e58e40 <__syscall_cancel_arch>
	ldr x9, [sp, #24]
	ldr w1, [x9]
	cmn x0, #0x4
	b.eq 0xfffff7e4b864 <__internal_syscall_cancel+132>  // b.none
	ldp x29, x30, [sp], #32
	autiasp
	ret
	mov x8, x6
	svc #0x0
	ret
	mov w2, #0x39                   // #57
	and w1, w1, w2
	cmp w1, #0x8
	b.ne 0xfffff7e4b84c <__internal_syscall_cancel+108>  // b.any
	bl 0xfffff7e4b780 <__syscall_do_cancel>

