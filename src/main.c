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
		if(argc != 4)
			exit_message("[!] Usage: ./png_vault <option> <input-png> <out-file>");
		unsigned char *bin_arr;
		size_t size_of_bin;
		read_png_file(argv[2]);
		read_steg(&bin_arr, &size_of_bin, 'g');
		char *str = (char*)malloc(size_of_bin/8);
		bin_to_str(bin_arr, size_of_bin, str);
		str[size_of_bin/8 - 1] = '\0';
		write_file(argv[3], str, size_of_bin/8 - 1);
	}
	else if(argv[1][0] == 'e'){
		if(argc != 5)
			exit_message("[!] Usage: ./png_vault <option> <embed-file> <input-png> <output-png>");
		char *file_str = (char*)malloc(1);
		size_t size_of_file;
		if(read_file(argv[2], &file_str, &size_of_file))
			exit_message("[!] Can't read file\n");
		printf("%s is %d bytes\n", file_str, size_of_file);

		size_t size_of_bin_arr = size_of_file * 8;
		unsigned char bin_arr[size_of_bin_arr];
		str_to_bin(file_str, size_of_file, bin_arr);

		read_png_file(argv[3]);
		write_steg(bin_arr, size_of_bin_arr, 'g');
		write_png_file(argv[4]);
	}
return 0;
}
