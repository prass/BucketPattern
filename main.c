/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>

#define TEST_SIZE 100

struct bucket_t {
	int size;
	int level;
};

void init_bucket(struct bucket_t * bucket, int token_count) {
	if(token_count < 0) {
		token_count = 0;
	}

	/* start with a filled bucket */
	bucket->size = token_count;
	bucket->level = token_count;
}

int bucket_empty(struct bucket_t * bucket, int drain_condition) {
	if(drain_condition) {
		if(bucket->level >= 0) {
			bucket->level--;
		}
	} else {
		if(bucket->level < bucket->size) {
			bucket->level++;
		}
	}

	/* reset invalid values */
	if(bucket->level > bucket->size) {
		bucket->level = bucket->size;
	}

	/* negative means empty so reset and return true */
	if(bucket->level < 0) {
		bucket->level =  0;
		return 1;
	}
	return 0;
}

int main(void) {
	int draining_count;
	int filling_count;

	struct bucket_t b;

	init_bucket(&b, TEST_SIZE);
	printf("Bucket has a level of %d:\n\n", TEST_SIZE);

	for(draining_count = 0; draining_count < TEST_SIZE + 1; draining_count++) {
		if(bucket_empty(&b, 1)) {
			printf("Bucket empty after %d times draining...\n", draining_count);
			break;
		}
	}
	if(draining_count != TEST_SIZE) {
		printf("Draining failed! Bucket should be empty after %d times!\n", TEST_SIZE);
	}

	b.level = 0;
	for(filling_count = 1; filling_count <= TEST_SIZE; filling_count++) {
		bucket_empty(&b, 0);
		if(b.level == b.size) {
			printf("Bucket full after %d times filling...\n", filling_count);
			break;
		}
	}
	if(filling_count != TEST_SIZE) {
		printf("Filling failed! Should be filled after %d times\n", TEST_SIZE);
	}
	return EXIT_SUCCESS;
}
