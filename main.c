/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include "bucket.h"

#define TEST_SIZE 100

int main(void) {
	int draining_count;
	int filling_count;

	struct bucket_t b;

	init_bucket(&b, TEST_SIZE);
	printf("Bucket has a level of %d:\n\n", TEST_SIZE);

	for(draining_count = 1; draining_count <= (TEST_SIZE + 1); draining_count++) {
		update_bucket(&b, 1);
		if(bucket_empty(&b)) {
			printf("Bucket empty after %d times draining...\n", draining_count);
			break;
		}
	}
	if(draining_count != TEST_SIZE) {
		printf("Draining failed! Bucket should be empty after %d times!\n", TEST_SIZE);
	}

	b.level = 0;
	for(filling_count = 1; filling_count <= (TEST_SIZE + 1); filling_count++) {
		update_bucket(&b, 0);
		if(bucket_full(&b)) {
			printf("Bucket full after %d times filling...\n", filling_count);
			break;
		}
	}
	if(filling_count != TEST_SIZE) {
		printf("Filling failed! Should be filled after %d times\n", TEST_SIZE);
	}
	return EXIT_SUCCESS;
}
