#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE (16)


void print_arr(uint32_t *arr) {
	int i = SIZE;

	printf("Colors array (%d-bit):\n", SIZE);
	while(i-- > 0) {
		printf(">> 0x%08x, %d\n", *arr, *arr);
		arr++;
	}

}

int main(int argc, char *argv[]) {
	uint32_t hex_color_codes[SIZE] = {
		0x00000000, 
		0x00FFFFFF,
		0x00FF0000,
		0x0000FF00,
		0x000000FF,
		0x00FFFF00,
		0x0000FFFF,
		0x00FF00FF,
		0x00C0C0C0,
		0x00808080,
		0x00800000,
		0x00808000,
		0x00008000,
		0x00800080,
		0x00008080,
		0x00000080
	};
	
	int i, j;
	uint32_t key;

	(void) argc;
	(void) argv;

	print_arr(hex_color_codes);
	// best for nearly sorted or small arrays
	for (i=1; i< SIZE; i++) {
		key = hex_color_codes[i];
		j = i-1;
		while(j >= 0 && hex_color_codes[j] > key) {
			// repeat shift till we reach the begin or key is no longer smaller
			hex_color_codes[j+1] = hex_color_codes[j];
			j--;
		}
		hex_color_codes[j+1] = key;
	}

	print_arr(hex_color_codes);

	return EXIT_SUCCESS;
}
