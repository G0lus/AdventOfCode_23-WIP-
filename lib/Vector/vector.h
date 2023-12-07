#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct vector vector;

vector* vector_init(size_t len);
void vector_deinit(vector* handle);
bool vector_add(vector* handle, void* data);
void* vector_get(vector* const handle, size_t index);
bool vector_remove(vector* handle, size_t index, size_t n);
size_t vector_get_size(vector* handle);
size_t vector_get_capacity(vector* handle);

#endif