
    .text
    .globl main
main:
    addi sp, sp, -128


    li t0, 0
    sw t0, 120(sp)


    li t1, 1
    sw t1, 116(sp)


    li t2, 2
    sw t2, 112(sp)


    lw t3, 120(sp)
    sw t3, 108(sp)

    li t4, 0
    lw t5, 108(sp)
    lw t6, 104(sp)
    xor t6, t4, t5
    snez t6, t6
    sw t6, 104(sp)

    lw a0, 104(sp)
    sw a0, 100(sp)

    lw a1, 104(sp)
    bnez a1, or2_end
    j or2_then

or2_end:
    lw a2, 100(sp)
    sw a2, 96(sp)

    lw a3, 96(sp)
    bnez a3, if1_then
    j if1_else

if1_then:
    li a4, 3
    sw a4, 116(sp)

    j if1_end

if1_end:
    lw a5, 120(sp)
    sw a5, 92(sp)

    lw a6, 92(sp)
    li t0, 0
    lw t1, 88(sp)
    add t1, a6, t0
    sw t1, 88(sp)

    lw t2, 116(sp)
    sw t2, 84(sp)

    lw t3, 88(sp)
    lw t4, 84(sp)
    lw t5, 80(sp)
    add t5, t3, t4
    sw t5, 80(sp)

    lw t6, 112(sp)
    sw t6, 76(sp)

    lw a0, 80(sp)
    lw a1, 76(sp)
    lw a2, 72(sp)
    add a2, a0, a1
    sw a2, 72(sp)

    lw a3, 72(sp)
    mv a0, a3
    j main_end

if1_else:
    li a4, 3
    sw a4, 112(sp)


    li a5, 1
    sw a5, 68(sp)


    lw a6, 68(sp)
    sw a6, 64(sp)

    li t0, 0
    lw t1, 64(sp)
    lw t2, 60(sp)
    xor t2, t0, t1
    snez t2, t2
    sw t2, 60(sp)

    lw t3, 60(sp)
    sw t3, 56(sp)

    lw t4, 60(sp)
    bnez t4, or4_end
    j or4_then

or4_end:
    lw t5, 56(sp)
    sw t5, 52(sp)

    lw t6, 52(sp)
    bnez t6, if3_then
    j if3_else

if3_then:
    li a0, 4
    sw a0, 116(sp)

    j if3_end

if3_end:
    lw a1, 68(sp)
    sw a1, 48(sp)

    lw a2, 48(sp)
    li a3, 0
    lw a4, 44(sp)
    xor a4, a2, a3
    seqz a4, a4
    sw a4, 44(sp)

    lw a5, 44(sp)
    bnez a5, if5_then
    j if5_else

if5_then:
    li a0, 1
    j main_end

if5_else:

    lw a6, 68(sp)
    sw a6, 40(sp)

    lw t0, 40(sp)
    li t1, 0
    lw t2, 36(sp)
    xor t2, t0, t1
    seqz t2, t2
    sw t2, 36(sp)

    li t3, 0
    lw t4, 36(sp)
    lw t5, 32(sp)
    xor t5, t3, t4
    snez t5, t5
    sw t5, 32(sp)

    lw t6, 32(sp)
    sw t6, 28(sp)

    lw a0, 32(sp)
    bnez a0, and7_then
    j and7_end

and7_then:
    lw a1, 68(sp)
    sw a1, 24(sp)

    li a2, 0
    li a3, 1
    lw a4, 20(sp)
    sub a4, a2, a3
    sw a4, 20(sp)

    lw a5, 24(sp)
    lw a6, 20(sp)
    lw t0, 16(sp)
    xor t0, a5, a6
    seqz t0, t0
    sw t0, 16(sp)

    li t1, 0
    lw t2, 16(sp)
    lw t3, 12(sp)
    xor t3, t1, t2
    snez t3, t3
    sw t3, 12(sp)

    lw t4, 12(sp)
    sw t4, 28(sp)

    j and7_end

and7_end:
    lw t5, 28(sp)
    sw t5, 8(sp)

    lw t6, 8(sp)
    bnez t6, if6_then
    j if6_end

if6_then:
    li a0, 2
    j main_end

if6_end:
    j if5_end

if5_end:
    j if1_end

if3_else:
    li a0, 4
    sw a0, 112(sp)

    j if3_end

or4_then:
    li a1, 0
    li a2, 0
    lw a3, 4(sp)
    xor a3, a1, a2
    snez a3, a3
    sw a3, 4(sp)

    lw a4, 4(sp)
    sw a4, 56(sp)

    j or4_end

or2_then:
    li a5, 0
    li a6, 0
    lw t0, 0(sp)
    xor t0, a5, a6
    snez t0, t0
    sw t0, 0(sp)

    lw t1, 0(sp)
    sw t1, 100(sp)

    j or2_end
main_end:
    addi sp, sp, 128
    ret

