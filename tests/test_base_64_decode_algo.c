#include <assert.h>
#include<string.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>
#include<stdio.h>

Test(base64algo, test_output) {
	const char* input = "YWJj";
	char output[4];
	char* ptr = output;
	output[3] = '\0';
	char out_buff[3];
	base_64_decode_algo(input, out_buff, &ptr);
	cr_expect(strcmp(output, "abc") == 0);
}
