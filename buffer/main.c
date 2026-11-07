#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int znak, pocet = 0;
	char *znaky = NULL;
	char *temp_znaky = NULL;
	
	printf("Zadej znaky:\n");
	while((znak = getchar()) != '\n') {
		temp_znaky = (char*) realloc (znaky, (pocet+1) * sizeof(char));

		if (temp_znaky != NULL) {
			znaky = temp_znaky;
			znaky[pocet] = (char)znak;
			pocet++;
		} else {
			free(znaky);
			puts("Error (re)allocating memory\n");
			exit(1);
		}
	}
// vypis zadanych znaku
	for (int i = 0; i < pocet; i++) {
		printf("%c", znaky[i]);
	}
	printf("\n");
	free(znaky);
	znaky = NULL;
	return 0;
}
