/* See LICENSE file for copyright and license details. */
#ifndef BUCKET_H
#define BUCKET_H

struct bucket_t {
	int size;
	int level;
};

void init_bucket(struct bucket_t * bucket, int token_count);
int bucket_empty(struct bucket_t * bucket, int drain_condition);
#endif
