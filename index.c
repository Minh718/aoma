#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define PAGING_CPU_BUS_WIDTH 22 /* 22bit bus - MAX SPACE 4MB */
#define SETBIT(v,mask) (v=v|mask)
#define CLRBIT(v,mask) (v=v&~mask)
#define SETVAL(v,value,mask,offst) (v=(v&~mask)|((value<<offst)&mask))
#define BIT(nr)                 (1U << (nr))
#define PAGING_PTE_SWAPPED_MASK BIT(30)
#define PAGING_PTE_PRESENT_MASK BIT(31)
#define PAGING_PTE_FPN_LOBIT 0
#define PAGING_PTE_FPN_HIBIT 12
#define BITS_PER_LONG 32
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define PAGING_PAGESZ  256      /* 256B or 8-bits PAGE NUMBER */
#define PAGING_PAGE_ALIGNSZ(sz) (DIV_ROUND_UP(sz,PAGING_PAGESZ)*PAGING_PAGESZ)
#define GENMASK(h, l) \
	(((~0U) << (l)) & (~0U >> (BITS_PER_LONG  - (h) - 1)))
#define PAGING_PTE_FPN_MASK    GENMASK(PAGING_PTE_FPN_HIBIT,PAGING_PTE_FPN_LOBIT)
int pte_set_fpn(uint32_t *pte, int fpn)
{
  SETBIT(*pte, PAGING_PTE_PRESENT_MASK);
  CLRBIT(*pte, PAGING_PTE_SWAPPED_MASK);

  SETVAL(*pte, fpn, PAGING_PTE_FPN_MASK, PAGING_PTE_FPN_LOBIT); 

  return 0;
}

int main(){
  printf("%d\n", PAGING_PAGE_ALIGNSZ(200));
  printf("%d\n", PAGING_PAGE_ALIGNSZ(300));
// uint32_t *pgd;
// pgd = malloc(PAGING_CPU_BUS_WIDTH * sizeof(uint32_t));
//   for(int pgit = 0; pgit < 10; pgit++)
//   {
//      uint32_t *pte = &pgd[pgit];
//      printf("%08ld: %08x\n", pgit * sizeof(uint32_t), pgd[pgit]);
//      pte_set_fpn(pte, pgit);
//      printf("%08ld: %08x\n", pgit * sizeof(uint32_t), pgd[pgit]);
//   }
}