#include<assert.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>

Test(strsize, test_output) {
	cr_expect(base_64_size(128) == 173, "Wrong base_64_output size for 128.");
	cr_expect(base_64_size(129) == 173, "Wrong base_64_output size for 129.");
}
