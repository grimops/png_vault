#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

int read_file(char *file_path, char **file_contents, size_t *file_size)
{
	*file_size = 1;
	*file_contents = (char*)malloc(*file_size);

	if(*file_contents == NULL)
		return 1;
	
	FILE *fp = fopen(file_path, "r");
	if(fp == NULL)
		return 1;

	while(1)
	{
		char ch = fgetc(fp);
		if(ch == EOF){
			fclose(fp);
			return 0;
		}
		*file_contents = (char*)realloc(*file_contents, ++(*file_size));
		if(*file_contents == NULL)
			return 1;
		(*file_contents)[*file_size - 2] = ch;
	}
}

int write_file(char *file_path, char *file_contents, size_t file_size)
{
	FILE *fp = fopen(file_path, "w");
	if(fp == NULL)
		return 1;
	for(int i = 0; i < file_size; i++)
	{
		fputc(file_contents[i], fp);
	}
	fclose(fp);
return 0;
}
