// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <stdint.h>
// #define PAGING_CPU_BUS_WIDTH 22 /* 22bit bus - MAX SPACE 4MB */
// #define SETBIT(v,mask) (v=v|mask)
// #define CLRBIT(v,mask) (v=v&~mask)
// #define SETVAL(v,value,mask,offst) (v=(v&~mask)|((value<<offst)&mask))
// #define BIT(nr)                 (1U << (nr))
// #define PAGING_PTE_SWAPPED_MASK BIT(30)
// #define PAGING_PTE_PRESENT_MASK BIT(31)
// #define PAGING_PTE_FPN_LOBIT 0
// #define PAGING_PTE_FPN_HIBIT 12
// #define BITS_PER_LONG 32
// #define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
// #define PAGING_PAGESZ  256      /* 256B or 8-bits PAGE NUMBER */
// #define PAGING_ADDR_OFFST_LOBIT 0

// #define NBITS2(n) ((n&2)?1:0)
// #define NBITS4(n) ((n&(0xC))?(2+NBITS2(n>>2)):(NBITS2(n)))
// #define NBITS8(n) ((n&0xF0)?(4+NBITS4(n>>4)):(NBITS4(n)))
// #define NBITS16(n) ((n&0xFF00)?(8+NBITS8(n>>8)):(NBITS8(n)))
// #define NBITS32(n) ((n&0xFFFF0000)?(16+NBITS16(n>>16)):(NBITS16(n)))
// #define NBITS(n) (n==0?0:NBITS32(n))
// #define PAGING_ADDR_PGN_LOBIT NBITS(PAGING_PAGESZ)
// #define PAGING_ADDR_PGN_HIBIT (PAGING_CPU_BUS_WIDTH - 1)
// #define PAGING_PGN_MASK  GENMASK(PAGING_ADDR_PGN_HIBIT,PAGING_ADDR_PGN_LOBIT)
// #define GETVAL(v,mask,offst) ((v&mask)>>offst)
// #define PAGING_PGN(x)  GETVAL(x,PAGING_PGN_MASK,PAGING_ADDR_PGN_LOBIT)

// #define PAGING_MEMRAMSZ BIT(10) /* 1MB */
// #define PAGING_ADDR_FPN_LOBIT NBITS(PAGING_PAGESZ)
// #define PAGING_ADDR_FPN_HIBIT (NBITS(PAGING_MEMRAMSZ) - 1)
// #define PAGING_FPN_MASK  GENMASK(PAGING_ADDR_FPN_HIBIT,PAGING_ADDR_FPN_LOBIT)
// #define PAGING_FPN(x)  GETVAL(x,PAGING_FPN_MASK,PAGING_ADDR_FPN_LOBIT)

// #define PAGING_ADDR_OFFST_HIBIT (NBITS(PAGING_PAGESZ) - 1)
// #define PAGING_OFFST_MASK  GENMASK(PAGING_ADDR_OFFST_HIBIT,PAGING_ADDR_OFFST_LOBIT)
// #define PAGING_OFFST(x)  GETVAL(x,PAGING_OFFST_MASK,PAGING_ADDR_OFFST_LOBIT)
// #define PAGING_PAGE_ALIGNSZ(sz) (DIV_ROUND_UP(sz,PAGING_PAGESZ)*PAGING_PAGESZ)
// #define GENMASK(h, l) \
// 	(((~0U) << (l)) & (~0U >> (BITS_PER_LONG  - (h) - 1)))
// #define PAGING_PTE_FPN_MASK    GENMASK(PAGING_PTE_FPN_HIBIT,PAGING_PTE_FPN_LOBIT)
// #define PAGING_PTE_PRESENT_MASK BIT(31) 
// #define PAGING_PAGE_PRESENT(pte) (pte&PAGING_PTE_PRESENT_MASK)

// #define PAGING_SWPFPN_OFFSET 5  
// #define PAGING_MEMSWPSZ BIT(14) /* 16MB */
// #define PAGING_SWP_HIBIT (NBITS(PAGING_MEMSWPSZ) - 1)
// #define PAGING_SWP_LOBIT NBITS(PAGING_PAGESZ)
// #define PAGING_SWP_MASK  GENMASK(PAGING_SWP_HIBIT,PAGING_SWP_LOBIT)
// #define PAGING_SWP(pte) ((pte&PAGING_SWP_MASK) >> PAGING_SWPFPN_OFFSET)
// int pte_set_fpn(uint32_t *pte, int fpn)
// {
//   SETBIT(*pte, PAGING_PTE_PRESENT_MASK);
//   CLRBIT(*pte, PAGING_PTE_SWAPPED_MASK);

//   SETVAL(*pte, fpn, PAGING_PTE_FPN_MASK, PAGING_PTE_FPN_LOBIT); 

//   return 0;
// }

// int main(){
// uint32_t *pgd = malloc(PAGING_CPU_BUS_WIDTH * sizeof(uint32_t));
//      uint32_t *pte5 = &pgd[0];
//     //  uint32_t *pte1 = &pgd[1];
//     //  uint32_t *pte2 = &pgd[2];
//     //  uint32_t *pte3 = &pgd[3];
//     //  uint32_t *pte4 = &pgd[4];
//       // pte_set_fpn(pte1, 0);
//       // pte_set_fpn(pte2, 1);
//       // pte_set_fpn(pte3, 2);
//       // pte_set_fpn(pte4, 3);
//       pte_set_fpn(pte5, 4);
//     uint32_t e5 = pgd[0];
//     // uint32_t e1 = pgd[1];
//     // uint32_t e2 = pgd[2];
//     // uint32_t e3 = pgd[3];
//     // uint32_t e4 = pgd[4];
//     // uint32_t e6 = pgd[6];
//   // printf("%d\n", PAGING_PAGE_PRESENT(e1));
//   // printf("%d\n", PAGING_PAGE_PRESENT(e2));
//   // printf("%d\n", PAGING_SWP(e2));
//   // printf("%d\n", PAGING_PAGE_PRESENT(e3));
//   // printf("%d\n", PAGING_SWP(e3));
//   // printf("%d\n", PAGING_PAGE_PRESENT(e4));
//   // printf("%d\n", PAGING_PAGE_PRESENT(e5));
//   printf("%d\n", PAGING_FPN(e5));

//   // printf("%d\n", PAGING_PAGE_PRESENT(e6));
//   // printf("%d\n", PAGING_PAGE_PRESENT(0));
//   // printf("%d\n", PAGING_PAGE_PRESENT(1));
//   // printf("%d\n", PAGING_PAGE_PRESENT(55));
// //   for(int pgit = 0; pgit < 10; pgit++)
// //   {
// //      printf("%08ld: %08x\n", pgit * sizeof(uint32_t), pgd[pgit]);
// //      pte_set_fpn(pte, pgit);
// //      printf("%08ld: %08x\n", pgit * sizeof(uint32_t), pgd[pgit]);
// //   }
// }
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PAGING_PAGESZ  256      /* 256B or 8-bits PAGE NUMBER */
#define NBITS2(n) ((n&2)?1:0)
#define NBITS4(n) ((n&(0xC))?(2+NBITS2(n>>2)):(NBITS2(n)))
#define NBITS8(n) ((n&0xF0)?(4+NBITS4(n>>4)):(NBITS4(n)))
#define NBITS16(n) ((n&0xFF00)?(8+NBITS8(n>>8)):(NBITS8(n)))
#define NBITS32(n) ((n&0xFFFF0000)?(16+NBITS16(n>>16)):(NBITS16(n)))
#define NBITS(n) (n==0?0:NBITS32(n))
#define GETVAL(v,mask,offst) ((v&mask)>>offst)
#define PAGING_MEMRAMSZ (1 << 10) /* 1MB */
#define PAGING_ADDR_FPN_LOBIT NBITS(PAGING_PAGESZ)
#define PAGING_ADDR_FPN_HIBIT (NBITS(PAGING_MEMRAMSZ) - 1)

#define PAGING_FPN_MASK  GENMASK(PAGING_ADDR_FPN_HIBIT, PAGING_ADDR_FPN_LOBIT)
#define PAGING_FPN(x)  GETVAL(x, PAGING_FPN_MASK, PAGING_ADDR_FPN_LOBIT)

void pte_set_fpn(uint32_t *pte, uint32_t fpn) {
  *pte = (*pte & ~PAGING_FPN_MASK) | (fpn << PAGING_ADDR_FPN_LOBIT);
}

int main() {
  uint32_t *pgd = malloc(PAGING_PAGESZ * sizeof(uint32_t));
  uint32_t *pte5 = &pgd[0];
  
  pte_set_fpn(pte5, 4);
  
  uint32_t e5 = pgd[0];
  printf("%d\n", PAGING_FPN(e5));
  
  free(pgd);
  return 0;
}