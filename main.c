#include "./src/base_64.h"
#include <stdio.h>
#include<stdlib.h>
const char* usage = "<cb64 e \"<string>\"\n";
int main(int argc, char* argv[]) { 
	if(argc != 3) {
		printf("%s", usage);
		return -1;
	}
	char* output_str;
	switch(argv[1][0]) {
		case 'e' :
			const char* input_str_encode = argv[2];
			output_str = (char *) malloc(base_64_size(strsize(input_str_encode)));
			base_64_encode(input_str_encode, output_str);
			printf("%s\n", output_str);
			free(output_str);
			break;
		case 'd' :
			const char* input_str_decode = argv[2];
			output_str = (char *) malloc(base_str_size(strsize(input_str_decode)));
			base_64_decode(input_str_decode, output_str);
			printf("%s\n", output_str);
			free(output_str);
			break;
		default:
		printf("%s", usage);
		return -1;

	}
	return 0;

}
