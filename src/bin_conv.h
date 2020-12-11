#ifndef _BIN_CONV_H_
#define _BIN_CONV_H_
#include <stddef.h>

void str_to_bin(char *file_str, size_t size_of_file, unsigned char *bin_arr);
void bin_to_str(unsigned char *bin_arr, size_t size_of_bin_arr, char *file_str);
void int64_to_bin(size_t integer_64, unsigned char *bin_arr);
void bin_to_int64(size_t *integer_64, unsigned char *bin_arr);
int bincat(unsigned char *bin_arr1, size_t size_bin1, unsigned char *bin_arr2, size_t size_bin2, unsigned char **new_bin, size_t *size_new);

#endif
