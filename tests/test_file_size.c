
#include<assert.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>
#include<sys/stat.h>

Test(filesize, test_output) {
	const char* test_file_path = "/home/anubhav/test.mp4";
	struct stat fd;
	FILE* file = fopen(test_file_path, "r");
	cr_expect(file != NULL, "File Opening Error");
	cr_expect(stat(test_file_path, &fd) != -1, "Error with fstat");
	cr_expect(file_size(file) == fd.st_size); 
}
