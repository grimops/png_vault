#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exit_message.h"
#include "png_io.h"
#include "file_io.h"

int main(int argc, char **argv)
{
	if (argc < 4)
		exit_message("Usage: program_name <file_in> <file_out>");
	char *file_str = (char*)malloc(1);
	size_t size_of_file; 
	if(read_file(argv[3], &file_str, &size_of_file))
		exit_message("[!] Can't read file");
	printf("%s\n", file_str);
	read_png_file(argv[1]);
	process_file();
	write_png_file(argv[2]);

return 0;
}
