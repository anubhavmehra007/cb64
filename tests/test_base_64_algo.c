#include <assert.h>
#include<string.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>

Test(base64algo, test_output) {
	const char* input = "abc";
	char output[5];
	char* ptr = output;
	output[4] = '\0';
	char out_buff[4];
	base_64_algo(input, out_buff, &ptr);
	cr_expect(strcmp(output, "YWJj") == 0);
}


