#include <assert.h>
#include<string.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>

Test(strsize, test_output) {
	cr_expect(strsize("anubhav") ==7, "Wrong size calculation!!");
}

Test(strsize, test_strlen) {
	const char* test_str = "Anubhav is a good boy";
	cr_expect(strsize(test_str)==strlen(test_str), "Wrong output compared to strlen");
}
