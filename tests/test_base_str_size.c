#include<assert.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>

Test(strsize, test_output) {
	cr_expect(base_str_size(172) == 130, "Wrong size for 172");
}
