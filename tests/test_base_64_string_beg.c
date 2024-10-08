
#include<assert.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>

Test(strsize, test_output) {
	const char* a = "abcd";
	const char* b = "a,bcd";
	cr_expect(find_base_64_beg(a) == NULL);
	cr_expect(*(find_base_64_beg(b)) == 'b');
}
