#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
uint32_t *pgd = malloc(PAGING_CPU_BUS_WIDTH * sizeof(uint32_t));
  for(int pgit = 0; pgit < 10; pgit++)
  {
     printf("%08ld: %08x\n", pgit * sizeof(uint32_t), pgd[pgit]);
  }
}