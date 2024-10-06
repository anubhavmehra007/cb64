#include "base_64.h"
#include<stdlib.h>
#include<memory.h>

size_t strsize(const char* str) {
	static const char* start = NULL;
	static const char* end = NULL;
	static size_t size = 0;
	if(start != NULL && end != NULL && str >= start && str < end) {
		return size;
	}
	size = 0;
	start = str;
	while(*(str++) != '\0') size++;
	end = str;
	return size;


}

size_t base_64_size(size_t n) {
	size_t rem = n % 3;
	if(rem != 0) n+=(3-rem);
	return 4*((n)/3) + 1; //1 for null character
}

size_t base_str_size(size_t n) {
	//this requires to be provided by strsize not base_64_size
	//if using base_64_size we'll need to pass n-1
	return n/4*3 + 1; //1 for null character
}

size_t base_64_search(char c) {
	const char* base_64_lookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int i;
	for(i =0; i < strsize(base_64_lookup); i++) {
		if (base_64_lookup[i] == c) return i;
	}
	return 64;
}

void base_64_decode_algo(const char* input_buf, char* output_buf, char** out) {
	int i =0;
	char tin_buf[4];
	while(i < 4) {
		tin_buf[i] = base_64_search(input_buf[i]);
		i++;
	}
	output_buf[0] = ((tin_buf[0] & 0x3f) << 2) | ((tin_buf[1]  & 0x30) >> 4);
	output_buf[1] = (((tin_buf[1] & 0x0f) << 4) | ((tin_buf[2] & 0x3c) >> 2));
	output_buf[2] = (((tin_buf[2] & 0x03) << 6 ) | ((tin_buf[3] & 0x3f)));
	for(i =0; i < 3; i++) {
		*(*(out)) = output_buf[i];
		(*out) = (*out) + 1;
	}

}

void base_64_algo(const char* input_buf, char* output_buf, char** out) {
	const char* base_64_lookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int i;
	output_buf[0] = (input_buf[0] & 0xfc) >> 2;
	output_buf[1] = (((input_buf[0] & 0x03) << 4) | ((input_buf[1] & 0xf0) >> 4));
	output_buf[2] = (((input_buf[1] & 0x0f) << 4 ) | ((input_buf[2] & 0xc0) >>4)) >> 2;
	output_buf[3] = (input_buf[2] & 0x3f);
	for(i =0 ; i < 4; i++) {
		*(*(out)) = base_64_lookup[(size_t)output_buf[i]];
		(*out) = (*out) + 1;
	}

}

char* base_64_encode(const char* in) {
	size_t input_size = strsize(in);
	size_t counter = input_size;
	char input_buffer[3];
	char output_buffer[4];
	size_t i = 0;
	char* out = (char *) malloc(base_64_size(input_size));
	if(out == NULL) return NULL;
	char* ptr = out;
	while(counter-- > 0) {
		input_buffer[i++] = in[input_size - counter-1];
		if(i == 3) {
			base_64_algo(input_buffer, output_buffer, &ptr);
			i = 0;
		}
	}
	if(i) {
		int j = i;
		while(i<3) input_buffer[i++] = 0;
		base_64_algo(input_buffer, output_buffer, &ptr);
		char* rev_ptr = ptr;
		while(j++<3) {
			*(--rev_ptr) = '=';
		}

	}
	*ptr = '\0';
	return out;
}

char * base_64_decode(const char* in) {
	size_t input_size = strsize(in);
	size_t counter = input_size;
	char input_buffer[4];
	char output_buffer[3];
	size_t i = 0;
	char* out = (char *) malloc(base_str_size(input_size));
	if(out == NULL) return NULL;
	char* ptr = out;
	while(counter -- > 0) {
		input_buffer[i++] = in[input_size-counter-1];
		if(i==4) {
			base_64_decode_algo(input_buffer, output_buffer, &ptr);
			i = 0;
		}
	if(*(ptr-1)!= '\0')
		*ptr = '\0';
	}
	return out;
}

size_t file_size(FILE* file) {
	size_t p = ftell(file);
	fseek(file, 0L, SEEK_END);
	size_t size = ftell(file);
	fseek(file, p, SEEK_SET);
	return size;
}

char* encode_file_base_64(FILE* file) {
	size_t size = file_size(file);
	char* encoded_output = (char*) malloc(base_64_size(size));
	if(encoded_output == NULL) return NULL;
	char type[30];
	file_type(file, type);
	char* ptr = encoded_output;
	char o_buf[4];
	char i_buf[3];
	int i = 0;
	while ((i=fread(i_buf, 1, 3, file)) > 0) {
		if(i == 3)
		{
			base_64_algo(i_buf, o_buf, &ptr);
		}
		else {
			break;
		}
	}
	if(i) {
		int j = i;
		while(i<3)	i_buf[i++] = 0;
		base_64_algo(i_buf, o_buf, &ptr);
		char* rev_ptr = ptr;
		while(j++<3)  *(--rev_ptr) = '=';
		
	} 
	*ptr = '\0';
	char* output = (char*) malloc(base_64_size(size) + strsize(type) + 13);
	if(output == NULL) return NULL;
	sprintf(output, "data:%s;base64,%s", type,encoded_output);
	free(encoded_output);
	return output;
}

void file_type(FILE* file, char* type) {
	size_t p = ftell(file);
	char buff[4];
	char rev_buff[4];
	int i =0;
	fread(&buff, sizeof(char)*4, 1, file);
	while(i < 4) {
		rev_buff[3-i] = buff[i];
		i++;
	}
	const unsigned int code = *((const unsigned int *)rev_buff);
//Le' CHAAT GPT Code
	switch (code) {
		case 0x89504E47: // PNG
		    memcpy(type, "image/png", strsize("image/png") + 1);
		    break;
		case 0x47494638: // GIF
		    memcpy(type, "image/gif", strsize("image/gif") + 1);
		    break;
		case 0xFFD8FFE0: // JPEG (JPEG Interchange Format)
		case 0xFFD8FFE1: // JPEG (Exif)
		    memcpy(type, "image/jpeg", strsize("image/jpeg") + 1);
		    break;
		case 0x49492A00: // TIFF (Little Endian)
		    memcpy(type, "image/tiff", strsize("image/tiff") + 1);
		    break;
		case 0x4D4D002A: // TIFF (Big Endian)
		    memcpy(type, "image/tiff", strsize("image/tiff") + 1);
		    break;
		case 0x52494646: // RIFF (WAVE)
		    memcpy(type, "audio/wav", strsize("audio/wav") + 1);
		    break;
		case 0x664C6143: // FLAC
		    memcpy(type, "audio/flac", strsize("audio/flac") + 1);
		    break;
		case 0x000001BA: // MPEG (System)
		case 0x000001B3: // MPEG (Video)
		    memcpy(type, "video/mpeg", strsize("video/mpeg") + 1);
		    break;
		case 0x75736167: // OGG
		    memcpy(type, "audio/ogg", strsize("audio/ogg") + 1);
		    break;
		case 0x1A45DFA3: // Matroska
		    memcpy(type, "video/x-matroska", strsize("video/x-matroska") + 1);
		    break;
		case 0x3C3F786D: // XML
		    memcpy(type, "text/xml", strsize("text/xml") + 1);
		    break;
		case 0x504B0304: // ZIP
		    memcpy(type, "application/zip", strsize("application/zip") + 1);
		    break;
		case 0x25504446: // PDF
		    memcpy(type, "application/pdf", strsize("application/pdf") + 1);
		    break;
		default:
		    // Check if the file is plain text
		    fseek(file, 0, SEEK_SET); // Reset file pointer to the beginning
		    size_t bytes_read = fread(buff, sizeof(char), 4, file);
		    int is_text = 1; // Assume it is text unless proven otherwise
		    for (size_t j = 0; j < bytes_read; j++) {
			if (buff[j] < 0x20 && buff[j] != '\n' && buff[j] != '\r' && buff[j] != '\t') {
			    is_text = 0; // Not text if there's a non-printable character
			    break;
			}
		    }
		    if (is_text) {
			memcpy(type, "text/plain", strsize("text/plain") + 1);
		    } else {
			memcpy(type, "application/octet-stream", strsize("application/octet-stream") + 1);
		    }
		    break;
	    }
	fseek(file, p, SEEK_SET);
}
