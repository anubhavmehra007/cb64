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
			output_str=base_64_encode(input_str_encode);
			printf("%s\n", output_str);
			break;
		case 'd' :
			const char* input_str_decode = argv[2];
			output_str=base_64_decode(input_str_decode);
			printf("%s\n", output_str);
			break;
		default:
		printf("%s", usage);
		return -1;

	}
	free(output_str);
	return 0;

}
