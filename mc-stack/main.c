#include <stdio.h>
#define STACK 64

int main(void){
	int  stacky, pocet, zbytek; 
	printf("Zadej pocet bloku: \n");
	scanf("%d", &pocet);
	stacky = (pocet - pocet%STACK) / STACK;
	printf("stacku: %d\n", stacky);
	zbytek = pocet - stacky * STACK;
	printf("zbytek: %d\n", zbytek);
}
