#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exit_message.h"
#include "png_io.h"
#include "file_io.h"
#include "bin_conv.h"

int main(int argc, char **argv)
{
	if(argv[1][0] == 'd'){
		unsigned char *bin_arr;
		size_t size_of_bin;
		read_png_file("example1.png");
		read_steg(&bin_arr, &size_of_bin, 'g');
		char *str = (char*)malloc(size_of_bin/8);
		str[size_of_bin/8 - 1] = '\0';
		bin_to_str(bin_arr, size_of_bin, str);
		printf("string: %s at size of %d\n", str, size_of_bin/8);
	}
	else{
		char *file_str = (char*)malloc(1);
		size_t size_of_file;
		if(read_file("test.txt", &file_str, &size_of_file))
			exit_message("[!] Can't embedded file read file");
		printf("%s is %d bytes\n", file_str, size_of_file);

		size_t size_of_bin_arr = size_of_file * 8;
		unsigned char bin_arr[size_of_bin_arr];
		str_to_bin(file_str, size_of_file, bin_arr);

		read_png_file("example0.png");
		write_steg(bin_arr, size_of_bin_arr, 'g');
		write_png_file("example1.png");
	}
return 0;
}
