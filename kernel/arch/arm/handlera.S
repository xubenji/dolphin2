.section .text
.global vector_table
.global enable_timer
.global read_timer_freq
.global read_timer_status
.global set_timer_interval
.global enable_irq
.global set_elr_el
.global disable_timer
.global irq_return
.global set_spsr_el

.balign 0x800
vector_table:
current_el_sp0_sync:
    b error

.balign 0x80
current_el_sp0_irq:
    b error

.balign 0x80
current_el_sp0_fiq:
    b error

.balign 0x80
current_el_sp0_serror:
    b error

.balign 0x80
current_el_spn_sync:
    b sync_handler

.balign 0x80
current_el_spn_irq:
    b irq_handler

.balign 0x80
current_el_spn_fiq:
    b error

.balign 0x80
current_el_spn_serror:
    b error

.balign 0x80
lower_el_aarch64_sync:
    b error

.balign 0x80
lower_el_aarch64_irq:
    b error

.balign 0x80
lower_el_aarch64_fiq:
    b error

.balign 0x80
lower_el_aarch64_serror:
    b error

.balign 0x80
lower_el_aarch32_sync:
    b error

.balign 0x80
lower_el_aarch32_irq:
    b error

.balign 0x80
lower_el_aarch32_fiq:
    b error

.balign 0x80
lower_el_aarch32_serror:
    b error


sync_handler:
    sub sp, sp, #(32 * 8)
    stp x0, x1, [sp]
    stp x2, x3, [sp, #(16 * 1)]
    stp x4, x5, [sp, #(16 * 2)]
    stp	x6, x7, [sp, #(16 * 3)]
	stp	x8, x9, [sp, #(16 * 4)]
	stp	x10, x11, [sp, #(16 * 5)]
	stp	x12, x13, [sp, #(16 * 6)]
	stp	x14, x15, [sp, #(16 * 7)]
	stp	x16, x17, [sp, #(16 * 8)]
	stp	x18, x19, [sp, #(16 * 9)]
	stp	x20, x21, [sp, #(16 * 10)]
	stp	x22, x23, [sp, #(16 * 11)]
	stp	x24, x25, [sp, #(16 * 12)]
	stp	x26, x27, [sp, #(16 * 13)]
	stp	x28, x29, [sp, #(16 * 14)]
    str x30, [sp, #(16 * 15)]

    mov x0, #1
    mrs x1, esr_el1
    mrs x2, elr_el1
    bl handler

    ldp x0, x1, [sp]
    ldp x2, x3, [sp, #(16 * 1)]
    ldp x4, x5, [sp, #(16 * 2)]
    ldp	x6, x7, [sp, #(16 * 3)]
	ldp	x8, x9, [sp, #(16 * 4)]
	ldp	x10, x11, [sp, #(16 * 5)]
	ldp	x12, x13, [sp, #(16 * 6)]
	ldp	x14, x15, [sp, #(16 * 7)]
	ldp	x16, x17, [sp, #(16 * 8)]
	ldp	x18, x19, [sp, #(16 * 9)]
	ldp	x20, x21, [sp, #(16 * 10)]
	ldp	x22, x23, [sp, #(16 * 11)]
	ldp	x24, x25, [sp, #(16 * 12)]
	ldp	x26, x27, [sp, #(16 * 13)]
	ldp	x28, x29, [sp, #(16 * 14)]
    ldr x30, [sp, #(16 * 15)]

    add sp, sp, #(32 * 8)
    eret

irq_handler:
    sub sp, sp, #(32 * 8)
    stp x0, x1, [sp]
    stp x2, x3, [sp, #(16 * 1)]
    stp x4, x5, [sp, #(16 * 2)]
    stp	x6, x7, [sp, #(16 * 3)]
	stp	x8, x9, [sp, #(16 * 4)]
	stp	x10, x11, [sp, #(16 * 5)]
	stp	x12, x13, [sp, #(16 * 6)]
	stp	x14, x15, [sp, #(16 * 7)]
	stp	x16, x17, [sp, #(16 * 8)]
	stp	x18, x19, [sp, #(16 * 9)]
	stp	x20, x21, [sp, #(16 * 10)]
	stp	x22, x23, [sp, #(16 * 11)]
	stp	x24, x25, [sp, #(16 * 12)]
	stp	x26, x27, [sp, #(16 * 13)]
	stp	x28, x29, [sp, #(16 * 14)]
    str x30, [sp, #(16 * 15)]

    mov x0, #2
    mrs x1, esr_el1
    mrs x2, elr_el1
    mov x3, sp
    mrs x4, spsr_el1
    bl handler

irq_return:
    ldp x2, x3, [x0, #(16 * 1)]
    ldp x4, x5, [x0, #(16 * 2)]
    ldp	x6, x7, [x0, #(16 * 3)]
	ldp	x8, x9, [x0, #(16 * 4)]
	ldp	x10, x11, [x0, #(16 * 5)]
	ldp	x12, x13, [x0, #(16 * 6)]
	ldp	x14, x15, [x0, #(16 * 7)]
	ldp	x16, x17, [x0, #(16 * 8)]
	ldp	x18, x19, [x0, #(16 * 9)]
	ldp	x20, x21, [x0, #(16 * 10)]
	ldp	x22, x23, [x0, #(16 * 11)]
	ldp	x24, x25, [x0, #(16 * 12)]
	ldp	x26, x27, [x0, #(16 * 13)]
	ldp	x28, x29, [x0, #(16 * 14)]
    ldr x30, [x0, #(8 * 31)]
    mov sp, x30
    ldr x1, [x0, #(8*1)]
    mov x30, #1
    msr CNTP_CTL_EL0, x30
    ldr x30, [x0, #(8 * 30)]
    
    ldr x0, [x0]    
    
    eret

error:
    sub sp, sp, #(32 * 8)
    stp x0, x1, [sp]
    stp x2, x3, [sp, #(16 * 1)]
    stp x4, x5, [sp, #(16 * 2)]
    stp	x6, x7, [sp, #(16 * 3)]
	stp	x8, x9, [sp, #(16 * 4)]
	stp	x10, x11, [sp, #(16 * 5)]
	stp	x12, x13, [sp, #(16 * 6)]
	stp	x14, x15, [sp, #(16 * 7)]
	stp	x16, x17, [sp, #(16 * 8)]
	stp	x18, x19, [sp, #(16 * 9)]
	stp	x20, x21, [sp, #(16 * 10)]
	stp	x22, x23, [sp, #(16 * 11)]
	stp	x24, x25, [sp, #(16 * 12)]
	stp	x26, x27, [sp, #(16 * 13)]
	stp	x28, x29, [sp, #(16 * 14)]
    str x30, [sp, #(16 * 15)]

    mov x0, #0
    bl handler

    ldp x0, x1, [sp]
    ldp x2, x3, [sp, #(16 * 1)]
    ldp x4, x5, [sp, #(16 * 2)]
    ldp	x6, x7, [sp, #(16 * 3)]
	ldp	x8, x9, [sp, #(16 * 4)]
	ldp	x10, x11, [sp, #(16 * 5)]
	ldp	x12, x13, [sp, #(16 * 6)]
	ldp	x14, x15, [sp, #(16 * 7)]
	ldp	x16, x17, [sp, #(16 * 8)]
	ldp	x18, x19, [sp, #(16 * 9)]
	ldp	x20, x21, [sp, #(16 * 10)]
	ldp	x22, x23, [sp, #(16 * 11)]
	ldp	x24, x25, [sp, #(16 * 12)]
	ldp	x26, x27, [sp, #(16 * 13)]
	ldp	x28, x29, [sp, #(16 * 14)]
    ldr x30, [sp, #(16 * 15)]

    add sp, sp, #(32 * 8)
    eret
    
read_timer_freq:
    mrs x0, CNTFRQ_EL0
    ret

set_timer_interval:
    msr CNTP_TVAL_El0, x0
    ret

enable_timer:
    stp x29, x30, [sp, #-16]!

    bl read_timer_freq
    mov x1, #100
    udiv x0, x0, x1
    bl set_timer_interval

    mov x0, #1
    msr CNTP_CTL_EL0, x0

    ldp x29, x30, [sp], #16
    ret

read_timer_status:
    mrs x0, CNTP_CTL_EL0
    ret

enable_irq:
    msr daifclr, #2
    ret

set_elr_el:
    msr elr_el1, x0
    ret

set_spsr_el:
    msr spsr_el1, x0
    ret

disable_timer:
    mov x0, #0
    msr CNTP_CTL_EL0, x0
    ret
