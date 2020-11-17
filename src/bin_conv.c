#include "bin_conv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_to_bin(char *file_str, size_t size_of_file, unsigned char *bin_arr)
{
	memset(bin_arr, 0, size_of_file * 8);
	int count = 0;
	for(int ind = 0; ind < size_of_file; ind++)
	{
		char byte = file_str[ind];
		printf("\n%c = ", byte);
		for(int i = 0; i < 8; i++)
		{
			char temp = byte >> (i * -1) + (8 - 1);
			if(temp % 2)
				bin_arr[count] = 1;
			printf("%d ", temp % 2);
			count++;
		}
	}
}

void bin_to_str(unsigned char *bin_arr, size_t size_of_bin_arr, char *file_str)
{
	size_t size_of_file = size_of_bin_arr / 8;
	for(int i = 0; i < size_of_file; i++)
	{
		file_str[i] = 0;
		for(int n = i * 8; n < (i * 8) + 8; n++)
		{
			file_str[i] = file_str[i] << 1;
			if(bin_arr[n] == 1){
				file_str[i]++;
				printf("1");
			}
			else{
				printf("0");
			}
		}
	printf("%c\n", file_str[i]);
	}
}
