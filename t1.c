#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define PAGING_PAGESZ 256      /* 256B or 8-bits PAGE NUMBER */
#define PAGING_CPU_BUS_WIDTH 32

#define NBITS2(n) ((n&2)?1:0)
#define NBITS4(n) ((n&(0xC))?(2+NBITS2(n>>2)):(NBITS2(n)))
#define NBITS8(n) ((n&0xF0)?(4+NBITS4(n>>4)):(NBITS4(n)))
#define NBITS16(n) ((n&0xFF00)?(8+NBITS8(n>>8)):(NBITS8(n)))
#define NBITS32(n) ((n&0xFFFF0000)?(16+NBITS16(n>>16)):(NBITS16(n)))
#define NBITS(n) (n==0?0:NBITS32(n))
#define GETVAL(v,mask,offst) ((v&mask)>>offst)

#define GENMASK(hi, lo) ((~0U << (lo)) & (~0U >> (31 - (hi))))
#define BIT(x) (1U << (x))

#define PAGING_MEMRAMSZ BIT(10) /* 1MB */
#define PAGING_ADDR_FPN_LOBIT NBITS(PAGING_PAGESZ)
#define PAGING_ADDR_FPN_HIBIT (NBITS(PAGING_MEMRAMSZ) - 1)
#define PAGING_FPN_MASK  GENMASK(PAGING_ADDR_FPN_HIBIT,PAGING_ADDR_FPN_LOBIT)
#define PAGING_FPN(x)  GETVAL(x,PAGING_FPN_MASK,PAGING_ADDR_FPN_LOBIT)

#define PAGING_PTE_FPN_HIBIT 12
#define PAGING_PTE_FPN_MASK    GENMASK(PAGING_PTE_FPN_HIBIT,PAGING_PTE_FPN_LOBIT)
#define PAGING_PTE_SWAPPED_MASK BIT(30)
#define PAGING_PTE_PRESENT_MASK BIT(31) 
#define PAGING_PTE_FPN_LOBIT 0
#define SETBIT(v,mask) (v=v|mask)
#define CLRBIT(v,mask) (v=v&~mask)
#define SETVAL(v,value,mask,offst) (v=(v&~mask)|((value<<offst)&mask))

void pte_set_fpn(uint32_t *pte, uint32_t fpn) {
    SETBIT(*pte, PAGING_PTE_PRESENT_MASK);
    CLRBIT(*pte, PAGING_PTE_SWAPPED_MASK);

    SETVAL(*pte, fpn, PAGING_PTE_FPN_MASK, PAGING_PTE_FPN_LOBIT); 
}

int main() {
    uint32_t *pgd = malloc(PAGING_CPU_BUS_WIDTH * sizeof(uint32_t));
    uint32_t *pte2 = &pgd[2];
    pte_set_fpn(pte2, 2);
    uint32_t e2 = *pte2;  // Retrieve the value from pte2
    printf("%d\n", PAGING_FPN(e2));

    free(pgd); // Don't forget to free the allocated memory
    return 0;
}
