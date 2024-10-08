#include "base_64.h"
#include<stdlib.h>
#include<memory.h>


char* encode_file_base_64(FILE* file) {
	size_t size = file_size(file);
	char* encoded_output = (char*) malloc(base_64_size(size));
	if(encoded_output == NULL) return NULL;
	char type[30];
	file_type(file, type);
	char* ptr = encoded_output;
	char o_buf[4];
	char i_buf[3];
	int i = 0;
	while ((i=fread(i_buf, 1, 3, file)) > 0) {
		if(i == 3)
		{
			base_64_algo(i_buf, o_buf, &ptr);
		}
		else {
			break;
		}
	}
	if(i) {
		int j = i;
		while(i<3)	i_buf[i++] = 0;
		base_64_algo(i_buf, o_buf, &ptr);
		char* rev_ptr = ptr;
		while(j++<3)  *(--rev_ptr) = '=';
		
	} 
	*ptr = '\0';
	char* output = (char*) malloc(base_64_size(size) + strsize(type) + 13);
	if(output == NULL) return NULL;
	sprintf(output, "data:%s;base64,%s", type,encoded_output);
	free(encoded_output);
	return output;
}

void decode_file_base_64(const char* in, FILE* file) {
	const char* base_64_beg = find_base_64_beg(in);
	const char* input;
	if(base_64_beg == NULL) input = in;
	else input = base_64_beg;
	size_t input_size = strsize(input);
	size_t counter = input_size;
	char input_buffer[4];
	char output_buffer[3];
	size_t i = 0;
	while(counter -- > 0) {
		input_buffer[i++] = input[input_size-counter-1];
		if(i==4) {
			base_64_decode_algo(input_buffer, output_buffer, NULL);
			fwrite(output_buffer, 1, 3, file);
			i = 0;
		}
	}
}
