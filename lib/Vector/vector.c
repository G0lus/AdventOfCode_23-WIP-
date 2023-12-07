#include <stdlib.h>
#include "vector.h"


struct vector{
    /* Max size of vector */
    size_t capacity;
    /* Current size of data in vector */
    size_t size;
    void **data;
};

vector* vector_init(size_t size){
    if(size == 0){
        return NULL;
    }

    vector* handle = calloc(1, sizeof(vector));
    
    if(handle == NULL){
        return NULL;
    }
    handle->data = calloc(size, sizeof(void*));
    
    if(handle->data == NULL){
        free(handle);
        return NULL;
    }
    handle->capacity = size;
    return handle;
}

void vector_deinit(vector* handle){
    if(handle == NULL){
        return;
    }

    free(handle->data);
    free(handle);
}

static bool vector_resize(vector* handle, size_t capacity){
    if(handle == NULL){
        return false;
    }

    void** new_data = realloc(handle->data, sizeof(void*) * capacity);
    if(new_data == NULL){
        return false;
    }

    handle->capacity = capacity;
    handle->data = new_data;
    return true;
}

bool vector_add(vector* handle, void* data){
    if(handle == NULL){
        return false;
    }
    if(handle->size +1 >= handle->capacity){
        if(vector_resize(handle, 2*handle->capacity) == false){
            return false;
        }
    }

    handle->data[handle->size] = data;
    handle->size++;
    return true;
}

void* vector_get(vector* const handle, size_t index){
    if(handle == NULL){
        return NULL;
    }
    
    if(handle->size < index){
        return NULL;
    }

    return handle->data[index];
}

bool vector_remove(vector* handle, size_t index, size_t n){
    if(handle == NULL){
        return false;
    }
    if(index + n > handle->capacity){
        n = handle->capacity - index;
    }

/* Removing at index and shift all data by 1 to the left. */
    for(size_t i = 0; i < n; i++){
        if((index + n + i) > handle->capacity){
            handle->data[index] = 0;
        }else{
            handle->data[index] = handle->data[index + n + i];
        }
    }

    handle->capacity -= n;
    return true;
}

size_t vector_get_size(vector* handle){
    return handle == NULL ? 0 : handle->size;
}

size_t vector_get_capacity(vector* handle){
    return handle == NULL ? 0 : handle->capacity;
}
