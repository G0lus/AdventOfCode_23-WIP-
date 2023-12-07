add_library(vector 
    vector.c
    vector.h
)

target_sources(vector INTERFACE vector.c)
target_sources(vector PUBLIC vector.h)