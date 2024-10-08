#include<assert.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>
#include<string.h>

Test(filesize, test_output) {
	const char* test_file_path = "/home/anubhav/test.txt";
	FILE* file = fopen(test_file_path, "r");
	char* output = encode_file_base_64(file);
	fclose(file);
	cr_expect(strcmp(output, "data:text/plain;base64,aGVsbG8gaG93IGFyZSB5b3Ugd2hhdCBhcmUgeW91IGRvaW5nCg==") == 0); 
	file = fopen("/home/anubhav/output.text", "w+");
	decode_file_base_64(output, file);
	fclose(file);
	free(output);
}
