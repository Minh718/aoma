#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define PAGING_CPU_BUS_WIDTH 32

#define PAGING_PTE_PRESENT_MASK (1 << 0)
#define PAGING_PTE_SWAPPED_MASK (1 << 1)
#define PAGING_PTE_SWPTYP_HIBIT 4
#define PAGING_PTE_SWPTYP_LOBIT 0
#define PAGING_PTE_SWPOFF_HIBIT 25
#define PAGING_PTE_SWPOFF_LOBIT 5
#define PAGING_PTE_SWPTYP_MASK GENMASK(PAGING_PTE_SWPTYP_HIBIT, PAGING_PTE_SWPTYP_LOBIT)
#define PAGING_PTE_SWPOFF_MASK GENMASK(PAGING_PTE_SWPOFF_HIBIT, PAGING_PTE_SWPOFF_LOBIT)
#define GENMASK(h, l) (((~0U) << (l)) & (~0U >> (31 - (h))))

#define SETBIT(pte, mask) (pte |= mask)
#define SETVAL(pte, val, mask, lbit) (pte = (pte & ~mask) | ((val << lbit) & mask))
#define PAGING_PAGE_PRESENT(pte) (!(pte & PAGING_PTE_PRESENT_MASK))

int pte_set_swap(uint32_t *pte, int swptyp, int swpoff) {
    SETBIT(*pte, PAGING_PTE_PRESENT_MASK);
    SETBIT(*pte, PAGING_PTE_SWAPPED_MASK);

    SETVAL(*pte, swptyp, PAGING_PTE_SWPTYP_MASK, PAGING_PTE_SWPTYP_LOBIT);
    SETVAL(*pte, swpoff, PAGING_PTE_SWPOFF_MASK, PAGING_PTE_SWPOFF_LOBIT);

    return 0;
}

int main() {
    uint32_t *pgd = malloc(PAGING_CPU_BUS_WIDTH * sizeof(uint32_t));
    uint32_t *pte0 = &pgd[0];
    pte_set_swap(pte0, 0, 2);
    uint32_t e0 = pgd[0];
    printf("%d\n", PAGING_PAGE_PRESENT(e0));

    free(pgd); // Free the allocated memory

    return 0;
}
