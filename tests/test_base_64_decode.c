#include <assert.h>
#include<string.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>

Test(base64encode, test_output) {
	const char* input = "under pressure, crushing down on you crushing down on me no man asked for under pressure brings the building down puts family in two put's people on street";
	char* output = base_64_encode(input);
	char* output_decode = base_64_decode(output);
	cr_expect(strcmp(output_decode, input) == 0);
	free(output);
	free(output_decode);
}
