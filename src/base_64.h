#ifndef BASE_64_H
#define BASE_64_H

#include<stddef.h>
size_t strsize(const char* str);
size_t base_64_size(size_t n);
size_t base_64_search(char c);
size_t base_str_size(size_t n);
void base_64_encode(const char* in, char* out);
void base_64_decode(const char* in, char* out);
void base_64_algo(const char* input_buf, char* output_buf, char** out);
void base_64_decode_algo(const char* input_buf, char* output_buf, char** out);

#endif
