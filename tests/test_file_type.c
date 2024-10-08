#include<assert.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>
#include<string.h>

Test(filesize, test_output) {
	const char* test_file_path = "./tests/test.txt";
	FILE* file = fopen(test_file_path, "r");
	char type[30];
	file_type(file, type);
	cr_expect(strcmp(type, "text/plain") == 0); 
}
