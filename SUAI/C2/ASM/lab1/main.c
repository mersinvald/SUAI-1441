#include <stdio.h>
#include <stdint.h>

/* Y = (1 + C - 2A^2) / 2B^3 */

/* Y = (1 + 135 - 2*2^2) / 2*4^3
 * Y = (136 - 8) / 2*64
 * Y = 128 / 128
 * Y = 1
 */

void assembler_signed() {
    int8_t A, Y;
    int16_t B, C;

    A = 2;
    B = 4;
    C = 135;

    asm (
        /* C -> bx */
        "movw %1,%%bx\n\t"
        /* A -> al */
        "movb %2,%%al\n\t"

        /* C + 1 */
        "addw  $1, %%bx\n\t"
        /* A * A */
        "imulb %%al\n\t"
        /* A * 2 */
        "addb  %%al, %%al\n\t"
        /* С - A */
        "subw %%ax, %%bx\n\t"

        /* B -> ax */
        "movw %3, %%ax\n\t"
        /* B * B * B */
        "movw %%ax, %%cx\n\t"
        "imulw %%cx\n\t"
        "imulw %%cx\n\t"
        /* B * 2 */
        "addw %%ax, %%ax\n\t"

        /* C / B */
        "idivw %%bx\n\t"

        "movw %%ax, %0\n\t"

        /* output registers */
        : "=m" (Y)
        /* input registers */
        : "m" (C), "m" (A), "m" (B)
        /* used registers */
        : "%bx", "%ax", "%al"
    );

    printf("%d\n", Y);

}

    void assembler_unsigned() {
        uint8_t A, Y;
        uint16_t B, C;

        A = 2;
        B = 4;
        C = 135;

        asm (
            /* C -> bx */
            "movw %1,%%bx\n\t"
            /* A -> al */
            "movb %2,%%al\n\t"

            /* C + 1 */
            "addw  $1, %%bx\n\t"
            /* A * A */
            "mulb %%al\n\t"
            /* A * 2 */
            "addb  %%al, %%al\n\t"
            /* С - A */
            "subw %%ax, %%bx\n\t"

            /* B -> ax */
            "movw %3, %%ax\n\t"
            /* B * B * B */
            "movw %%ax, %%cx\n\t"
            "mulw %%cx\n\t"
            "mulw %%cx\n\t"

            /* B * 2 */
            "addw %%ax, %%ax\n\t"

            /* C / B */
            "divw %%bx\n\t"

            "movw %%ax, %0\n\t"

            /* output registers */
            : "=m" (Y)
            /* input registers */
            : "m" (C), "m" (A), "m" (B)
            /* used registers */
            : "%bx", "%ax", "%al"
        );

        printf("%d\n", Y);

    }

int main(void) {
    assembler_signed();
    assembler_unsigned();
    return 0;
}

