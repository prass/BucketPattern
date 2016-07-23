/* See LICENSE file for copyright and license details. */
#include "bucket.h"

void init_bucket(struct bucket_t * bucket, int token_count) {
	if(token_count < 0) {
		token_count = 0;
	}

	/* start with a filled bucket */
	bucket->size = token_count;
	bucket->level = token_count;
}

void update_bucket(struct bucket_t * bucket, int drain) {
	if(drain) {
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
	}
}

int bucket_empty(struct bucket_t *bucket) {
	if(bucket->level <= 0) {
		return 1;
	}
	return 0;
}

int bucket_full(struct bucket_t *bucket) {
	if(bucket->level >= bucket->size) {
		return 1;
	}
	return 0;
}
