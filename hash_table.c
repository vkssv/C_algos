#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 5 /* to obtain more collisions */


typedef uint32_t hash_t;

typedef struct hlist_node {
	uint32_t next;
	uint32_t prev;
} hlist_node_t;

typedef struct hlist_head {
	uint32_t first;
	uint32_t last;
} hlist_head_t;

static inline uint32_t __hash_color() {

	
	
}  

int main(int argc, char *argv[]) {

	(void) argc;
	(void) argv;

	hlist_head_t color_hash_table[HASH_TABLE_SIZE];

	memset(color_hash_table, 0 sizeof(color_hash_table));

	
	
	

	return EXIT_SUCCESS;
}
