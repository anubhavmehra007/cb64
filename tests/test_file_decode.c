#include<assert.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>
#include<string.h>

Test(filesize, test_output) {
	const char* test_file_path = "./tests/test.txt";
	FILE* file_input = fopen(test_file_path, "r");
	char* output = encode_file_base_64(file_input);
	cr_expect(strcmp(output, "data:text/plain;base64,aGVsbG8gaG93IGFyZSB5b3U/Cg==") == 0); 
	FILE* file_output = fopen("./tests/output.txt", "w+");
	decode_file_base_64(output, file_output);
	char input_file[100];
	char output_file[100];
	fseek(file_input, 0, SEEK_SET);
	fseek(file_output, 0, SEEK_SET);
	fgets(input_file, 100, file_input);
	fgets(output_file, 100, file_output);
	cr_expect(strcmp(input_file, output_file)==0);
	fclose(file_output);
	fclose(file_input);
	free(output);
}
