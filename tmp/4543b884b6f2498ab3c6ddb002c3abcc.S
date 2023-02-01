
    .text
    .globl t
t:
    addi sp, sp, -16

    lw t0, 4(sp)
    sw t0, 0(sp)

    lw t1, 0(sp)
    li t2, 1
    lw t3, 18446744073709551612(sp)
    add t3, t1, t2
    sw t3, 18446744073709551612(sp)

    lw t4, 18446744073709551612(sp)
    sw t4, 4(sp)

    li a0, 1
    j t_end
t_end:
    addi sp, sp, 16
    ret

    .text
    .globl f
f:
    addi sp, sp, -16

    lw t5, 4(sp)
    sw t5, 0(sp)

    lw t6, 0(sp)
    li a0, 1
    lw a1, 18446744073709551612(sp)
    add a1, t6, a0
    sw a1, 18446744073709551612(sp)

    lw a2, 18446744073709551612(sp)
    sw a2, 4(sp)

    li a0, 0
    j f_end
f_end:
    addi sp, sp, 16
    ret

    .text
    .globl main
main:
    addi sp, sp, -544
    sw ra, 536(sp)


    li a3, 0
    sw a3, 532(sp)

    lw a4, 532(sp)
    sw a4, 528(sp)


    call f
    sw a0, 524(sp)
    li a5, 0
    lw a6, 524(sp)
    lw t0, 520(sp)
    xor t0, a5, a6
    snez t0, t0
    sw t0, 520(sp)

    lw t1, 520(sp)
    sw t1, 516(sp)

    lw t2, 520(sp)
    bnez t2, or1_end
    j or1_then

or1_end:
    lw t3, 516(sp)
    sw t3, 512(sp)

    lw t4, 528(sp)
    lw t5, 512(sp)
    lw t6, 508(sp)
    add t6, t4, t5
    sw t6, 508(sp)

    lw a0, 508(sp)
    sw a0, 532(sp)

    lw a1, 532(sp)
    sw a1, 504(sp)


    call f
    sw a0, 500(sp)
    li a2, 0
    lw a3, 500(sp)
    lw a4, 496(sp)
    xor a4, a2, a3
    snez a4, a4
    sw a4, 496(sp)

    lw a5, 496(sp)
    sw a5, 492(sp)

    lw a6, 496(sp)
    bnez a6, or2_end
    j or2_then

or2_end:
    lw t0, 492(sp)
    sw t0, 488(sp)

    lw t1, 504(sp)
    lw t2, 488(sp)
    lw t3, 484(sp)
    add t3, t1, t2
    sw t3, 484(sp)

    lw t4, 484(sp)
    sw t4, 532(sp)

    lw t5, 532(sp)
    sw t5, 480(sp)


    call t
    sw a0, 476(sp)
    li t6, 0
    lw a0, 476(sp)
    lw a1, 472(sp)
    xor a1, t6, a0
    snez a1, a1
    sw a1, 472(sp)

    lw a2, 472(sp)
    sw a2, 468(sp)

    lw a3, 472(sp)
    bnez a3, or3_end
    j or3_then

or3_end:
    lw a4, 468(sp)
    sw a4, 464(sp)

    lw a5, 480(sp)
    lw a6, 464(sp)
    lw t0, 460(sp)
    add t0, a5, a6
    sw t0, 460(sp)

    lw t1, 460(sp)
    sw t1, 532(sp)

    lw t2, 532(sp)
    sw t2, 456(sp)


    call t
    sw a0, 452(sp)
    li t3, 0
    lw t4, 452(sp)
    lw t5, 448(sp)
    xor t5, t3, t4
    snez t5, t5
    sw t5, 448(sp)

    lw t6, 448(sp)
    sw t6, 444(sp)

    lw a0, 448(sp)
    bnez a0, or4_end
    j or4_then

or4_end:
    lw a1, 444(sp)
    sw a1, 440(sp)

    lw a2, 456(sp)
    lw a3, 440(sp)
    lw a4, 436(sp)
    add a4, a2, a3
    sw a4, 436(sp)

    lw a5, 436(sp)
    sw a5, 532(sp)

    lw a6, 532(sp)
    sw a6, 432(sp)


    call f
    sw a0, 428(sp)
    li t0, 0
    lw t1, 428(sp)
    lw t2, 424(sp)
    xor t2, t0, t1
    snez t2, t2
    sw t2, 424(sp)

    lw t3, 424(sp)
    sw t3, 420(sp)

    lw t4, 424(sp)
    bnez t4, and5_then
    j and5_end

and5_then:
    call f
    sw a0, 416(sp)
    li t5, 0
    lw t6, 416(sp)
    lw a0, 412(sp)
    xor a0, t5, t6
    snez a0, a0
    sw a0, 412(sp)

    lw a1, 412(sp)
    sw a1, 420(sp)

    j and5_end

and5_end:
    lw a2, 420(sp)
    sw a2, 408(sp)

    lw a3, 432(sp)
    lw a4, 408(sp)
    lw a5, 404(sp)
    add a5, a3, a4
    sw a5, 404(sp)

    lw a6, 404(sp)
    sw a6, 532(sp)

    lw t0, 532(sp)
    sw t0, 400(sp)


    call f
    sw a0, 396(sp)
    li t1, 0
    lw t2, 396(sp)
    lw t3, 392(sp)
    xor t3, t1, t2
    snez t3, t3
    sw t3, 392(sp)

    lw t4, 392(sp)
    sw t4, 388(sp)

    lw t5, 392(sp)
    bnez t5, and6_then
    j and6_end

and6_then:
    call t
    sw a0, 384(sp)
    li t6, 0
    lw a0, 384(sp)
    lw a1, 380(sp)
    xor a1, t6, a0
    snez a1, a1
    sw a1, 380(sp)

    lw a2, 380(sp)
    sw a2, 388(sp)

    j and6_end

and6_end:
    lw a3, 388(sp)
    sw a3, 376(sp)

    lw a4, 400(sp)
    lw a5, 376(sp)
    lw a6, 372(sp)
    add a6, a4, a5
    sw a6, 372(sp)

    lw t0, 372(sp)
    sw t0, 532(sp)

    lw t1, 532(sp)
    sw t1, 368(sp)


    call t
    sw a0, 364(sp)
    li t2, 0
    lw t3, 364(sp)
    lw t4, 360(sp)
    xor t4, t2, t3
    snez t4, t4
    sw t4, 360(sp)

    lw t5, 360(sp)
    sw t5, 356(sp)

    lw t6, 360(sp)
    bnez t6, and7_then
    j and7_end

and7_then:
    call f
    sw a0, 352(sp)
    li a0, 0
    lw a1, 352(sp)
    lw a2, 348(sp)
    xor a2, a0, a1
    snez a2, a2
    sw a2, 348(sp)

    lw a3, 348(sp)
    sw a3, 356(sp)

    j and7_end

and7_end:
    lw a4, 356(sp)
    sw a4, 344(sp)

    lw a5, 368(sp)
    lw a6, 344(sp)
    lw t0, 340(sp)
    add t0, a5, a6
    sw t0, 340(sp)

    lw t1, 340(sp)
    sw t1, 532(sp)

    lw t2, 532(sp)
    sw t2, 336(sp)


    call t
    sw a0, 332(sp)
    li t3, 0
    lw t4, 332(sp)
    lw t5, 328(sp)
    xor t5, t3, t4
    snez t5, t5
    sw t5, 328(sp)

    lw t6, 328(sp)
    sw t6, 324(sp)

    lw a0, 328(sp)
    bnez a0, and8_then
    j and8_end

and8_then:
    call t
    sw a0, 320(sp)
    li a1, 0
    lw a2, 320(sp)
    lw a3, 316(sp)
    xor a3, a1, a2
    snez a3, a3
    sw a3, 316(sp)

    lw a4, 316(sp)
    sw a4, 324(sp)

    j and8_end

and8_end:
    lw a5, 324(sp)
    sw a5, 312(sp)

    lw a6, 336(sp)
    lw t0, 312(sp)
    lw t1, 308(sp)
    add t1, a6, t0
    sw t1, 308(sp)

    lw t2, 308(sp)
    sw t2, 532(sp)


    call t
    sw a0, 304(sp)
    li t3, 0
    lw t4, 304(sp)
    lw t5, 300(sp)
    xor t5, t3, t4
    snez t5, t5
    sw t5, 300(sp)

    lw t6, 300(sp)
    sw t6, 296(sp)

    lw a0, 300(sp)
    bnez a0, or9_end
    j or9_then

or9_end:
    lw a1, 296(sp)
    sw a1, 292(sp)


    call f
    sw a0, 288(sp)
    li a2, 0
    lw a3, 288(sp)
    lw a4, 284(sp)
    xor a4, a2, a3
    snez a4, a4
    sw a4, 284(sp)

    lw a5, 284(sp)
    sw a5, 280(sp)

    lw a6, 284(sp)
    bnez a6, or11_end
    j or11_then

or11_end:
    lw t0, 280(sp)
    sw t0, 276(sp)


    call f
    sw a0, 272(sp)
    li t1, 0
    lw t2, 272(sp)
    lw t3, 268(sp)
    xor t3, t1, t2
    snez t3, t3
    sw t3, 268(sp)

    lw t4, 268(sp)
    sw t4, 264(sp)

    lw t5, 268(sp)
    bnez t5, or13_end
    j or13_then

or13_end:
    lw t6, 264(sp)
    sw t6, 260(sp)



    call t
    sw a0, 256(sp)
    li a0, 0
    lw a1, 256(sp)
    lw a2, 252(sp)
    xor a2, a0, a1
    snez a2, a2
    sw a2, 252(sp)

    lw a3, 252(sp)
    sw a3, 248(sp)

    lw a4, 252(sp)
    bnez a4, and16_then
    j and16_end

and16_then:
    call t
    sw a0, 244(sp)
    li a5, 0
    lw a6, 244(sp)
    lw t0, 240(sp)
    xor t0, a5, a6
    snez t0, t0
    sw t0, 240(sp)

    lw t1, 240(sp)
    sw t1, 248(sp)

    j and16_end

and16_end:
    lw t2, 248(sp)
    sw t2, 236(sp)

    li t3, 0
    lw t4, 236(sp)
    lw t5, 232(sp)
    xor t5, t3, t4
    snez t5, t5
    sw t5, 232(sp)

    lw t6, 232(sp)
    sw t6, 228(sp)

    lw a0, 232(sp)
    bnez a0, or15_end
    j or15_then

or15_end:
    lw a1, 228(sp)
    sw a1, 224(sp)



    call f
    sw a0, 220(sp)
    li a2, 0
    lw a3, 220(sp)
    lw a4, 216(sp)
    xor a4, a2, a3
    snez a4, a4
    sw a4, 216(sp)

    lw a5, 216(sp)
    sw a5, 212(sp)

    lw a6, 216(sp)
    bnez a6, and18_then
    j and18_end

and18_then:
    call t
    sw a0, 208(sp)
    li t0, 0
    lw t1, 208(sp)
    lw t2, 204(sp)
    xor t2, t0, t1
    snez t2, t2
    sw t2, 204(sp)

    lw t3, 204(sp)
    sw t3, 212(sp)

    j and18_end

and18_end:
    lw t4, 212(sp)
    sw t4, 200(sp)

    li t5, 0
    lw t6, 200(sp)
    lw a0, 196(sp)
    xor a0, t5, t6
    snez a0, a0
    sw a0, 196(sp)

    lw a1, 196(sp)
    sw a1, 192(sp)

    lw a2, 196(sp)
    bnez a2, or17_end
    j or17_then

or17_end:
    lw a3, 192(sp)
    sw a3, 188(sp)



    call f
    sw a0, 184(sp)
    li a4, 0
    lw a5, 184(sp)
    lw a6, 180(sp)
    xor a6, a4, a5
    snez a6, a6
    sw a6, 180(sp)

    lw t0, 180(sp)
    sw t0, 176(sp)

    lw t1, 180(sp)
    bnez t1, and20_then
    j and20_end

and20_then:
    call f
    sw a0, 172(sp)
    li t2, 0
    lw t3, 172(sp)
    lw t4, 168(sp)
    xor t4, t2, t3
    snez t4, t4
    sw t4, 168(sp)

    lw t5, 168(sp)
    sw t5, 176(sp)

    j and20_end

and20_end:
    lw t6, 176(sp)
    sw t6, 164(sp)

    li a0, 0
    lw a1, 164(sp)
    lw a2, 160(sp)
    xor a2, a0, a1
    snez a2, a2
    sw a2, 160(sp)

    lw a3, 160(sp)
    sw a3, 156(sp)

    lw a4, 160(sp)
    bnez a4, or19_end
    j or19_then

or19_end:
    lw a5, 156(sp)
    sw a5, 152(sp)

    lw a6, 148(sp)
    sw a6, 144(sp)

    lw a0, 144(sp)
    call putint
    li a0, 32
    call putch
    lw t0, 140(sp)
    sw t0, 136(sp)

    lw a0, 136(sp)
    call putint
    li a0, 10
    call putch
    lw t1, 532(sp)
    sw t1, 132(sp)

    lw t2, 132(sp)
    mv a0, t2
    j main_end

or19_then:
    call f
    sw a0, 128(sp)
    li t3, 0
    lw t4, 128(sp)
    lw t5, 124(sp)
    xor t5, t3, t4
    snez t5, t5
    sw t5, 124(sp)

    lw t6, 124(sp)
    sw t6, 156(sp)

    j or19_end

or17_then:
    call t
    sw a0, 120(sp)
    li a0, 0
    lw a1, 120(sp)
    lw a2, 116(sp)
    xor a2, a0, a1
    snez a2, a2
    sw a2, 116(sp)

    lw a3, 116(sp)
    sw a3, 192(sp)

    j or17_end

or15_then:
    call t
    sw a0, 112(sp)
    li a4, 0
    lw a5, 112(sp)
    lw a6, 108(sp)
    xor a6, a4, a5
    snez a6, a6
    sw a6, 108(sp)

    lw t0, 108(sp)
    sw t0, 228(sp)

    j or15_end

or13_then:

    call f
    sw a0, 104(sp)
    li t1, 0
    lw t2, 104(sp)
    lw t3, 100(sp)
    xor t3, t1, t2
    snez t3, t3
    sw t3, 100(sp)

    lw t4, 100(sp)
    sw t4, 96(sp)

    lw t5, 100(sp)
    bnez t5, and14_then
    j and14_end

and14_then:
    call t
    sw a0, 92(sp)
    li t6, 0
    lw a0, 92(sp)
    lw a1, 88(sp)
    xor a1, t6, a0
    snez a1, a1
    sw a1, 88(sp)

    lw a2, 88(sp)
    sw a2, 96(sp)

    j and14_end

and14_end:
    lw a3, 96(sp)
    sw a3, 84(sp)

    li a4, 0
    lw a5, 84(sp)
    lw a6, 80(sp)
    xor a6, a4, a5
    snez a6, a6
    sw a6, 80(sp)

    lw t0, 80(sp)
    sw t0, 264(sp)

    j or13_end

or11_then:

    call t
    sw a0, 76(sp)
    li t1, 0
    lw t2, 76(sp)
    lw t3, 72(sp)
    xor t3, t1, t2
    snez t3, t3
    sw t3, 72(sp)

    lw t4, 72(sp)
    sw t4, 68(sp)

    lw t5, 72(sp)
    bnez t5, and12_then
    j and12_end

and12_then:
    call t
    sw a0, 64(sp)
    li t6, 0
    lw a0, 64(sp)
    lw a1, 60(sp)
    xor a1, t6, a0
    snez a1, a1
    sw a1, 60(sp)

    lw a2, 60(sp)
    sw a2, 68(sp)

    j and12_end

and12_end:
    lw a3, 68(sp)
    sw a3, 56(sp)

    li a4, 0
    lw a5, 56(sp)
    lw a6, 52(sp)
    xor a6, a4, a5
    snez a6, a6
    sw a6, 52(sp)

    lw t0, 52(sp)
    sw t0, 280(sp)

    j or11_end

or9_then:

    call t
    sw a0, 48(sp)
    li t1, 0
    lw t2, 48(sp)
    lw t3, 44(sp)
    xor t3, t1, t2
    snez t3, t3
    sw t3, 44(sp)

    lw t4, 44(sp)
    sw t4, 40(sp)

    lw t5, 44(sp)
    bnez t5, and10_then
    j and10_end

and10_then:
    call t
    sw a0, 36(sp)
    li t6, 0
    lw a0, 36(sp)
    lw a1, 32(sp)
    xor a1, t6, a0
    snez a1, a1
    sw a1, 32(sp)

    lw a2, 32(sp)
    sw a2, 40(sp)

    j and10_end

and10_end:
    lw a3, 40(sp)
    sw a3, 28(sp)

    li a4, 0
    lw a5, 28(sp)
    lw a6, 24(sp)
    xor a6, a4, a5
    snez a6, a6
    sw a6, 24(sp)

    lw t0, 24(sp)
    sw t0, 296(sp)

    j or9_end

or4_then:
    call t
    sw a0, 20(sp)
    li t1, 0
    lw t2, 20(sp)
    lw t3, 16(sp)
    xor t3, t1, t2
    snez t3, t3
    sw t3, 16(sp)

    lw t4, 16(sp)
    sw t4, 444(sp)

    j or4_end

or3_then:
    call f
    sw a0, 12(sp)
    li t5, 0
    lw t6, 12(sp)
    lw a0, 8(sp)
    xor a0, t5, t6
    snez a0, a0
    sw a0, 8(sp)

    lw a1, 8(sp)
    sw a1, 468(sp)

    j or3_end

or2_then:
    call t
    sw a0, 4(sp)
    li a2, 0
    lw a3, 4(sp)
    lw a4, 0(sp)
    xor a4, a2, a3
    snez a4, a4
    sw a4, 0(sp)

    lw a5, 0(sp)
    sw a5, 492(sp)

    j or2_end

or1_then:
    call f
    sw a0, 18446744073709551612(sp)
    li a6, 0
    lw t0, 18446744073709551612(sp)
    lw t1, 18446744073709551608(sp)
    xor t1, a6, t0
    snez t1, t1
    sw t1, 18446744073709551608(sp)

    lw t2, 18446744073709551608(sp)
    sw t2, 516(sp)

    j or1_end
main_end:
    lw ra, 536(sp)
    addi sp, sp, 544
    ret

