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

size_t file_size(FILE* file) {
	size_t p = ftell(file);
	fseek(file, 0L, SEEK_END);
	size_t size = ftell(file);
	fseek(file, p, SEEK_SET);
	return size;
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
