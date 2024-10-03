#include <assert.h>
#include<string.h>
#include "../src/base_64.h"
#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>

Test(base64encode, test_output) {
	const char* input = "ankh uthi mohabbat ne agadai li dil ka sauda hua chandni raat me unki nazaro ne kuch esa jaadu kiya mit gaye hum to pehli mulakaat me";
	char * output = (char *)malloc(base_64_size(strsize(input)));	
	base_64_encode(input, output);
	printf("%s\n", output);
	cr_expect(strcmp(output, "YW5raCB1dGhpIG1vaGFiYmF0IG5lIGFnYWRhaSBsaSBkaWwga2Egc2F1ZGEgaHVhIGNoYW5kbmkgcmFhdCBtZSB1bmtpIG5hemFybyBuZSBrdWNoIGVzYSBqYWFkdSBraXlhIG1pdCBnYXllIGh1bSB0byBwZWhsaSBtdWxha2FhdCBtZQ==") == 0);
	free(output);
}
