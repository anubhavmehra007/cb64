#include <assert.h>
#include<string.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>

Test(base64algo, test_output) {
	const char c = 'a';
	const char c2 = '=';
	cr_expect(base_64_search(c) == 26); 
	cr_expect(base_64_search(c2) == 64); 
}
