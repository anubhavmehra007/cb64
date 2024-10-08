#include "base_64.h"
#include<stdlib.h>
#include<memory.h>


void base_64_decode_algo(const char* input_buf, char* output_buf, char** out) {
	int i =0;
	char tin_buf[4];
	while(i < 4) {
		tin_buf[i] = base_64_search(input_buf[i]);
		i++;
	}
	output_buf[0] = ((tin_buf[0] & 0x3f) << 2) | ((tin_buf[1]  & 0x30) >> 4);
	output_buf[1] = (((tin_buf[1] & 0x0f) << 4) | ((tin_buf[2] & 0x3c) >> 2));
	output_buf[2] = (((tin_buf[2] & 0x03) << 6 ) | ((tin_buf[3] & 0x3f)));
	if(out == NULL) return;
	for(i =0; i < 3; i++) {
		*(*(out)) = output_buf[i];
		(*out) = (*out) + 1;
	}

}

void base_64_algo(const char* input_buf, char* output_buf, char** out) {
	const char* base_64_lookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int i;
	output_buf[0] = (input_buf[0] & 0xfc) >> 2;
	output_buf[1] = (((input_buf[0] & 0x03) << 4) | ((input_buf[1] & 0xf0) >> 4));
	output_buf[2] = (((input_buf[1] & 0x0f) << 4 ) | ((input_buf[2] & 0xc0) >>4)) >> 2;
	output_buf[3] = (input_buf[2] & 0x3f);
	for(i =0 ; i < 4; i++) {
		*(*(out)) = base_64_lookup[(size_t)output_buf[i]];
		(*out) = (*out) + 1;
	}

}

char* base_64_encode(const char* in) {
	size_t input_size = strsize(in);
	size_t counter = input_size;
	char input_buffer[3];
	char output_buffer[4];
	size_t i = 0;
	char* out = (char *) malloc(base_64_size(input_size));
	if(out == NULL) return NULL;
	char* ptr = out;
	while(counter-- > 0) {
		input_buffer[i++] = in[input_size - counter-1];
		if(i == 3) {
			base_64_algo(input_buffer, output_buffer, &ptr);
			i = 0;
		}
	}
	if(i) {
		int j = i;
		while(i<3) input_buffer[i++] = 0;
		base_64_algo(input_buffer, output_buffer, &ptr);
		char* rev_ptr = ptr;
		while(j++<3) {
			*(--rev_ptr) = '=';
		}

	}
	*ptr = '\0';
	return out;
}

char * base_64_decode(const char* in) {
	size_t input_size = strsize(in);
	size_t counter = input_size;
	char input_buffer[4];
	char output_buffer[3];
	size_t i = 0;
	char* out = (char *) malloc(base_str_size(input_size));
	if(out == NULL) return NULL;
	char* ptr = out;
	while(counter -- > 0) {
		input_buffer[i++] = in[input_size-counter-1];
		if(i==4) {
			base_64_decode_algo(input_buffer, output_buffer, &ptr);
			i = 0;
		}
	if(*(ptr-1)!= '\0')
		*ptr = '\0';
	}
	return out;
}


