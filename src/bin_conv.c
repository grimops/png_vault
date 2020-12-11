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
		for(int i = 0; i < 8; i++)
		{
			char temp = byte >> (i * -1) + (8 - 1);
			if(temp % 2)
				bin_arr[count] = 1;
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
		for(int n = i * 8; n < ((i * 8) + 8); n++)
		{
			file_str[i] = file_str[i] << 1;
			if(bin_arr[n] == 1){
				file_str[i]++;
			}
		}
	}
}

void int64_to_bin(size_t integer_64, unsigned char *bin_arr)
{

	for(int i = 63; i >= 0; i--)
	{
		bin_arr[i] = integer_64 % 2;
		integer_64 = integer_64 >> 1;
	}
}

void bin_to_int64(size_t *integer_64, unsigned char *bin_arr)
{
	*integer_64 = 0;
	for(int i = 0; i < 64; i++)
	{
		*integer_64 = *integer_64 << 1;
		*integer_64 += bin_arr[i];
	}
}

int bincat(unsigned char *bin_arr1, size_t size_bin1, unsigned char *bin_arr2, size_t size_bin2, unsigned char **new_bin, size_t *size_new)
{
	*size_new = size_bin1 + size_bin2;
	*new_bin = (unsigned char*)malloc(*size_new);
	if(*new_bin == NULL)
		return 1;
	for(int i = 0; i < size_bin1; i++)
	{
		(*new_bin)[i] = bin_arr1[i];
	}
	for(int i = 0; i < size_bin2; i++)
	{
		(*new_bin)[i + size_bin1] = bin_arr2[i];
	}
return 0;
}
