#include<assert.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>
#include<string.h>

Test(filesize, test_output) {
	const char* test_file_path = "./tests/test.txt";
	FILE* file = fopen(test_file_path, "r");
	char* output = encode_file_base_64(file);
	fclose(file);
	cr_expect(strcmp(output, "data:text/plain;base64,aGVsbG8gaG93IGFyZSB5b3U/Cg==") == 0); 
	free(output);
}
