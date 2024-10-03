#include "base_64.h"

size_t strsize(const char* str) {
	static const char* start = NULL;
	static const char* end = NULL;
	static size_t size = 0;
	if(start != NULL && end != NULL && str >= start && str < end) {
		return size;
	}
	size = 0;
	start = str;
	while(*(str++) != '\0') size++;
	end = str;
	return size;


}

size_t base_64_size(size_t n) {
	size_t rem = n % 3;
	if(rem != 0) n+=(3-rem);
	return 4*((n)/3) + 1; //1 for null character
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

void base_64_encode(const char* in, char* out) {
	size_t input_size = strsize(in);
	size_t counter = input_size;
	char input_buffer[3];
	char output_buffer[4];
	size_t i = 0;
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
}
