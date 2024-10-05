#include "./src/base_64.h"
#include <stdio.h>
#include<stdlib.h>
const char* usage = "<cb64 <option> \"<string/file>\"\n Supported Options:-\ne - encode string\nd - decode string\nfe - encode file";
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
			break;
		case 'd' :
			const char* input_str_decode = argv[2];
			output_str=base_64_decode(input_str_decode);
			break;
		case 'f' :
			switch(argv[1][1]) {
				case 'e':
					FILE* file = fopen(argv[2], "r");
					if(file == NULL) {
						printf("Error Opening File\n%s", usage);
						return -1;
					}
					output_str = encode_file_base_64(file);
					fclose(file);
					break;
				default:
					printf("%s", usage);
					return -1;
			}
			break;
		default:
		printf("%s", usage);
		return -1;

	}
	if(output_str == NULL) {
		printf("Something went wrong\n");
		return - 1;
	}
	printf("%s\n", output_str);
	free(output_str);
	return 0;

}
