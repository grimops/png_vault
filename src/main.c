#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exit_message.h"
#include "png_io.h"
#include "file_io.h"
#include "bin_conv.h"

int main(int argc, char **argv)
{
	
	unsigned char *bin_arr;
	size_t size_of_bin;
	read_png_file(argv[1]);
	read_steg(&bin_arr, &size_of_bin, 'g');
	char *str = (char*)malloc(45);

	bin_to_str(bin_arr, size_of_bin, str);
	printf("string: %s\n", str);
	
	/*
	char *file_str = (char*)malloc(1);
	size_t size_of_file;
	if(read_file("test.txt", &file_str, &size_of_file))
		exit_message("[!] Can't embedded file read file");
	printf("%s is %d bytes\n", file_str, size_of_file);

	size_t size_of_bin_arr = size_of_file * 8;
	unsigned char bin_arr[size_of_bin_arr];
	str_to_bin(file_str, size_of_file, bin_arr);

	read_png_file(argv[1]);
	write_steg(bin_arr, size_of_bin_arr, 'g');
	write_png_file(argv[2]);
	*/
return 0;
}
